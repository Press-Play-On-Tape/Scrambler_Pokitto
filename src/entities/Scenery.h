#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "Enemies.h"

class Scenery {

    public:

        int8_t scenery_Top_Inc;
        uint8_t scenery_Top_Counter;
        int8_t scenery_Bottom_Inc;
        uint8_t scenery_Bottom_Counter;
        int16_t scenery_Top[220];
        uint8_t scenery_Bot[220];

        int16_t viewY = 980;
        uint16_t distTravelled = 0;

        Enemies enemies;

    private:

        void launchEnemy(EnemyType enemyType, uint16_t x, int16_t y) {

            uint8_t idx = this->enemies.getInactiveEnemy();
            Enemy &enemy = this->enemies.enemies[idx];

            enemy.enemyType = enemyType;
            enemy.setX(x);
            enemy.setActive(true);


            switch (enemyType) {

                case EnemyType::Rocket:
                    enemy.setY(y - Constants::Rocket_Height);
                    break;

            }

            printf("One Rocket %i, %i, %i - %i, %i\n", this->scenery_Top[217]  ,  scenery_Top_Inc , this->scenery_Bot[217], enemy.getX(), enemy.getY());

        }

    public:

        void createScenery(uint8_t x) {

            if (this->scenery_Top_Counter > 0) {

                this->scenery_Top[x] = this->scenery_Top[x - 1] + this->scenery_Top_Inc;
                this->scenery_Top_Counter--;

            }
            else {

                if (this->scenery_Top[x] > Constants::Scenery_Top) {

                    this->scenery_Top_Inc = (random(0, 5) - 2);       

                    if (this->scenery_Top_Inc == 0) {

                        this->scenery_Top_Counter = random(1, 3);

                    }
                    else {
                        
                        this->scenery_Top_Counter = random(2, 5);

                    }

                }
                else {

                    this->scenery_Top_Inc = random(0, 3);       

                    if (this->scenery_Top_Inc == 0) {

                        this->scenery_Top_Counter = random(1, 3);

                    }
                    else {
                        
                        this->scenery_Top_Counter = random(3, 7);

                    }

                }

                this->scenery_Top[x] = this->scenery_Top[x - 1] + this->scenery_Top_Inc;
                this->scenery_Top_Counter--;         

            }


            // Bottom ..

            int16_t enemyLaunch = this->scenery_Top[x - 1] + this->scenery_Bot[x - 1];// + scenery_Top_Inc;

            if (this->scenery_Bottom_Counter > 0) {

                this->scenery_Bot[x] = this->scenery_Bot[x - 1] - scenery_Top_Inc + this->scenery_Bottom_Inc;
                this->scenery_Bottom_Counter--;

            }
            else {

                switch (this->scenery_Bot[x]) {

                    case Constants::Scenery_DistanceBetween_Min_Start ... Constants::Scenery_DistanceBetween_Min_End:

                        this->scenery_Bottom_Inc = random(0, 3);       

                        if (this->scenery_Bottom_Inc == 0) {

                            this->scenery_Bottom_Counter = random(1, 3);

                        }
                        else {
                            
                            this->scenery_Bottom_Counter = random(3, 7);

                        }

                        break;

                    case Constants::Scenery_DistanceBetween_Normal_Start ... Constants::Scenery_DistanceBetween_Normal_End:
                        {

                            uint8_t activeEnemies = this->enemies.getInactiveEnemyCount();
                            uint8_t randomEnemy = random(0, Constants::LaunchEnemy_Max + 1);

                            switch (randomEnemy) {

                                case Constants::LaunchEnemy_Start ... Constants::LaunchEnemy_Nothing:
                                    break;

                                case Constants::LaunchEnemy_OneRocket_Start ... Constants::LaunchEnemy_OneRocket_End:
                                    if (activeEnemies == 0) {
                                        randomEnemy = Constants::LaunchEnemy_Start;
                                    }
                                    break;

                                case Constants::LaunchEnemy_TwoRocket_Start ... Constants::LaunchEnemy_TwoRocket_End:

                                    switch (activeEnemies) {

                                        case 0:
                                            randomEnemy = Constants::LaunchEnemy_Start;
                                            break;

                                        case 1:
                                            randomEnemy = Constants::LaunchEnemy_OneRocket_Start;
                                            break;

                                        case 2 ... Constants::Enemy_Count:
                                            break;
                                            
                                    }

                                    break;

                                case Constants::LaunchEnemy_ThreeRocket_Start ... Constants::LaunchEnemy_ThreeRocket_End:

                                    switch (activeEnemies) {

                                        case 0:
                                            randomEnemy = Constants::LaunchEnemy_Start;
                                            break;

                                        case 1:
                                            randomEnemy = Constants::LaunchEnemy_OneRocket_Start;
                                            break;

                                        case 2:
                                            randomEnemy = Constants::LaunchEnemy_TwoRocket_Start;
                                            break;

                                        case 3 ... Constants::Enemy_Count:
                                            break;
                                            
                                    }

                                    break;

                                case Constants::LaunchEnemy_FourRocket_Start ... Constants::LaunchEnemy_FourRocket_End:

                                    switch (activeEnemies) {

                                        case 0:
                                            randomEnemy = Constants::LaunchEnemy_Start;
                                            break;

                                        case 1:
                                            randomEnemy = Constants::LaunchEnemy_OneRocket_Start;
                                            break;

                                        case 2:
                                            randomEnemy = Constants::LaunchEnemy_TwoRocket_Start;
                                            break;

                                        case 3:
                                            randomEnemy = Constants::LaunchEnemy_ThreeRocket_Start;
                                            break;

                                        case 4 ... Constants::Enemy_Count:
                                            break;
                                            
                                    }

                                    break;

                            }


                            switch (randomEnemy) {

                                case Constants::LaunchEnemy_Start ... Constants::LaunchEnemy_Nothing:

                                    this->scenery_Bottom_Inc = (random(0, 5) - 2);       

                                    if (this->scenery_Bottom_Inc == 0) {

                                        this->scenery_Bottom_Counter = random(1, 3);

                                    }
                                    else {
                                        
                                        this->scenery_Bottom_Counter = random(2, 5);

                                    }

                                    break;

                                case Constants::LaunchEnemy_OneRocket_Start ... Constants::LaunchEnemy_OneRocket_End:

                                    this->scenery_Bottom_Inc = 0;       
                                    this->scenery_Bottom_Counter = Constants::Rocket_Width + (Constants::Rocket_Space * 2);
                                    this->launchEnemy(EnemyType::Rocket, this->distTravelled + 220 + Constants::Rocket_Space, enemyLaunch );

                                    break;

                                case Constants::LaunchEnemy_TwoRocket_Start ... Constants::LaunchEnemy_TwoRocket_End:

                                    this->scenery_Bottom_Inc = 0;       
                                    this->scenery_Bottom_Counter = (Constants::Rocket_Width * 2) + (Constants::Rocket_Space * 3);
                                    this->launchEnemy(EnemyType::Rocket, this->distTravelled + 220 + Constants::Rocket_Space, enemyLaunch );
                                    this->launchEnemy(EnemyType::Rocket, this->distTravelled + 220 + (2 * Constants::Rocket_Space) + Constants::Rocket_Width, enemyLaunch );

                                    break;

                                case Constants::LaunchEnemy_ThreeRocket_Start ... Constants::LaunchEnemy_ThreeRocket_End:

                                    this->scenery_Bottom_Inc = 0;       
                                    this->scenery_Bottom_Counter = (Constants::Rocket_Width * 3) + (Constants::Rocket_Space * 4);
                                    this->launchEnemy(EnemyType::Rocket, this->distTravelled + 220 + Constants::Rocket_Space, enemyLaunch );
                                    this->launchEnemy(EnemyType::Rocket, this->distTravelled + 220 + (2 * Constants::Rocket_Space) + Constants::Rocket_Width, enemyLaunch );
                                    this->launchEnemy(EnemyType::Rocket, this->distTravelled + 220 + (3 * Constants::Rocket_Space) + (2 * Constants::Rocket_Width), enemyLaunch );

                                    break;

                                case Constants::LaunchEnemy_FourRocket_Start ... Constants::LaunchEnemy_FourRocket_End:

                                    this->scenery_Bottom_Inc = 0;       
                                    this->scenery_Bottom_Counter = (Constants::Rocket_Width * 5) + (Constants::Rocket_Space * 6);
                                    this->launchEnemy(EnemyType::Rocket, this->distTravelled + 220 + Constants::Rocket_Space, enemyLaunch );
                                    this->launchEnemy(EnemyType::Rocket, this->distTravelled + 220 + (2 * Constants::Rocket_Space) + Constants::Rocket_Width, enemyLaunch );
                                    this->launchEnemy(EnemyType::Rocket, this->distTravelled + 220 + (3 * Constants::Rocket_Space) + (2 * Constants::Rocket_Width), enemyLaunch );
                                    this->launchEnemy(EnemyType::Rocket, this->distTravelled + 220 + (4 * Constants::Rocket_Space) + (3 * Constants::Rocket_Width), enemyLaunch );

                                    break;


                            }

                        }

                        break;

                    default:

                        this->scenery_Bottom_Inc = (random(0, 3) - 2);       

                        if (this->scenery_Bottom_Inc == 0) {

                            this->scenery_Bottom_Counter = random(1, 3);

                        }
                        else {
                            
                            this->scenery_Bottom_Counter = random(3, 7);

                        }

                        break;

                }

                this->scenery_Bot[x] = this->scenery_Bot[x - 1] - this->scenery_Top_Inc + this->scenery_Bottom_Inc;
                this->scenery_Bottom_Counter--;         

            }


        }

        void moveScenery(uint8_t x) {

            for (uint8_t i = 0; i < 220 - x; i++) {

                this->scenery_Top[i] = this->scenery_Top[i + x];
                this->scenery_Bot[i] = this->scenery_Bot[i + x];

            }

        }

        void reset() {

            for (uint8_t i = 0; i < 220; i++) {
                this->scenery_Top[i] = 880;
                this->scenery_Bot[i] = 240;
            }

            this->viewY = 980;
            this->distTravelled = 0;
            
        }




};
