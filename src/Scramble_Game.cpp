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

                        if (bullet.getActive()) checkPlayerBulletCollision(bullet);

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

                        if (bomb.getActive()) checkPlayerBulletCollision(bomb);

                    }

                }


                // Process enemy bullets ..

                for (Bullet &enemyBullet : bullets.enemyBullets) {
                        
                    if (enemyBullet.getHitCount() > 0) {

                        enemyBullet.incHitCount();

                    }

                    if (enemyBullet.getX() > 0 && enemyBullet.getHitCount() == 0) {

                        if (enemyBullet.getMuzzleIndex() > 0) {

                            enemyBullet.decMuzzleIndex();
                            // enemyBullet.setX(this->player.getX() + (Constants::Player_Width / 2));

                        }
                        else {

                            enemyBullet.move();

                            if (enemyBullet.getY() - this->viewY < -30 || enemyBullet.getY() - this->viewY > 220) {

                                enemyBullet.setActive(false);

                            }

                        }

                        if (enemyBullet.getActive()) checkEnemyBulletCollision(enemyBullet);

                    }

                }

    // Redirect surface to air missiles ..

    for (Enemy &enemy : this->enemies.enemies) {

        if (enemy.getActive() && enemy.getEnemyType() == EnemyType::SurfaceAir) {

            switch (enemy.getX() - this->player.getX()) {

                case -999 ... 30:
                    enemy.setDirection(Direction::Right);
                    break;

                case 31 ... 60:
                    enemy.setDirection(Direction::Up);
                    break;

                default:
                    enemy.setDirection(Direction::Left);
                    break;

            }


            if (random(0, 64) == 0) {

                uint8_t bulletIdx = bullets.getInactiveEnemyBullet();

                if (bulletIdx != Constants::Bullet_None) {

                    Bullet &bullet = bullets.enemyBullets[bulletIdx];
                    bullet.setActive(true);
                    bullet.setBulletType(BulletType::EnemyBullet);
                    bullet.setMuzzleIndex(8);
                    bullet.setDirection(enemy.getDirection());

                    switch (enemy.getDirection()) {

                        case Direction::Left:
                            bullet.setX(enemy.getX() - 2);
                            bullet.setY(enemy.getY() + 2);
                            break;

                        case Direction::Up:
                            bullet.setX(enemy.getX() - 2);
                            bullet.setY(enemy.getY() + 2);
                            break;

                        case Direction::Right:
                            bullet.setX(enemy.getX() + Constants::SurfaceAir_Width - 2);
                            bullet.setY(enemy.getY() + 2);
                            break;

                    }

                    #ifdef SOUNDS
                        playSoundEffect(SoundEffect::Laser);
                    #endif

                }

            }

        }

    }



    // Launch rockets?

    for (Enemy &enemy : this->enemies.enemies) {

        if (enemy.getActive() && enemy.getEnemyType() == EnemyType::Rocket) {

            if (!enemy.getInFlight()) {

                enemy.setSpeed(random(2, 5));
                    
                switch (enemy.getX() - this->player.getX()) {

                    case -999 ... 30:
                        enemy.setInFlight(true);
                        break;

                    case 31 ... 40:
                        enemy.setInFlight(random(0, 16) == 0);
                        break;

                    case 41 ... 50:
                        enemy.setInFlight(random(0, 32) == 0);
                        break;

                    case 51 ... 60:
                        enemy.setInFlight(random(0, 96) == 0);
                        break;

                    case 61 ... 100:
                        enemy.setInFlight(random(0, 256) == 0);
                        break;

                    case 101 ... 150:
                        enemy.setInFlight(random(0, 512) == 0);
                        break;

                    case 151 ... 210:
                        enemy.setInFlight(random(0, 1024) == 0);
                        break;

                }

            }
            else {


                // Move the rocket accoring to the random speed ..

                enemy.setY(enemy.getY() - enemy.getSpeed());


                // Has the rocket hit the ceiling?

                Rect enemyRect = enemy.getRect();

                for (uint16_t x = enemyRect.x; x < enemyRect.x + enemyRect.width; x = x + 2) {

                    Point point;
                    point.setX(x);
                    point.setY(this->scenery_Top[x - this->distTravelled]);


                    // Collide with top ?

                    if (this->collide(point, enemyRect)) {

                        this->explode(enemy.getX() + (Constants::Player_Bullet_Width / 2), enemy.getY() + (Constants::Player_Bullet_Height / 2), ExplosionSize::Small, this->gameScreenVars.getColor());
                        enemy.setActive(false);
                        return;

                    }

                }

            }
            
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

                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Huge, this->gameScreenVars.getColor());
                this->player.setActive(false);
                this->player.setCountdown(1);
                break;

            }

            point.setY(this->scenery_Top[x] + this->scenery_Bot[x]);


            if (this->collide(point, playerRect)) {

                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Huge, this->gameScreenVars.getColor());
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

                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Huge, this->gameScreenVars.getColor());
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


            if (PC::frameCount % Constants::Distance == 0) {

                this->gameScreenVars.score++;

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

    this->renderEnemies();



    // Render player ..
// ////printf("%i,%i\n", this->player.getX() - this->distTravelled, this->player.getY() - this->viewY);

    if (this->player.getActive()) {
        PD::drawBitmap(this->player.getX() - this->distTravelled, this->player.getY() - this->viewY, Images::PlayerShip);
    }



                // Render player bullets ..
                
                for (Bullet &bullet : bullets.bullets) {
                                            
                    if (bullet.getActive()) {
                            
                        if (bullet.getMuzzleIndex() > 1) {

                            PD::drawBitmap(bullet.getX() - this->distTravelled, bullet.getY() - this->viewY, Images::Muzzle[3 - (bullet.getMuzzleIndex() / 2)]);

                        }
                        else {

                            switch (bullet.getHitCount()) {

                                case 0:
                                    PD::drawBitmap(bullet.getX() - this->distTravelled, bullet.getY() - this->viewY, Images::Bullet);
                                    break;

                                default:

                                    PD::drawBitmap(bullet.getX() - this->distTravelled, bullet.getY() - this->viewY - 5, Images::Hit[bullet.getHitCount() - 1]);
                                    break;

                            }

                        }

                    }

                }


                // Render player bombs ..
                
                for (Bullet &bomb : bullets.bombs) {
                                            
                    if (bomb.getActive()) {
                            
                        if (bomb.getMuzzleIndex() > 1) {

                            PD::drawBitmap(bomb.getX() - this->distTravelled, bomb.getY() - this->viewY, Images::Muzzle[3 - (bomb.getMuzzleIndex() / 2)]);

                        }
                        else {

                            switch (bomb.getHitCount()) {

                                case 0:
                                    PD::drawBitmap(bomb.getX() - this->distTravelled, bomb.getY() - this->viewY, Images::Bomb);
                                    break;

                                default:

                                    PD::drawBitmap(bomb.getX() - this->distTravelled, bomb.getY() - this->viewY - 5, Images::Hit[bomb.getHitCount() - 1]);
                                    break;

                            }

                        }

                    }

                }


                // Render enemy bullets ..
                
                for (Bullet &bullet : bullets.enemyBullets) {
                                            
                    if (bullet.getActive()) {
                            
                        if (bullet.getMuzzleIndex() > 1) {

                            PD::drawBitmap(bullet.getX() - this->distTravelled, bullet.getY() - this->viewY, Images::Muzzle[3 - (bullet.getMuzzleIndex() / 2)]);

                        }
                        else {

                            switch (bullet.getHitCount()) {

                                case 0:
                                    PD::drawBitmap(bullet.getX() - this->distTravelled, bullet.getY() - this->viewY, Images::EnemyBullet);
                                    break;

                                default:
                                    PD::drawBitmap(bullet.getX() - this->distTravelled, bullet.getY() - this->viewY - 5, Images::Hit[bullet.getHitCount() - 1]);
                                    break;

                            }

                        }

                    }

                }


    // Render shockwaves and particles ..

    this->renderShockwave(this->distTravelled, this->viewY);
    this->renderParticles(this->distTravelled, this->viewY);


    // Render HUD ..

    this->renderHUD();


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

            if (enemy.getX() >= this->distTravelled - Constants::Enemy_Max_Width && enemy.getX() < this->distTravelled + 220) {

                switch (enemy.getEnemyType()) {

                    case EnemyType::Rocket:
                        PD::drawBitmap(enemy.getX() - this->distTravelled, enemy.getY() - this->viewY, Images::Rocket);
                        break;

                    case EnemyType::FuelDepot:
                        PD::drawBitmap(enemy.getX() - this->distTravelled, enemy.getY() - this->viewY, Images::FuelDepot);
                        break;

                    case EnemyType::GroundPod:
                        PD::drawBitmap(enemy.getX() - this->distTravelled, enemy.getY() - this->viewY, Images::GroundPod);
                        break;

                    case EnemyType::SurfaceAir:
                        PD::drawBitmap(enemy.getX() - this->distTravelled, enemy.getY() - this->viewY, Images::SurfaceToAir[static_cast<uint8_t>(enemy.getDirection())]);
                        break;
                        

                }

            }

        }

    }

}