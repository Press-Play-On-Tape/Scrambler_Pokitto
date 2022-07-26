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
        GameCookie *cookie;

        File mainThemeFile;      

        Particles particles;
        Shockwaves shockwaves;
        Player player;




        int8_t scenery_Top_Inc;
        uint8_t scenery_Top_Counter;
        int8_t scenery_Bottom_Inc;
        uint8_t scenery_Bottom_Counter;
        int16_t scenery_Top[220];
        uint8_t scenery_Bot[220];

        int16_t viewY = 980;
        uint16_t distTravelled = 0;

        Enemies enemies;




    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void splashScreen();
        void title_Init();
        void title();
        void game_Init();
        void game();


        bool collide(Rect rect1, Rect rect2);
        bool collide(Point point, Rect rect);


        // Music and sounds ..

        void playTheme(Themes theme);
        void muteTheme();
        void playSoundEffect(SoundEffect soundEffect);


        // Scenery ..

        void launchEnemy(EnemyType enemyType, uint16_t x, int16_t y);
        void createScenery(uint8_t x);
        void moveScenery(uint8_t x);
        void resetScenery();


        // Explosions ..

        void explode(int16_t x, int16_t y, ExplosionSize explosionSize, ExplosionColor color);
        void createShockwave(int16_t x, int16_t y, uint8_t maxRadius);
        void renderShockwave(uint16_t distTravelled, int16_t viewY);
        void renderParticles(uint16_t distTravelled, int16_t viewY);
        float getRandomFloat(int8_t min, int8_t max);
        uint8_t getBlueShade(uint8_t page);
        uint8_t getRedShade(uint8_t page);

};

