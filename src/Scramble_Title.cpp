#include "Scramble.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title_Init() {

    this->gameState = GameState::Title;
    this->playTheme(Themes::Main);
    // this->gamePlay.setCounter(0);

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::Scenario_Init;

    }         

    if (PC::buttons.pressed(BTN_B)) { 

        uint32_t index = cookie->setLastScore(0);
        this->gameState = GameState::HighScore_Init;

    }         

    if (PC::buttons.pressed(BTN_UP)) {

        this->cookie->sfx--;
        this->cookie->saveCookie();

        if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

            this->muteTheme();
            
        }
        else {

            this->playTheme(Themes::Main);

        }

    }

    if (PC::buttons.pressed(BTN_DOWN)) {

        this->cookie->sfx++;
        this->cookie->saveCookie();

        if (this->cookie->sfx != SoundEffects::Both && this->cookie->sfx != SoundEffects::Music) {

            this->muteTheme();
            
        }
        else {

            this->playTheme(Themes::Main);
            
        }
        
    }


    // Create explosions ..

    if (PC::frameCount % 60 == 0) {

        this->explode(random(6, 210) + this->gameScreenVars.distance, random(62, 62 + 52) + this->gameScreenVars.viewY, static_cast<ExplosionSize>(random(1, 3)), this->gameScreenVars.getColor());

    }


    // Render page ..

    PD::drawBitmap(6, 62, Images::Title);

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
            PD::drawBitmap(186, 164, Images::Sound_Music);
            break;

        case SoundEffects::SFX:
            PD::drawBitmap(186, 164, Images::Sound_SFX);
            break;

        case SoundEffects::Both:
            PD::drawBitmap(186, 164, Images::Sound_Both);
            break;

        default:
            PD::drawBitmap(186, 164, Images::Sound_None);
            break;

    }


    // Render shockwaves and particles ..

    this->renderShockwave(this->gameScreenVars.distance, this->gameScreenVars.viewY);
    this->renderParticles(this->gameScreenVars.distance, this->gameScreenVars.viewY);

}
