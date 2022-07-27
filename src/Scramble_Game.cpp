#include "Scramble.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;



// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::game_Init() {

    this->gameState = GameState::Game;
    // this->playTheme(Themes::Main);
    // this->gamePlay.setCounter(0);
    this->resetScenery();
    this->player.reset();
    this->enemies.reset();
    this->bullets.reset();
    this->gameScreenVars.reset();

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//

void Game::game() {


    // Process player actions ..

    this->playerActions();




                // Process player bullets ..

                for (Bullet &bullet : bullets.bullets) {
                        
                    if (bullet.getHitCount() > 0) {

                        bullet.incHitCount();

                    }

                    if (bullet.getX() > 0 && bullet.getHitCount() == 0) {

                        if (bullet.getMuzzleIndex() > 0) {

                            bullet.decMuzzleIndex();
                            bullet.setX(this->player.getX() + Constants::Player_Width);

                        }
                        else {

                            bullet.setX(bullet.getX() + 6);

                            if (bullet.getX() - this->distTravelled >= 220) {

                                bullet.setActive(false);

                            }

                        }

                        if (bullet.getActive()) checkBulletCollision(bullet);

                    }

                }



                // Process player bombs ..

                for (Bullet &bomb : bullets.bombs) {
                        
                    if (bomb.getHitCount() > 0) {

                        bomb.incHitCount();

                    }

                    if (bomb.getX() > 0 && bomb.getHitCount() == 0) {

                        if (bomb.getMuzzleIndex() > 0) {

                            bomb.decMuzzleIndex();
                            bomb.setX(this->player.getX() + (Constants::Player_Width / 2));

                        }
                        else {

                            bomb.move();

                            if (bomb.getY() - this->viewY >= 176) {

                                bomb.setActive(false);

                            }

                        }

                        if (bomb.getActive()) checkBulletCollision(bomb);

                    }

                }






    // Has the player collided with the scenery ?

//    Rect playerRect = { this->player.getX() - this->distTravelled + 1, this->player.getY() - this->viewY + 1, Constants::Player_Width, Constants::Player_Height };
    Rect playerRect = { this->player.getX() + 1, this->player.getY() + 1, Constants::Player_Width, Constants::Player_Height };

    if (player.getActive()) {

        for (uint16_t x = this->player.getX() - this->distTravelled + 1; x < this->player.getX() - this->distTravelled + Constants::Player_Width; x = x + 2) {

            Point point;
            // point.setX(x);
//            point.setY(this->scenery_Top[x] - this->viewY + 1);
            point.setX(x + this->distTravelled);
            point.setY(this->scenery_Top[x]);

            // PD::drawPixel(point.getX(), point.getY());


            if (this->collide(point, playerRect)) {

                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Large, this->gameScreenVars.getColor());
                this->player.setActive(false);
                this->player.setCountdown(1);
                break;

            }

            point.setY(this->scenery_Top[x] + this->scenery_Bot[x]);


            if (this->collide(point, playerRect)) {

                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Large, this->gameScreenVars.getColor());
                this->player.setActive(false);
                this->player.setCountdown(1);
                break;

            }

        }

    }


    // Has the player collided with an enemy?

    for (Enemy &enemy : this->enemies.enemies) {

        if (enemy.getActive()) {

            Rect enemyRect = enemy.getRect();

            if (collide(enemyRect, playerRect)) {

                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Large, this->gameScreenVars.getColor());
                this->player.setActive(false);
                enemy.setActive(false);
                this->player.setCountdown(1);
                break;

            }

        }

    }









    //if (PC::buttons.pressed(BTN_A) || PC::buttons.repeat(BTN_A, 1)) {

        if (this->player.getMoveScenery()) {

            this->moveScenery(2);
            this->createScenery(218);
            this->createScenery(219);
            this->distTravelled = this->distTravelled + 2;
            this->player.incX(2);

            for (Enemy &enemy : this->enemies.enemies) {

                if (enemy.getX() < this->distTravelled - Constants::Enemy_Max_Width) {

                    enemy.setActive(false);

                }

            }

        }

        this->player.updateCounter();

    //}


    // Render page ..

    for (uint8_t i = 0; i < 220; i++) {


        // Top 

        if (this->scenery_Top[i] > this->viewY && (this->scenery_Top[i] <= this->viewY + Constants::Screen_Height)) {

            PD::setColor(2);
            PD::drawFastVLine(i, 0, this->scenery_Top[i] - this->viewY);
            PD::setColor(3);
            PD::drawFastVLine(i, this->scenery_Top[i] - this->viewY - 1, 1);

        }


        // Bottom

        if (this->scenery_Top[i] + this->scenery_Bot[i] <= this->viewY + Constants::Screen_Height) {

            PD::setColor(1);
            PD::drawFastVLine(i, this->scenery_Top[i] + this->scenery_Bot[i] - this->viewY, Constants::Screen_Height * 3);
            PD::setColor(3);
            PD::drawFastVLine(i, this->scenery_Top[i] + this->scenery_Bot[i] - this->viewY, 1);

        }

    }


    // Render enemies ..

    for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {

        Enemy &enemy = this->enemies.enemies[i];

        if (enemy.getActive()) {

            if (enemy.getX() >= this->distTravelled - Constants::Enemy_Max_Width && enemy.getX() < this->distTravelled + 220) {

                switch (enemy.getEnemyType()) {

                    case EnemyType::Rocket:
                        PD::drawBitmap(enemy.getX() - this->distTravelled, enemy.getY() - this->viewY, Images::Rocket);
                        break;

                    case EnemyType::FuelDepot:
                        PD::drawBitmap(enemy.getX() - this->distTravelled, enemy.getY() - this->viewY, Images::FuelDepot);
                        break;
                        

                }

            }

        }

    }



    // Render player ..
// ////printf("%i,%i\n", this->player.getX() - this->distTravelled, this->player.getY() - this->viewY);

    if (this->player.getActive()) {
        PD::drawBitmap(this->player.getX() - this->distTravelled, this->player.getY() - this->viewY, Images::PlayerShip);
    }



                // Render player bullets ..
                
                for (Bullet &bullet : bullets.bullets) {
                                            
                    if (bullet.getActive()) {
                            
                        if (bullet.getMuzzleIndex() > 1) {

                            PD::drawBitmap(bullet.getX() - this->distTravelled + this->gameScreenVars.xOffset, bullet.getY() - this->viewY + this->gameScreenVars.yOffset, Images::Muzzle[3 - (bullet.getMuzzleIndex() / 2)]);

                        }
                        else {

                            switch (bullet.getHitCount()) {

                                case 0:
                                    PD::drawBitmap(bullet.getX() - this->distTravelled + this->gameScreenVars.xOffset, bullet.getY() - this->viewY + this->gameScreenVars.yOffset, Images::Bullet);
                                    break;

                                default:

                                    PD::drawBitmap(bullet.getX() - this->distTravelled + this->gameScreenVars.xOffset, bullet.getY() - this->viewY - 5 + this->gameScreenVars.yOffset, Images::Hit[bullet.getHitCount() - 1]);
                                    break;

                            }

                        }

                    }

                }


                // Render player bombs ..
                
                for (Bullet &bomb : bullets.bombs) {
                                            
                    if (bomb.getActive()) {
                            
                        if (bomb.getMuzzleIndex() > 1) {

                            PD::drawBitmap(bomb.getX() - this->distTravelled + this->gameScreenVars.xOffset, bomb.getY() - this->viewY + this->gameScreenVars.yOffset, Images::Muzzle[3 - (bomb.getMuzzleIndex() / 2)]);

                        }
                        else {

                            switch (bomb.getHitCount()) {

                                case 0:
                                    PD::drawBitmap(bomb.getX() - this->distTravelled + this->gameScreenVars.xOffset, bomb.getY() - this->viewY + this->gameScreenVars.yOffset, Images::Bomb);
                                    break;

                                default:

                                    PD::drawBitmap(bomb.getX() - this->distTravelled + this->gameScreenVars.xOffset, bomb.getY() - this->viewY - 5 + this->gameScreenVars.yOffset, Images::Hit[bomb.getHitCount() - 1]);
                                    break;

                            }

                        }

                    }

                }


    // Render shockwaves and particles ..

    this->renderShockwave(this->distTravelled, this->viewY);
    this->renderParticles(this->distTravelled, this->viewY);


// ////printf("\n");
    // PD::setColor(0);
    // PD::fillRect(0, 0, 16, 8);
    // PD::setColor(7);
    // PD::setCursor(0,0);
    // PD::print(viewY);









}



void Game::checkBulletCollision(Bullet &bullet) {

    Rect bulletRect = bullet.getRect();


    // Collide with scenery?

    for (uint16_t x = bulletRect.x; x < bulletRect.x + bulletRect.width; x = x + 2) {

        Point point;
        point.setX(x);
        point.setY(this->scenery_Top[x - this->distTravelled]);


        // Collide with top ?

        if (this->collide(point, bulletRect)) {

            this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
            bullet.setActive(false);
            return;

        }


        // Collide with bottom ?

        point.setY(this->scenery_Top[x - this->distTravelled] + this->scenery_Bot[x - this->distTravelled]);

        if (this->collide(point, bulletRect)) {

            this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
            bullet.setActive(false);
            return;

        }

    }


    // Collide with enemy?

    for (Enemy &enemy : this->enemies.enemies) {

        if (enemy.getActive()) {

            Rect enemyRect = enemy.getRect();

            if (this->collide(enemyRect, bulletRect)) {

                this->explode(bullet.getX() + (Constants::Player_Bullet_Width / 2), bullet.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Medium, this->gameScreenVars.getColor());
                enemy.setActive(false);
                bullet.setActive(false);
                return;

            }

        }

    }

}