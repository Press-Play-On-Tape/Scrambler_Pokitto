#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "Rect.h"

class Enemy : public Point {

    private:

        EnemyType enemyType = EnemyType::Rocket;


    public:

        EnemyType getEnemyType()                { return this->enemyType; }

        void setEnemyType(EnemyType val)        { this->enemyType = val; }


    public:

        void reset() {

            this->setActive(false);
            
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

                default:
                    return rect;
                    
            }

        }

};
