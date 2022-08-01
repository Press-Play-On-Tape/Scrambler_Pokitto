#include "Scramble.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::scenario_Init() {

    this->gameState = GameState::Scenario;

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::scenario() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::Game_Init;

    }         

    if (PC::buttons.pressed(BTN_B)) { 

        this->gameState = GameState::Title_Init;

    }         


    this->stars.moveY();


    // Render page ..

    this->renderStars(false);

    PD::setColor(6);
    PD::drawBitmap(6, 0, Images::Title);

    PD::setCursor(60, 65);
    PD::print("-- Score Table --");

    PD::drawBitmap(24, 80, Images::Rocket);
    PD::drawBitmap(27, 96, Images::Flame[PC::frameCount % 16 / 4]);
    PD::setCursor(50, 85);
    PD::print(".. 20 Pts");

    PD::drawBitmap(20, 110, Images::Mine);
    PD::setCursor(50, 115);
    PD::print(".. 25 Pts");

    // PD::drawBitmap(16, 110, Images::FuelDepot_Sml);
    // PD::setCursor(50, 115);
    // PD::print(".. 100 Pts");

    PD::drawBitmap(20, 140, Images::GroundPod);
    PD::setCursor(50, 145);
    PD::print(".. 75 Pts");

    PD::drawBitmap(120, 80, Images::Eighter[PC::frameCount % 16 / 4]);
    PD::setCursor(150, 85);
    PD::print(".. 20 Pts");

    PD::drawBitmap(114, 110, Images::SurfaceToAir[PC::frameCount % 128 / 32]);
    PD::setCursor(150, 115);
    PD::print(".. 100 Pts");

    // PD::drawBitmap(120, 140, Images::Mine);
    // PD::setCursor(150, 145);
    // PD::print(".. 25 Pts");

    PD::drawBitmap(114, 140, Images::FuelDepot_Sml);
    PD::setCursor(150, 145);
    PD::print(".. 100 Pts");
    PD::setCursor(150, 154);
    PD::print("    + Fuel");



}
