#pragma once

#include "Pokitto.h"
#include <LibAudio>
//#include <LibSchedule>
#include "entities/Entities.h"
#include "images/Images.h"
#include "utils/Enums.h"
#include "utils/GameCookie.h"
//#include "music/Music.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;


class Game {

    private:

        SplashScreenVariables splashScreenVariables;
        GameState gameState = GameState::Splash;
        // GameState nextGameState;
        // GamePlay gamePlay;
        GameCookie *cookie;

        File mainThemeFile;      

        Scenery scenery;

        Particles particles;
        Shockwaves shockwaves;


    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void splashScreen();
        void title_Init();
        void title();
        void game_Init();
        void game();

        void playTheme(Themes theme);
        void muteTheme();
        void playSoundEffect(SoundEffect soundEffect);


        // Explosions ..

        void explode(int16_t x, int16_t y, ExplosionSize explosionSize, ExplosionColor color);
        void createShockwave(int16_t x, int16_t y, uint8_t maxRadius);
        void renderShockwave(uint16_t distTravelled, int16_t viewY);
        void renderParticles(uint16_t distTravelled, int16_t viewY);
        float getRandomFloat(int8_t min, int8_t max);
        uint8_t getBlueShade(uint8_t page);
        uint8_t getRedShade(uint8_t page);

};

