#include "Scramble.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::setup(GameCookie *cookie) {

    this->cookie = cookie;

}

void Game::loop() {

    PD::clear();
    PC::buttons.pollButtons();

    switch (this->gameState) {

        case GameState::Splash:
            this->splashScreen();
            break;

        case GameState::Title_Init:
            this->title_Init();
            [[fallthrough]]

        case GameState::Title:
            this->title();
            break;

        case GameState::Game_Init:
            this->game_Init();
            [[fallthrough]]

        case GameState::Game:
            this->game();
            break;

    }

}
