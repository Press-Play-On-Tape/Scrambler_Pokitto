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

    if (player.getActive()) {

        this->playerActions();

    }
    else {

        if (PC::buttons.pressed(BTN_C)) {

            gameState = GameState::Game_Init;

        }

    }


    // Move bullets and check for collisions ..

    this->movePlayerBullets();
    this->movePlayerBombs();
    this->moveEnemyBullets();


    // Update S2A and rockets ..

    this->redirectSurfaceToAir();
    this->launchRockets();



    // Has the player collided with anything ?

    this->checkPlayerCollision();
    

    // Move scenery ..

    if (this->player.getMoveScenery()) {

        this->moveScenery(2);
        this->createScenery(218);
        this->createScenery(219);
        this->gameScreenVars.distance = this->gameScreenVars.distance + 2;
        this->player.incX(2);

        for (Enemy &enemy : this->enemies.enemies) {

            if (enemy.getX() < this->gameScreenVars.distance - Constants::Enemy_Max_Width) {

                enemy.setActive(false);

            }

        }


        if (PC::frameCount % Constants::Distance == 0) {

            this->gameScreenVars.score++;

        }

    }

    this->player.updateCounter();


    // ----------------------------------------------------------------------------------------------------
    // Render page ..
    // ----------------------------------------------------------------------------------------------------

    this->renderScenery();
    this->renderEnemies();



    // Render player ..
// ////printf("%i,%i\n", this->player.getX() - this->gameScreenVars.distance, this->player.getY() - this->gameScreenVars.viewY);

    if (this->player.getActive()) {
        PD::drawBitmap(this->player.getX() - this->gameScreenVars.distance, this->player.getY() - this->gameScreenVars.viewY, Images::PlayerShip);
    }



    // Render bullets and bombs ..

    this->renderPlayerBullets();
    this->renderPlayerBombs();
    this->renderEnemyBullets();


    // Render shockwaves and particles ..

    this->renderShockwave(this->gameScreenVars.distance, this->gameScreenVars.viewY);
    this->renderParticles(this->gameScreenVars.distance, this->gameScreenVars.viewY);


    // Render HUD ..

    this->renderHUD();

}


void Game::movePlayerBullets() {


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

                if (bullet.getX() - this->gameScreenVars.distance >= 220) {

                    bullet.setActive(false);

                }

            }

            if (bullet.getActive()) checkPlayerBulletCollision(bullet);

        }

    }

}


void Game::movePlayerBombs() {


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

                if (bomb.getY() - this->gameScreenVars.viewY >= 176) {

                    bomb.setActive(false);

                }

            }

            if (bomb.getActive()) checkPlayerBulletCollision(bomb);

        }

    }

}

void Game::moveEnemyBullets() {

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

                if (enemyBullet.getY() - this->gameScreenVars.viewY < -30 || enemyBullet.getY() - this->gameScreenVars.viewY > 220) {

                    enemyBullet.setActive(false);

                }

            }

            if (enemyBullet.getActive()) checkEnemyBulletCollision(enemyBullet);

        }

    }

}


void Game::redirectSurfaceToAir() {


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


            if (random(0, 96) == 0) {

                uint8_t bulletIdx = this->bullets.getInactiveEnemyBullet();

                if (bulletIdx != Constants::Bullet_None) {

                    Bullet &bullet = this->bullets.enemyBullets[bulletIdx];
                    bullet.setActive(true);
                    bullet.setBulletType(BulletType::EnemyBullet);
                    bullet.setMuzzleIndex(8);
                    bullet.setDirection(enemy.getDirection());

                    switch (enemy.getDirection()) {

                        case Direction::Left:
                            bullet.setX(enemy.getX() - 1);
                            bullet.setY(enemy.getY() + 1);
                            break;

                        case Direction::Up:
                            bullet.setX(enemy.getX() + (Constants::SurfaceAir_Width / 2) - 1);
                            bullet.setY(enemy.getY() - 2);
                            break;

                        case Direction::Right:
                            bullet.setX(enemy.getX() + Constants::SurfaceAir_Width - 1);
                            bullet.setY(enemy.getY() + 1);
                            break;

                    }

                    #ifdef SOUNDS
                        playSoundEffect(SoundEffect::Laser);
                    #endif

                }

            }

        }

    }

}


void Game::launchRockets() {


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
                    point.setY(this->gameScreenVars.scenery.top[x - this->gameScreenVars.distance]);


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

}