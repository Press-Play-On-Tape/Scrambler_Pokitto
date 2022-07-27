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

    switch (this->player.getYDirection()) {

        case Direction::None:

            if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) {

                this->player.decY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->viewY < 70) {
                    this->viewY = this->viewY - 1;
                }

            }

            if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) {

                this->player.incY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->viewY > 176 - 90) {
                    this->viewY = this->viewY + 1;
                }

            }

            break;

        case Direction::Up:

            if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, (this->player.getYDelay() / 2))) {

                if (this->player.getYDelay() == 1) {

                    this->player.decY(2, PC::frameCount);

                    if (this->player.getY() - this->viewY < 70) {
                        this->viewY = this->viewY - 2;
                    }

                }
                else {

                    this->player.decY(1, PC::frameCount);

                    if (this->player.getY() - this->viewY < 70) {
                        this->viewY = this->viewY - 1;
                    }

                }

            }

            else if (PC::buttons.repeat(BTN_UP, 1)) { }

            else if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) {
                
                this->player.incY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->viewY > 176 - 90) {
                    this->viewY = this->viewY + 1;
                }

            }

            else if (this->player.getYDelay() <= Constants::Player_Inertia) {

                if (this->player.getYDelay() == 1) { this->player.setYDelay(2); }

                if (this->player.movePlayerY(PC::frameCount)) {

                    this->player.decY(1, PC::frameCount, this->player.getYDelay() * 2, true);

                    if (this->player.getY() - this->viewY < 70) {
                        this->viewY = this->viewY - 1;
                    }

                }

            }

            break;

        case Direction::Down:

            if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) {

                this->player.decY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->viewY < 70) {
                    this->viewY = this->viewY - 1;
                }

            }

            else if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, (this->player.getYDelay() / 2))) {

                if (this->player.getYDelay() == 1) {

                    this->player.incY(2, PC::frameCount);

                    if (this->player.getY() - this->viewY > 176 - 90) {
                        this->viewY = this->viewY + 2;
                    }

                }
                else {

                    this->player.incY(1, PC::frameCount);

                    if (this->player.getY() - this->viewY > 176 - 90) {
                        this->viewY = this->viewY + 1;
                    }

                }

            }

            else if (PC::buttons.repeat(BTN_DOWN, 1)) { }

            else if (this->player.getYDelay() <= Constants::Player_Inertia) {

                if (this->player.getYDelay() == 1) { this->player.setYDelay(2); }

                if (this->player.movePlayerY(PC::frameCount)) {

                    this->player.incY(1, PC::frameCount, this->player.getYDelay() * 2, true);

                    if (this->player.getY() - this->viewY > 176 - 90) {
                        this->viewY = this->viewY + 1;
                    }

                }

            }

            break;

    }

    if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1) && this->player.getX() > this->distTravelled) {
        this->player.setX(this->player.getX() - 1);
    }

    if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1) && this->player.getX() < this->distTravelled + 220 - Constants::Player_Width) {
        this->player.setX(this->player.getX() + 1);
    }

    if (PC::buttons.pressed(BTN_C)) {

        gameState = GameState::Game_Init;

    }


    if (PC::buttons.pressed(BTN_A)) {

        uint8_t bulletIdx = bullets.getInactiveBullet();

        if (bulletIdx != Constants::Bullet_None) {

            Bullet &bullet = bullets.bullets[bulletIdx];
            bullet.setActive(true);
            bullet.setX(this->player.getX() + Constants::Player_Width);
            bullet.setY(this->player.getY() + 4);
            bullet.setMuzzleIndex(8);
//            bullet.setHitObject(HitObject::None);

            #ifdef SOUNDS
                playSoundEffect(SoundEffect::Laser);
            #endif


        }

    }






                // Process player bullets (graphics) ..

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






    // Has the player collided with the scenery ?

    //PD::setColor(5);
    Rect playerRect = { this->player.getX() - this->distTravelled + 1, this->player.getY() - this->viewY + 1, Constants::Player_Width, Constants::Player_Height };
    //PD::drawRect(playerRect.x, playerRect.y, playerRect.width, playerRect.height );
    // PD::setColor(4);

    if (player.getActive()) {

        for (uint16_t x = this->player.getX() - this->distTravelled + 1; x < this->player.getX() - this->distTravelled + Constants::Player_Width; x = x + 2) {

            Point point;
            point.setX(x);
            point.setY(this->scenery_Top[x] - this->viewY + 1);

            // PD::drawPixel(point.getX(), point.getY());


            if (this->collide(point, playerRect)) {

                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Large, this->gameScreenVars.getColor());
                this->player.setActive(false);
                this->player.setCountdown(1);
                break;

            }

            point.setY(this->scenery_Top[x] + this->scenery_Bot[x] - this->viewY);

            // PD::drawPixel(point.getX(), point.getY());


            if (this->collide(point, playerRect)) {

                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Large, this->gameScreenVars.getColor());
                this->player.setActive(false);
                this->player.setCountdown(1);
                break;

            }



            // ////printf("(%i, %i) ", point.getX(), point.getY());


        }
    // ////printf("\n");

    }









    //if (PC::buttons.pressed(BTN_A) || PC::buttons.repeat(BTN_A, 1)) {

        if (this->player.getMoveScenery()) {

            this->moveScenery(2);
            this->createScenery(218);
            this->createScenery(219);
            this->distTravelled = this->distTravelled + 2;
            this->player.incX(2);

            for (Enemy &enemy : this->enemies.enemies) {

                if (enemy.getX() < this->distTravelled) {

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
// ////printf("(%i %i) ", i, scenery_Top[i] + scenery_Bot[i] - viewY);

        // Bottom

//        if (this->scenery_Top[i] + this->scenery_Bot[i] > this->viewY && (this->scenery_Top[i] + this->scenery_Bot[i] <= this->viewY + Constants::Screen_Height)) {
        if (this->scenery_Top[i] + this->scenery_Bot[i] <= this->viewY + Constants::Screen_Height) {

            PD::setColor(2);
            PD::drawFastVLine(i, this->scenery_Top[i] + this->scenery_Bot[i] - this->viewY, Constants::Screen_Height);
            PD::setColor(3);
            PD::drawFastVLine(i, this->scenery_Top[i] + this->scenery_Bot[i] - this->viewY, 1);

        }
        // PD::drawPixel(i, scenery_Top[i]);

    }


    // Render enemies ..

    for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {

        Enemy &enemy = this->enemies.enemies[i];

        if (enemy.getActive()) {

            if (enemy.getX() >= this->distTravelled - 10 && enemy.getX() < this->distTravelled + 220) {

                PD::drawBitmap(enemy.getX() - this->distTravelled, enemy.getY() - this->viewY, Images::Rocket);

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
                                            
                    if (bullet.getX() > 0) {
                            
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

    Rect bulletRect = bullet.getRect(BulletType::PlayerBullet);

    for (uint16_t x = bulletRect.x; x < bulletRect.x + bulletRect.width; x = x + 2) {

        Point point;
        point.setX(x + this->distTravelled);
        point.setY(this->scenery_Top[x] + 1);
printf("Rect %i,%i,%i,%i, pt %i,%i == ", bulletRect.x, bulletRect.y, bulletRect.width, bulletRect.height, point.getX(), point.getY());

        // PD::drawPixel(point.getX(), point.getY());


        if (this->collide(point, bulletRect)) {

            this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
            bullet.setActive(false);
            break;

        }

        point.setY(this->scenery_Top[x] + this->scenery_Bot[x]);

        // PD::drawPixel(point.getX(), point.getY());


        if (this->collide(point, bulletRect)) {

            this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
            bullet.setActive(false);
            break;

        }

        // ////printf("(%i, %i) ", point.getX(), point.getY());


    }

printf("\n");
}