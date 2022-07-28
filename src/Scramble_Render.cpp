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
    PD::fillRect(180, 0, 40, 12);
    PD::setColor(7);
    PD::setCursor(181, 2);

    {
        uint8_t digits[6] = {};
        extractDigits(digits, this->gameScreenVars.score);

        uint8_t location = 212;

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

                switch (bullet.getHitCount()) {

                    case 0:
                        PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance, bullet.getY() - this->gameScreenVars.viewY, Images::Bullet);
                        break;

                    default:

                        PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance, bullet.getY() - this->gameScreenVars.viewY - 5, Images::Hit[bullet.getHitCount() - 1]);
                        break;

                }

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

                switch (bomb.getHitCount()) {

                    case 0:
                        PD::drawBitmap(bomb.getX() - this->gameScreenVars.distance, bomb.getY() - this->gameScreenVars.viewY, Images::Bomb);
                        break;

                    default:

                        PD::drawBitmap(bomb.getX() - this->gameScreenVars.distance, bomb.getY() - this->gameScreenVars.viewY - 5, Images::Hit[bomb.getHitCount() - 1]);
                        break;

                }

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

                switch (bullet.getHitCount()) {

                    case 0:
                        PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance, bullet.getY() - this->gameScreenVars.viewY, Images::EnemyBullet);
                        break;

                    default:
                        PD::drawBitmap(bullet.getX() - this->gameScreenVars.distance, bullet.getY() - this->gameScreenVars.viewY - 5, Images::Hit[bullet.getHitCount() - 1]);
                        break;

                }

            }

        }

    }

}