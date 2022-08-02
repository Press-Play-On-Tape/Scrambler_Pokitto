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
    uint8_t countdown;

    void reset() {

        for (uint8_t i = 0; i < 220; i++) {
            this->top[i] = 880;
            this->bot[i] = 240;
        }

        this->top_Counter = 192;
        this->bot_Counter = 192;
        this->top_Inc = 0;
        this->bot_Inc = 0;
        this->countdown = 0;

    }

};


struct SplashScreenVariables {

    uint8_t counter = 0;
    uint8_t buttonCounter = 20;

};


struct TitleScreenVariables {

    //                         S   C   R   A   M    B    L    E    R
    const uint8_t charsX[9] = {0, 20, 42, 60, 84, 109, 128, 142, 161 };
    const uint8_t charsIdx[9] = { 11, 2, 10, 0, 8, 1, 7, 3, 10 };

    int8_t counter = -3;
    int8_t charsY[9];
    uint8_t charsYCount[9];

    void incLetters() {

        for (uint8_t i = 0; i < 9; i++) {

            if (this->charsYCount[i] < 55) this->charsYCount[i]++;
            this->charsY[i] = Pathways::TitleSeq[this->charsYCount[i]];

        }

    }

    void reset() {

        this->counter = -3;
        
        for (uint8_t i = 0; i < 9; i++) {
            
            this->charsYCount[i] = random(0, 7);
            this->charsY[i] = Pathways::TitleSeq[this->charsYCount[i]];

        }

    }

};


struct GameScreenVars {


    //                            G   A   M   E   O    V    E    R
    const uint8_t charsX[8] =   { 0, 22, 46, 71, 94, 118, 139, 158 };
    const uint8_t charsIdx[8] = { 4,  0,  8,  3,  9,  12,   3,  10 };

    int8_t counter = -3;
    int8_t charsY[8];
    uint8_t charsYCount[8];

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


        // Game Over sequence ..

        this->counter = -3;
        
        for (uint8_t i = 0; i < 8; i++) {
            
            this->charsYCount[i] = random(0, 7);
            this->charsY[i] = Pathways::TitleSeq[this->charsYCount[i]];

        }

    }

    void incLetters() {

        for (uint8_t i = 0; i < 8; i++) {

            if (this->charsYCount[i] < 55) this->charsYCount[i]++;
            this->charsY[i] = Pathways::TitleSeq[this->charsYCount[i]];

        }

    }

};