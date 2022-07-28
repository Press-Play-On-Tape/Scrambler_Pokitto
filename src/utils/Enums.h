#pragma once

#define _DEBUG
#define _SOUNDS
#define COOKIE_INITIALISED 12

namespace Constants {

    constexpr uint8_t Screen_Height = 188;
    constexpr uint8_t Distance = 64;

    constexpr uint8_t Player_Width = 20;
    constexpr uint8_t Player_Height = 13;
    constexpr uint8_t Player_Inertia = 8;

    constexpr uint8_t Player_Bullet_Count = 4;
    constexpr uint8_t Player_Bullet_Width = 8;
    constexpr uint8_t Player_Bullet_Height = 5;
    constexpr uint8_t Bullet_None = 255;

    constexpr uint8_t Player_Bomb_Count = 4;
    constexpr uint8_t Player_Bomb_Width = 5;
    constexpr uint8_t Player_Bomb_Height = 8;

    constexpr uint8_t Bomb_None = 255;

    constexpr uint8_t Enemy_Bullet_Count = 4;
    constexpr uint8_t Enemy_Bullet_Width = 2;
    constexpr uint8_t Enemy_Bullet_Height = 2;
    constexpr uint8_t Enemy_Max_Width = 40;
    constexpr uint8_t Enemy_Count = 10;
    constexpr uint8_t Enemy_None = 255;    

    constexpr uint8_t Enemy_Space = 3;
    constexpr uint8_t Rocket_Width = 9;
    constexpr uint8_t Rocket_Height = 20;

    constexpr uint8_t FuelDepot_Width = 25;
    constexpr uint8_t FuelDepot_Height = 15;

    constexpr uint8_t GroundPod_Width = 16;
    constexpr uint8_t GroundPod_Height = 16;

    constexpr uint8_t SurfaceAir_Width = 24;
    constexpr uint8_t SurfaceAir_Height = 18;

    constexpr uint8_t Particle_Count = 75;
    constexpr uint8_t Particle_None = 255;
    constexpr uint8_t Shockwave_Count = 20;
    constexpr uint8_t Shockwave_None = 255;


    // Scenery limits ..

    constexpr uint16_t Scenery_Top = 15;
    constexpr uint16_t Scenery_DistanceBetween_Min_Start = 0;
    constexpr uint16_t Scenery_DistanceBetween_Min_End = Scenery_DistanceBetween_Min_Start + 100;
    constexpr uint16_t Scenery_DistanceBetween_Normal_Start = Scenery_DistanceBetween_Min_End + 1;
    constexpr uint16_t Scenery_DistanceBetween_Normal_End = Scenery_DistanceBetween_Normal_Start + 100;


    // Enemy limits ..

    constexpr uint16_t LaunchEnemy_Start = 0;
    constexpr uint16_t LaunchEnemy_Nothing = LaunchEnemy_Start + 1600;

    constexpr uint16_t LaunchEnemy_OneRocket_Start = LaunchEnemy_Nothing + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_End = LaunchEnemy_OneRocket_Start + 12;
    constexpr uint16_t LaunchEnemy_TwoRocket_Start = LaunchEnemy_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_End = LaunchEnemy_TwoRocket_Start + 6;
    constexpr uint16_t LaunchEnemy_ThreeRocket_Start = LaunchEnemy_TwoRocket_End + 1;
    constexpr uint16_t LaunchEnemy_ThreeRocket_End = LaunchEnemy_ThreeRocket_Start + 0;
    constexpr uint16_t LaunchEnemy_FourRocket_Start = LaunchEnemy_ThreeRocket_End + 1;
    constexpr uint16_t LaunchEnemy_FourRocket_End = LaunchEnemy_FourRocket_Start + 0;

    constexpr uint16_t LaunchEnemy_OneRocket_FuelDepot_Start = LaunchEnemy_FourRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_FuelDepot_End = LaunchEnemy_OneRocket_FuelDepot_Start + 2;
    constexpr uint16_t LaunchEnemy_TwoRocket_FuelDepot_Start = LaunchEnemy_OneRocket_FuelDepot_End + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_FuelDepot_End = LaunchEnemy_TwoRocket_FuelDepot_Start + 1;

    constexpr uint16_t LaunchEnemy_FuelDepot_OneRocket_Start = LaunchEnemy_TwoRocket_FuelDepot_End + 1;
    constexpr uint16_t LaunchEnemy_FuelDepot_OneRocket_End = LaunchEnemy_FuelDepot_OneRocket_Start + 2;
    constexpr uint16_t LaunchEnemy_FuelDepot_TwoRocket_Start = LaunchEnemy_FuelDepot_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_FuelDepot_TwoRocket_End = LaunchEnemy_FuelDepot_TwoRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_OneRocket_FuelDepot_OneRocket_Start = LaunchEnemy_FuelDepot_TwoRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_FuelDepot_OneRocket_End = LaunchEnemy_OneRocket_FuelDepot_OneRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_OneRocket_GroundPod_Start = LaunchEnemy_OneRocket_FuelDepot_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_GroundPod_End = LaunchEnemy_OneRocket_GroundPod_Start + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_GroundPod_Start = LaunchEnemy_OneRocket_GroundPod_End + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_GroundPod_End = LaunchEnemy_TwoRocket_GroundPod_Start + 1;

    constexpr uint16_t LaunchEnemy_GroundPod_OneRocket_Start = LaunchEnemy_TwoRocket_GroundPod_End + 1;
    constexpr uint16_t LaunchEnemy_GroundPod_OneRocket_End = LaunchEnemy_GroundPod_OneRocket_Start + 1;
    constexpr uint16_t LaunchEnemy_GroundPod_TwoRocket_Start = LaunchEnemy_GroundPod_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_GroundPod_TwoRocket_End = LaunchEnemy_GroundPod_TwoRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_OneRocket_GroundPod_OneRocket_Start = LaunchEnemy_GroundPod_TwoRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_GroundPod_OneRocket_End = LaunchEnemy_OneRocket_GroundPod_OneRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_OneRocket_SurfaceAir_Start = LaunchEnemy_OneRocket_GroundPod_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_SurfaceAir_End = LaunchEnemy_OneRocket_SurfaceAir_Start + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_SurfaceAir_Start = LaunchEnemy_OneRocket_SurfaceAir_End + 1;
    constexpr uint16_t LaunchEnemy_TwoRocket_SurfaceAir_End = LaunchEnemy_TwoRocket_SurfaceAir_Start + 1;

    constexpr uint16_t LaunchEnemy_SurfaceAir_OneRocket_Start = LaunchEnemy_TwoRocket_SurfaceAir_End + 1;
    constexpr uint16_t LaunchEnemy_SurfaceAir_OneRocket_End = LaunchEnemy_SurfaceAir_OneRocket_Start + 1;
    constexpr uint16_t LaunchEnemy_SurfaceAir_TwoRocket_Start = LaunchEnemy_SurfaceAir_OneRocket_End + 1;
    constexpr uint16_t LaunchEnemy_SurfaceAir_TwoRocket_End = LaunchEnemy_SurfaceAir_TwoRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_OneRocket_SurfaceAir_OneRocket_Start = LaunchEnemy_SurfaceAir_TwoRocket_End + 1;
    constexpr uint16_t LaunchEnemy_OneRocket_SurfaceAir_OneRocket_End = LaunchEnemy_OneRocket_SurfaceAir_OneRocket_Start + 1;

    constexpr uint16_t LaunchEnemy_Max = LaunchEnemy_OneRocket_SurfaceAir_OneRocket_End;

}

enum class GameState : uint8_t {
    Splash_Init,
    Splash,
    Title_Init,
    Title,
    Game_Init,
    Game,
};

enum class EnemyType : uint8_t {
    Rocket,
    FuelDepot,
    GroundPod,
    SurfaceAir,
};

enum class Themes : uint8_t {
    Main,
    Winner
};

enum class ExplosionSize : int8_t {
    Small,
    Medium,
    Large,
    Huge
};

enum class ExplosionColor : int8_t {
    Blue,
    Red
};

enum class Direction : uint8_t {
    Left,
    Up,
    Right,
    Down,
    None,
};

enum class SoundEffects : uint8_t {
    Both,
    Music,
    SFX,
    None
};

enum class SoundEffect : uint8_t {
    Deal,
    EnemyDeath,
};

inline SoundEffects &operator++(SoundEffects &c ) {
    c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) + 1) % 4 );
    return c;
}

inline SoundEffects operator++(SoundEffects &c, int ) {
    SoundEffects result = c;
    ++c;
    return result;
}

inline SoundEffects &operator--(SoundEffects &c ) {
    if (static_cast<uint8_t>(c) > 0) {
        c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) - 1) % 4 );
    }
    else {
        c = static_cast<SoundEffects>( 3 );
    }
    return c;
}

inline SoundEffects operator--(SoundEffects &c, int ) {
    SoundEffects result = c;
    --c;
    return result;
}