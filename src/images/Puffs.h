#pragma once

namespace Images {

    #include "puffs/Hit_00.h"
    #include "puffs/Hit_01.h"
    #include "puffs/Hit_02.h"
    #include "puffs/Hit_03.h"
    #include "puffs/Hit_04.h"
    #include "puffs/Hit_05.h"

    #include "puffs/Hit360_00.h"
    #include "puffs/Hit360_01.h"
    #include "puffs/Hit360_02.h"
    #include "puffs/Hit360_03.h"
    #include "puffs/Hit360_04.h"
    #include "puffs/Hit360_05.h"
    #include "puffs/Hit360_06.h"

    #include "puffs/Muzzle_00.h"
    #include "puffs/Muzzle_01.h"
    #include "puffs/Muzzle_02.h"

    const uint8_t * const Hit[] = { 
        Hit_00,
        Hit_01,
        Hit_02,
        Hit_03,
        Hit_04,
        Hit_05,
    };

    const uint8_t * const Hit360[] = { 
        Hit360_00,
        Hit360_01,
        Hit360_02,
        Hit360_03,
        Hit360_04,
        Hit360_05,
        Hit360_06,
    };
    
    const uint8_t * const Muzzle[] = { 
        Muzzle_00,
        Muzzle_01,
        Muzzle_02,
    };
    
};