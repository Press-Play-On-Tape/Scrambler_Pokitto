#pragma once

namespace Images {

    #include "player/Bomb.h"
    #include "player/Bullet.h"
    #include "player/PlayerShip.h"

    #include "player/PlayerFlame_00.h"
    #include "player/PlayerFlame_01.h"
    #include "player/PlayerFlame_02.h"
    #include "player/PlayerFlame_03.h"

    const uint8_t * const PlayerFlame[] = { 
        PlayerFlame_00,
        PlayerFlame_01,
        PlayerFlame_02,
        PlayerFlame_03,
    };

};