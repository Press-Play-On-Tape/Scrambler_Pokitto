#include "Scramble.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::playTheme(Themes theme) {

    #ifdef SOUNDS

    constexpr char themes[2][19] = { "music/Regic_01.raw", "music/Regic_02.raw" };

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
        case SoundEffects::Both:

            if (this->mainThemeFile.openRO(themes[static_cast<uint8_t>(theme)])) {
                auto& music = Audio::play<0>(this->mainThemeFile);
                music.setLoop(true);
            }

            break;

        case SoundEffects::SFX:
        case SoundEffects::None:

            this->muteTheme();

    }

    #endif

}

void Game::muteTheme() {

    #ifdef SOUNDS
    Audio::stop<0>();
    #endif

}


void Game::playSoundEffect(SoundEffect soundEffect) {

    #ifdef SOUNDS

    switch (this->cookie->sfx) {

        case SoundEffects::SFX:
        case SoundEffects::Both:
                
            switch (soundEffect) {
                
                case SoundEffect::Deal: 
                    //Audio::play<1>(Sounds::sfx_Tone_00);    
                    break;
                
                case SoundEffect::EnemyDeath: 
                    //Audio::play<1>(Sounds::sfx_Tone_01);    
                    break;

            }

            break;

        default: break;
        
    }  

    #endif

}    
