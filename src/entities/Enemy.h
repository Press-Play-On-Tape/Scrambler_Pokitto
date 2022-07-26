#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"

class Enemy : public Point {

    public:

        EnemyType enemyType = EnemyType::Rocket;

        void reset() {

            this->setActive(false);
            
        }

};
