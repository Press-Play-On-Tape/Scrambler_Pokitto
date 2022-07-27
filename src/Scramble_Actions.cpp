#include "Scramble.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::playerActions() {

    switch (this->player.getYDirection()) {

        case Direction::None:

            if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) {

                this->player.decY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->viewY < 70) {
                    this->viewY = this->viewY - 1;
                }

            }

            if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) {

                this->player.incY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->viewY > 176 - 90) {
                    this->viewY = this->viewY + 1;
                }

            }

            break;

        case Direction::Up:

            if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, (this->player.getYDelay() / 2))) {

                if (this->player.getYDelay() == 1) {

                    this->player.decY(2, PC::frameCount);

                    if (this->player.getY() - this->viewY < 70) {
                        this->viewY = this->viewY - 2;
                    }

                }
                else {

                    this->player.decY(1, PC::frameCount);

                    if (this->player.getY() - this->viewY < 70) {
                        this->viewY = this->viewY - 1;
                    }

                }

            }

            else if (PC::buttons.repeat(BTN_UP, 1)) { }

            else if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1)) {
                
                this->player.incY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->viewY > 176 - 90) {
                    this->viewY = this->viewY + 1;
                }

            }

            else if (this->player.getYDelay() <= Constants::Player_Inertia) {

                if (this->player.getYDelay() == 1) { this->player.setYDelay(2); }

                if (this->player.movePlayerY(PC::frameCount)) {

                    this->player.decY(1, PC::frameCount, this->player.getYDelay() * 2, true);

                    if (this->player.getY() - this->viewY < 70) {
                        this->viewY = this->viewY - 1;
                    }

                }

            }

            break;

        case Direction::Down:

            if (PC::buttons.pressed(BTN_UP) || PC::buttons.repeat(BTN_UP, 1)) {

                this->player.decY(1, PC::frameCount, Constants::Player_Inertia);

                if (this->player.getY() - this->viewY < 70) {
                    this->viewY = this->viewY - 1;
                }

            }

            else if (PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, (this->player.getYDelay() / 2))) {

                if (this->player.getYDelay() == 1) {

                    this->player.incY(2, PC::frameCount);

                    if (this->player.getY() - this->viewY > 176 - 90) {
                        this->viewY = this->viewY + 2;
                    }

                }
                else {

                    this->player.incY(1, PC::frameCount);

                    if (this->player.getY() - this->viewY > 176 - 90) {
                        this->viewY = this->viewY + 1;
                    }

                }

            }

            else if (PC::buttons.repeat(BTN_DOWN, 1)) { }

            else if (this->player.getYDelay() <= Constants::Player_Inertia) {

                if (this->player.getYDelay() == 1) { this->player.setYDelay(2); }

                if (this->player.movePlayerY(PC::frameCount)) {

                    this->player.incY(1, PC::frameCount, this->player.getYDelay() * 2, true);

                    if (this->player.getY() - this->viewY > 176 - 90) {
                        this->viewY = this->viewY + 1;
                    }

                }

            }

            break;

    }

    if (PC::buttons.pressed(BTN_LEFT) || PC::buttons.repeat(BTN_LEFT, 1) && this->player.getX() > this->distTravelled) {
        this->player.setX(this->player.getX() - 1);
    }

    if (PC::buttons.pressed(BTN_RIGHT) || PC::buttons.repeat(BTN_RIGHT, 1) && this->player.getX() < this->distTravelled + 220 - Constants::Player_Width) {
        this->player.setX(this->player.getX() + 1);
    }

    if (PC::buttons.pressed(BTN_C)) {

        gameState = GameState::Game_Init;

    }


    // Player shoots bullet ..

    if (PC::buttons.pressed(BTN_A)) {

        uint8_t bulletIdx = bullets.getInactiveBullet();

        if (bulletIdx != Constants::Bullet_None) {

            Bullet &bullet = bullets.bullets[bulletIdx];
            bullet.setActive(true);
            bullet.setBulletType(BulletType::PlayerBullet);
            bullet.setX(this->player.getX() + Constants::Player_Width);
            bullet.setY(this->player.getY() + 4);
            bullet.setMuzzleIndex(8);

            #ifdef SOUNDS
                playSoundEffect(SoundEffect::Laser);
            #endif


        }

    }


    // Player drops bomb ..

    if (PC::buttons.pressed(BTN_B)) {

        uint8_t bombIdx = bullets.getInactiveBomb();

        if (bombIdx != Constants::Bomb_None) {

            Bullet &bomb = bullets.bombs[bombIdx];
            bomb.setActive(true);
            bomb.setBulletType(BulletType::PlayerBomb);
            bomb.setX(this->player.getX() + (Constants::Player_Width / 2));
            bomb.setY(this->player.getY() + Constants::Player_Height);
            bomb.setMuzzleIndex(8);
            bomb.setXInertia(1);

            #ifdef SOUNDS
                playSoundEffect(SoundEffect::Laser);
            #endif

        }

    }

}