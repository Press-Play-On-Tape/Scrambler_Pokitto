#pragma once

namespace Images {

    #include "enemy/EnemyBullet.h"
    #include "enemy/Rocket.h"
    #include "enemy/FuelDepot.h"
    #include "enemy/GroundPod.h"
    #include "enemy/SurfaceToAir_00.h"
    #include "enemy/SurfaceToAir_01.h"
    #include "enemy/SurfaceToAir_02.h"
    #include "enemy/Mine.h"
    #include "enemy/City_00.h"
    #include "enemy/City_01.h"
    #include "enemy/City_02.h"
    #include "enemy/FuelCan.h"
    #include "enemy/Eighter_00.h"
    #include "enemy/Eighter_01.h"
    #include "enemy/Eighter_02.h"
    #include "enemy/Eighter_03.h"
    #include "enemy/Eighter_04.h"

    const uint8_t * const SurfaceToAir[] = { 
        SurfaceToAir_00,
        SurfaceToAir_01,
        SurfaceToAir_02,
    };

    const uint8_t * const Eighter[] = { 
        Eighter_00,
        Eighter_01,
        Eighter_02,
        Eighter_03,
        Eighter_04,
    };

};