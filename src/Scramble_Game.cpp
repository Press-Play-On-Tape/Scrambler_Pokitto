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

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::game() {

    if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) {
//        this->viewY++;
this->player.decY(2);
if (this->player.getY() - this->viewY < 70) {
    this->viewY = this->viewY- 2;
}
    }

    if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) {
//        this->viewY--;
this->player.incY(2);
if (this->player.getY() - this->viewY > 188 - 100) {
    this->viewY = this->viewY + 2;
}
    }

    if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1) && this->player.getX() > this->distTravelled) {
        this->player.setX(this->player.getX() - 1);
    }

    if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1) && this->player.getX() < this->distTravelled + 220 - Constants::Player_Width) {
        this->player.setX(this->player.getX() + 1);
    }

    if (PC::buttons.pressed(BTN_C)) {

        this->explode(this->distTravelled + 110, this->viewY + 88, ExplosionSize::Medium, ExplosionColor::Blue);

    }


    //if (PC::buttons.pressed(BTN_A) || PC::buttons.repeat(BTN_A, 1)) {

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

    //}


    // Render page ..

    for (uint8_t i = 0; i < 220; i++) {

        // Top 

        if (this->scenery_Top[i] > this->viewY && (this->scenery_Top[i] <= this->viewY + Constants::Screen_Height)) {

            PD::setColor(5);
            PD::drawFastVLine(i, 0, this->scenery_Top[i] - this->viewY);
            PD::setColor(3);
            PD::drawFastVLine(i, this->scenery_Top[i] - this->viewY - 1, 1);

        }
// printf("(%i %i) ", i, scenery_Top[i] + scenery_Bot[i] - viewY);

        // Bottom

//        if (this->scenery_Top[i] + this->scenery_Bot[i] > this->viewY && (this->scenery_Top[i] + this->scenery_Bot[i] <= this->viewY + Constants::Screen_Height)) {
        if (this->scenery_Top[i] + this->scenery_Bot[i] <= this->viewY + Constants::Screen_Height) {

            PD::setColor(5);
            PD::drawFastVLine(i, this->scenery_Top[i] + this->scenery_Bot[i] - this->viewY, Constants::Screen_Height);
            PD::setColor(3);
            PD::drawFastVLine(i, this->scenery_Top[i] + this->scenery_Bot[i] - this->viewY, 1);

        }
        // PD::drawPixel(i, scenery_Top[i]);

    }


    for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {

        Enemy &enemy = this->enemies.enemies[i];

        if (enemy.getActive()) {

            if (enemy.getX() >= this->distTravelled - 10 && enemy.getX() < this->distTravelled + 220) {

                PD::drawBitmap(enemy.getX() - this->distTravelled, enemy.getY() - this->viewY, Images::Rocket);

            }

        }

    }



    // Render player ..
// printf("%i,%i\n", this->player.getX() - this->distTravelled, this->player.getY() - this->viewY);

    if (this->player.getActive()) {
        PD::drawBitmap(this->player.getX() - this->distTravelled, this->player.getY() - this->viewY, Images::PlayerShip);
    }



    // Render shockwaves and particles ..

    this->renderShockwave(this->distTravelled, this->viewY);
    this->renderParticles(this->distTravelled, this->viewY);


// printf("\n");
    // PD::setColor(0);
    // PD::fillRect(0, 0, 16, 8);
    // PD::setColor(7);
    // PD::setCursor(0,0);
    // PD::print(viewY);








    // Has the player collided with the scenery ?

    //PD::setColor(5);
    Rect playerRect = { this->player.getX() - this->distTravelled + 1, this->player.getY() - this->viewY + 1, Constants::Player_Width, Constants::Player_Height };
    //PD::drawRect(playerRect.x, playerRect.y, playerRect.width, playerRect.height );
    PD::setColor(4);

    if (player.getActive()) {

        for (uint16_t x = this->player.getX() - this->distTravelled + 1; x < this->player.getX() - this->distTravelled + Constants::Player_Width; x = x + 2) {

            Point point;
            point.setX(x);
            point.setY(this->scenery_Top[x] - this->viewY + 1);

            PD::drawPixel(point.getX(), point.getY());


            if (this->collide(point, playerRect)) {

                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Large, ExplosionColor::Blue);
                this->player.setActive(false);
                break;

            }

            point.setY(this->scenery_Top[x] + this->scenery_Bot[x] - this->viewY);

            PD::drawPixel(point.getX(), point.getY());


            if (this->collide(point, playerRect)) {

                this->explode(this->player.getX() + (Constants::Player_Width / 2), this->player.getY() + (Constants::Player_Height / 2), ExplosionSize::Large, ExplosionColor::Blue);
                this->player.setActive(false);
                break;

            }



            // printf("(%i, %i) ", point.getX(), point.getY());


        }
    // printf("\n");

    }






}
