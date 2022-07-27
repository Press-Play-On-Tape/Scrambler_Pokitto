#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "Rect.h"

class Enemy : public Point {

    private:

        bool inFlight = false;
        uint8_t speed = 0;
        Direction direction = Direction::Left;
        EnemyType enemyType = EnemyType::Rocket;


    public:

        bool getInFlight()                      { return this->inFlight; }
        uint8_t getSpeed()                      { return this->speed; }
        Direction getDirection()                { return this->direction; }
        EnemyType getEnemyType()                { return this->enemyType; }

        void setInFlight(bool val)              { this->inFlight = val; }
        void setSpeed(uint8_t val)              { this->speed = val; }
        void setDirection(Direction val)        { this->direction = val; }
        void setEnemyType(EnemyType val)        { this->enemyType = val; }


    public:

        void setActive(bool val) {

            if (!val) {
                this->inFlight = false;
                this->direction = Direction::Left;
            }

            Point::setActive(val);

        }

        void reset() {

            this->setActive(false);
            this->inFlight = false;
            
        }

        Rect getRect() {

            Rect rect;

            switch (this->enemyType) {

                case EnemyType::Rocket:
                    rect.x = this->getX() + 1;
                    rect.y = this->getY() + 1;
                    rect.width = Constants::Rocket_Width;
                    rect.height = Constants::Rocket_Height;
                    return rect;

                case EnemyType::FuelDepot:
                    rect.x = this->getX() + 1;
                    rect.y = this->getY() + 1;
                    rect.width = Constants::FuelDepot_Width;
                    rect.height = Constants::FuelDepot_Height;
                    return rect;

                case EnemyType::GroundPod:
                    rect.x = this->getX() + 1;
                    rect.y = this->getY() + 1;
                    rect.width = Constants::GroundPod_Width;
                    rect.height = Constants::GroundPod_Height;
                    return rect;

                case EnemyType::SurfaceAir:

                    switch (this->direction) { //15x15

                        case Direction::Left:
                            rect.x = this->getX() + 1;
                            rect.y = this->getY() + 3;
                            rect.width = 15;
                            rect.height = 16;
                            break;

                        case Direction::Up:
                            rect.x = this->getX() + 5;
                            rect.y = this->getY() + 1;
                            rect.width = 15;
                            rect.height = 18;
                            break;

                        case Direction::Right:
                            rect.x = this->getX() + 9;
                            rect.y = this->getY() + 3;
                            rect.width = 15;
                            rect.height = 16;
                            break;

                    }

                    return rect;

                default:
                    return rect;
                    
            }

        }

};
