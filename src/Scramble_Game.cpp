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
    this->scenery.reset();

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::game() {

    if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) {
        this->scenery.viewY--;
    }

    if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) {
        this->scenery.viewY++;
    }

    if (PC::buttons.pressed(BTN_C)) {

                this->explode(this->scenery.distTravelled + 110, this->scenery.viewY + 88, ExplosionSize::Medium, ExplosionColor::Blue);
    }


    if (PC::buttons.pressed(BTN_A) || PC::buttons.repeat(BTN_A, 1)) {

        this->scenery.moveScenery(2);
        this->scenery.createScenery(218);
        this->scenery.createScenery(219);
        this->scenery.distTravelled = this->scenery.distTravelled + 2;

        for (Enemy &enemy : this->scenery.enemies.enemies) {

            if (enemy.getX() < this->scenery.distTravelled) {

                enemy.setActive(false);

            }

        }

    }


    // Render page ..

    for (uint8_t i = 0; i < 220; i++) {

        // Top 

        if (this->scenery.scenery_Top[i] > this->scenery.viewY && (this->scenery.scenery_Top[i] <= this->scenery.viewY + Constants::Screen_Height)) {

            PD::setColor(5);
            PD::drawFastVLine(i, 0, this->scenery.scenery_Top[i] - this->scenery.viewY);
            PD::setColor(3);
            PD::drawFastVLine(i, this->scenery.scenery_Top[i] - this->scenery.viewY - 1, 1);

        }
// printf("(%i %i) ", i, scenery_Top[i] + scenery_Bot[i] - viewY);

        // Bottom

//        if (this->scenery.scenery_Top[i] + this->scenery.scenery_Bot[i] > this->scenery.viewY && (this->scenery.scenery_Top[i] + this->scenery.scenery_Bot[i] <= this->scenery.viewY + Constants::Screen_Height)) {
        if (this->scenery.scenery_Top[i] + this->scenery.scenery_Bot[i] <= this->scenery.viewY + Constants::Screen_Height) {

            PD::setColor(5);
            PD::drawFastVLine(i, this->scenery.scenery_Top[i] + this->scenery.scenery_Bot[i] - this->scenery.viewY, Constants::Screen_Height);
            PD::setColor(3);
            PD::drawFastVLine(i, this->scenery.scenery_Top[i] + this->scenery.scenery_Bot[i] - this->scenery.viewY, 1);

        }
        // PD::drawPixel(i, scenery_Top[i]);

    }


    for (uint8_t i = 0; i < Constants::Enemy_Count; i++) {

        Enemy &enemy = this->scenery.enemies.enemies[i];

        if (enemy.getActive()) {

            if (enemy.getX() >= this->scenery.distTravelled - 10 && enemy.getX() < this->scenery.distTravelled + 220) {

                PD::drawBitmap(enemy.getX() - this->scenery.distTravelled, enemy.getY() - this->scenery.viewY, Images::Rocket);

            }

        }

    }


    // Render shockwaves and particles ..

    this->renderShockwave(this->scenery.distTravelled, this->scenery.viewY);
    this->renderParticles(this->scenery.distTravelled, this->scenery.viewY);


// printf("\n");
    // PD::setColor(0);
    // PD::fillRect(0, 0, 16, 8);
    // PD::setColor(7);
    // PD::setCursor(0,0);
    // PD::print(viewY);

}
