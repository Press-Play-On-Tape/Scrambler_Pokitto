#pragma once

namespace Images {

    #include "enemy/EnemyBullet.h"
    #include "enemy/Rocket.h"
    #include "enemy/FuelDepot.h"
    #include "enemy/GroundPod.h"
    #include "enemy/SurfaceToAir_00.h"
    #include "enemy/SurfaceToAir_01.h"
    #include "enemy/SurfaceToAir_02.h"

    const uint8_t * const SurfaceToAir[] = { 
        SurfaceToAir_00,
        SurfaceToAir_01,
        SurfaceToAir_02,
    };

};