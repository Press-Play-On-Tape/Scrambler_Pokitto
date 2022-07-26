#pragma once

#define _DEBUG
#define _SOUNDS
#define COOKIE_INITIALISED 12

namespace Constants {

    constexpr uint8_t Screen_Height = 188;

    constexpr uint8_t Player_Width = 12;
    constexpr uint8_t Player_Height = 8;

    constexpr uint8_t Enemy_Count = 10;
    constexpr uint8_t Enemy_None = 255;    

    constexpr uint8_t Rocket_Width = 9;
    constexpr uint8_t Rocket_Space = 3;
    constexpr uint8_t Rocket_Height = 20;

    constexpr uint8_t Particle_Count = 75;
    constexpr uint8_t Particle_None = 255;
    constexpr uint8_t Shockwave_Count = 20;
    constexpr uint8_t Shockwave_None = 255;



    constexpr uint8_t Scenery_Top = 15;
    constexpr uint8_t Scenery_DistanceBetween_Min_Start = 0;
    constexpr uint8_t Scenery_DistanceBetween_Min_End = Scenery_DistanceBetween_Min_Start + 79;
    constexpr uint8_t Scenery_DistanceBetween_Normal_Start = Scenery_DistanceBetween_Min_End + 1;
    constexpr uint8_t Scenery_DistanceBetween_Normal_End = Scenery_DistanceBetween_Normal_Start + 100;



    constexpr uint8_t LaunchEnemy_Start = 0;
    constexpr uint8_t LaunchEnemy_Nothing = LaunchEnemy_Start + 180;
    constexpr uint8_t LaunchEnemy_OneRocket_Start = LaunchEnemy_Nothing + 1;
    constexpr uint8_t LaunchEnemy_OneRocket_End = LaunchEnemy_OneRocket_Start + 4;
    constexpr uint8_t LaunchEnemy_TwoRocket_Start = LaunchEnemy_OneRocket_End + 1;
    constexpr uint8_t LaunchEnemy_TwoRocket_End = LaunchEnemy_TwoRocket_Start + 1;
    constexpr uint8_t LaunchEnemy_ThreeRocket_Start = LaunchEnemy_TwoRocket_End + 1;
    constexpr uint8_t LaunchEnemy_ThreeRocket_End = LaunchEnemy_ThreeRocket_Start + 0;
    constexpr uint8_t LaunchEnemy_FourRocket_Start = LaunchEnemy_ThreeRocket_End + 1;
    constexpr uint8_t LaunchEnemy_FourRocket_End = LaunchEnemy_FourRocket_Start + 0;

    constexpr uint8_t LaunchEnemy_Max = LaunchEnemy_FourRocket_Start;



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
};

enum class Themes : uint8_t {
    Main,
    Winner
};

enum class ExplosionSize : int8_t {
    Small,
    Medium,
    Large
};

enum class ExplosionColor : int8_t {
    Blue,
    Red
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