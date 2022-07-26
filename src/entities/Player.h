#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"

class Player : public Point {

    private:

        uint8_t health = 0;
        uint8_t countdown = 0;

    public:

        uint8_t getHealth()                     { return this->health; }
        uint8_t getCountdown()                  { return this->countdown; }

        void setHealth(uint8_t val)             { this->health = val; }
        void setCountdown(uint8_t val)          { this->countdown = val; }

    public:

        void incX(uint8_t inc) {

            this->setX(this->getX() + inc);

        }

        void incY(uint8_t inc) {

            this->setY(this->getY() + inc);

        }

        void decY(uint8_t inc) {

            this->setY(this->getY() - inc);

        }

        void reset() {

            this->setActive(true);
            this->setX(40);
            this->setY(1030);
            
        }

};
