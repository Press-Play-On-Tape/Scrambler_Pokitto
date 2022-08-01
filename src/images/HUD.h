#pragma once

namespace Images {

    #include "hud/HUD.h"
    #include "hud/Live.h"
    #include "hud/Live_Grey.h"

    const uint8_t * const Lives[] = { 
        Live_Grey,
        Live,
    };
    
};