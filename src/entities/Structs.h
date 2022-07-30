#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"


struct Scenery {

    int8_t top_Inc;
    int8_t bot_Inc;
    uint8_t top_Counter;
    uint8_t bot_Counter;
    int16_t top[220];
    uint8_t bot[220];
    uint8_t rand;

    void reset() {

        for (uint8_t i = 0; i < 220; i++) {
            this->top[i] = 880;
            this->bot[i] = 240;
        }

        this->top_Counter = 192;
        this->bot_Counter = 192;
        this->top_Inc = 0;
        this->bot_Inc = 0;

    }

};


struct SplashScreenVariables {

    uint8_t counter = 0;
    uint8_t buttonCounter = 20;

};


struct GameScreenVars {

    uint8_t clearScores = 0;
    uint32_t score = 0;
    int16_t viewY = 980;
    uint32_t distance = 0;
    uint8_t countdown = 0;

    ExplosionColor explosionColor = ExplosionColor::Blue;
    Scenery scenery;

    ExplosionColor getColor() {

        switch (this->explosionColor) {

            case ExplosionColor::Blue:
                this->explosionColor = ExplosionColor::Red;
                break;

            case ExplosionColor::Red:
                this->explosionColor = ExplosionColor::Blue;
                break;
                
        }

        return this->explosionColor;

    }

    void reset(bool startOfGame) {

        this->clearScores = 0;
        this->viewY = 980;
        this->distance = 0;
        this->countdown = (32 * 4) - 1;
        this->scenery.reset();

        if (startOfGame) {
    
            this->score = 0;

        }

    }

};