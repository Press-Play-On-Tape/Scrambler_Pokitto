#include "Scramble.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::renderScenery() {

    for (uint8_t i = 0; i < 220; i++) {


        // Top 

        if (this->gameScreenVars.scenery.top[i] > this->gameScreenVars.viewY && (this->gameScreenVars.scenery.top[i] <= this->gameScreenVars.viewY + Constants::Screen_Height)) {

            PD::setColor(15);
            PD::drawFastVLine(i, 0, this->gameScreenVars.scenery.top[i] - this->gameScreenVars.viewY);
            PD::setColor(3);
            PD::drawFastVLine(i, this->gameScreenVars.scenery.top[i] - this->gameScreenVars.viewY - 1, 1);

        }


        // Bottom

        if (this->gameScreenVars.scenery.top[i] + this->gameScreenVars.scenery.bot[i] <= this->gameScreenVars.viewY + Constants::Screen_Height) {

            PD::setColor(15);
            PD::drawFastVLine(i, this->gameScreenVars.scenery.top[i] + this->gameScreenVars.scenery.bot[i] - this->gameScreenVars.viewY, Constants::Screen_Height * 3);
            PD::setColor(3);
            PD::drawFastVLine(i, this->gameScreenVars.scenery.top[i] + this->gameScreenVars.scenery.bot[i] - this->gameScreenVars.viewY, 1);

        }

    }

}

void Game::renderHUD() {

    PD::setColor(0);
    PD::fillRect(98, 0, 121, 9);
    PD::setColor(7);
    PD::setCursor(181, 2);

    PD::drawBitmap(99, 1, Images::Lives[this->player.getLives() > 0]);
    PD::drawBitmap(107, 1, Images::Lives[this->player.getLives() > 1]);
    PD::drawBitmap(115, 1, Images::Lives[this->player.getLives() > 2]);

    PD::drawBitmap(125, 1, Images::Fuel);
    PD::setColor(4);


    // Rneder fuel left ..
    
    const uint8_t colors[] = { 8, 8, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };

    for (uint8_t i = 0; i < 45; i = i + 3) {

        PD::setColor(5);

        if (i <= (this->player.getFuel() * 3) / 10) {

            if (this->player.getFuel() > 30 || PC::frameCount % 64 < 32) { 

                PD::setColor(colors[i / 3]);

            }

        }

        PD::fillRect(135 + i, 1, 2, 7);

    }


    // Render score ..
    {
        uint8_t digits[6] = {};
        extractDigits(digits, this->gameScreenVars.score);

        uint8_t location = 213;

        for (uint8_t j = 0; j < 6; ++j, location -= 6) {

            PD::drawBitmap(location, 1, Images::Numbers[digits[j]]);

        }

    }

}


void Game::renderEnemies() {

    for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {

        Enemy &enemy = this->enemies.enemies[i];

        if (enemy.getActive()) {

            if (enemy.getX() >= this->gameScreenVars.distance - Constants::Enemy_Max_Width && enemy.getX() < this->gameScreenVars.distance + 220) {

                switch (enemy.getEnemyType()) {

                    case EnemyType::Rocket:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::Rocket);

                        if (enemy.getInFlight()) {
                            PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance + 3, enemy.getY() - this->gameScreenVars.viewY + 16, Images::Flame[PC::frameCount % 16 / 4]);
                        }
                        break;

                    case EnemyType::FuelDepot:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::FuelDepot);
                        break;

                    case EnemyType::GroundPod:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::GroundPod);
                        break;

                    case EnemyType::SurfaceAir:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::SurfaceToAir[static_cast<uint8_t>(enemy.getDirection())]);
                        break;

                    case EnemyType::Mine:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::Mine);
                        break;

                    case EnemyType::City_00:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::City_00);
                        break;

                    case EnemyType::City_01:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::City_01);
                        break;

                    case EnemyType::City_02:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::City_02);
                        break;

                    case EnemyType::FuelCan:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::FuelCan);
                        break;

                    case EnemyType::Eighter:
                    case EnemyType::Circler:
                        PD::drawBitmap(enemy.getX() - this->gameScreenVars.distance, enemy.getY() - this->gameScreenVars.viewY, Images::Eighter[PC::frameCount % 32 / 8]);
                        break;
                        

                }

            }

        }

    }

}


void Game::renderPlayerBullets() {


    // Render player bullets ..
    
    for (Bullet &bullet : bullets.bullets) {
                                
        if (bullet.getActive()) {
                
            if (bullet.getMuzzleIndex() > 1) {

                PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance, bullet.getY() - this->gameScreenVars.viewY, Images::Muzzle[3 - (bullet.getMuzzleIndex() / 2)]);

            }
            else {

                PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance, bullet.getY() - this->gameScreenVars.viewY, Images::Bullet);

            }

        }

    }

}


void Game::renderPlayerBombs() {


    // Render player bombs ..
    
    for (Bullet &bomb : bullets.bombs) {
                                
        if (bomb.getActive()) {
                
            if (bomb.getMuzzleIndex() > 1) {

                PD::drawBitmap(bomb.getX() - this->gameScreenVars.distance, bomb.getY() - this->gameScreenVars.viewY, Images::Muzzle[3 - (bomb.getMuzzleIndex() / 2)]);

            }
            else {

                PD::drawBitmap(bomb.getX() - this->gameScreenVars.distance, bomb.getY() - this->gameScreenVars.viewY, Images::Bomb);

            }

        }

    }

}


void Game::renderEnemyBullets() {


    // Render enemy bullets ..
    
    for (Bullet &bullet : bullets.enemyBullets) {
                                
        if (bullet.getActive()) {
                
            if (bullet.getMuzzleIndex() > 1) {

                PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance - 2, bullet.getY() - this->gameScreenVars.viewY - 2, Images::Muzzle[3 - (bullet.getMuzzleIndex() / 2)]);

            }
            else {

                PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance, bullet.getY() - this->gameScreenVars.viewY, Images::EnemyBullet);

            }

        }

    }

}