#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct SplashScreenVariables {

    uint8_t counter = 0;
    uint8_t buttonCounter = 0;

};



struct GameScreenVars {

    int8_t xOffset = 0;
    int8_t yOffset = 0;
    uint8_t offsetCount = 0;
    uint8_t scoreIndex = 0;
    uint8_t clearScores = 0;
    uint8_t healthCounter = 0;
    uint8_t highScoreCounter = 0;
    uint16_t score = 0;
    uint16_t distance = 0;

    ExplosionColor explosionColor = ExplosionColor::Blue;

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

    void decHealthCounter() {

        this->healthCounter--;

    }

    void resetHealthCounter() {

        this->healthCounter = 15 + random(25);

    }

    void reset() {

        this->xOffset = 0;
        this->yOffset = 0;
        this->offsetCount = 0;
        this->scoreIndex = 0;
        this->clearScores = 0;
        this->score = 0;
        this->distance = 0;
        this->highScoreCounter = 0;

        this->resetHealthCounter();

    }

};