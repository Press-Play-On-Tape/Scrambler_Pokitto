
#pragma once

#include "Enemy.h"

class Bullets {

    public:

        Bullet bullets[Constants::Player_Bullet_Count];
        Bullet bombs[Constants::Player_Bomb_Count];

    public:
        
        void reset() {

            for (Bullet &bullet : this->bullets) {

                bullet.reset();

            }

            for (Bullet &bullet : this->bombs) {

                bullet.reset();

            }

        }

        uint8_t getInactiveBullet() {

            for (uint8_t i = 0; i < Constants::Player_Bullet_Count; i++) {

                Bullet &bullet = this->bullets[i];

                if (!bullet.getActive()) {

                    return i;

                }

            }

            return Constants::Bullet_None;

        }

        uint8_t getInactiveBomb() {

            for (uint8_t i = 0; i < Constants::Player_Bomb_Count; i++) {

                Bullet &bomb = this->bombs[i];

                if (!bomb.getActive()) {

                    return i;

                }

            }

            return Constants::Bomb_None;

        }
};
