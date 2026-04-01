#pragma once
#include "AnmId.h"
#include "Bullet.h"
#include "Chireiden.h"
#include "Interp.h"
#include "Macros.h"
#include "Timer.h"
#include "Vectors.h"

struct EnemyBulletShooter
{
    int16_t color;
    Float3 enemyPos;
    float angleAim;
    float angleBetween;
    float speedFirst;
    float speedLast;
    float distance;
    BulletEx ex[18];
    int32_t idk[9];
    int16_t countBullets;
    int16_t countLayers;
    int32_t aimType;
    int32_t initial_active_ex_flags;
    int32_t sfx_slot;
    int32_t sfx_transform;
    int32_t initial_ex_index;
    int32_t idk2;   
};
ASSERT_SIZE(EnemyBulletShooter, 0x214);

struct PosVel
{
    Float3 pos;
    Float3 prevFinalPosOffset;
    float speed;
    float angle;
    float radialDistance;
    int idk2[3];
    uint32_t flags;
};
ASSERT_SIZE(PosVel, 0x34);

struct EnemyLife
{
    int32_t current;
    int32_t maximum;
    int32_t remainingForCurrentAttack;
    int32_t currentScaled;
    int32_t startingValueForNextAttack;
    BOOL isSpell;
};
ASSERT_SIZE(EnemyLife, 0x18);

struct EnemyDrop
{
    int32_t mainDrop;
    int exDrop[12];
    Float2 area;
};
ASSERT_SIZE(EnemyDrop, 0x3c);

class Enemy;
class EnemyBase
{
public:
    PosVel prevFinalPos;
    PosVel finalPos;
    PosVel absPos;
    PosVel relPos;
    Float2 hurtboxSize;
    Float2 hitboxSize;
    AnmId anmIds[10];
    int selectedAnmIndex;
    int anmSlot0Index;
    int anmSlot0Script;
    int anmSetMain;
    int idk;
    int unused;
    int anmLayers;
    int intVars[4];
    float floatVars[8];
    Timer timer_0x154;
    int idk0[3];
    Interp<Float3> absPosInterp;
    Interp<Float3> relPosInterp;
    Interp<Float2> absAngleSpeedInterp;
    Interp<Float2> relAngleSpeedInterp;
    Interp<Float2> absRadialDistInterp;
    Interp<Float2> relRadialDistInterp;
    Interp<Float2> absEllipseInterp;
    Interp<Float2> relEllipseInterp;
    EnemyBulletShooter bulletProps[8];
    Float3 bulletOffsets[8];
    Float3 bulletOrigins[8];
    int idk1[2];
    Float2 moveLimitCenter;
    Float2 moveLimitSize;
    int scoreReward;
    EnemyLife life;
    EnemyDrop drop;
    int deathSound;
    int deathAnmScript;
    int deathAnmIndex;
    int idk2[2];
    Timer timer_for_set_invuln;
    Timer maybe_timer_for_no_hitbox_dur;
    uint32_t flags;
    int bombshield_on_anm_main;
    int bombshield_off_anm_main;
    int own_boss_id;
    float et_protect_range;
    int damageTakenMaybe;
    int idk3[31];
    Enemy* enemyFull;
    int idk6;
    int idk4;
    float someFloat;
    int someInt;
    int idk5[2];
    void* func_from_ecl_func_set;
    void* func_from_ecl_flag_ext_damage;
    void* func_from_ecl_unknown_531;
};