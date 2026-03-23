#pragma once
#include "Chireiden.h"
#include "AnmVm.h"
#include "Macros.h"
#include "LaserData.h"

struct LaserLine// : public LaserData
{
    LaserData laserData;
    float float_0x440;
    float float_0x444;
    int int_0x448;
    float float_0x44c;
    float float_0x450;
    float float_0x454;
    int int_0x458;
    D3DXVECTOR2 maybePlayerPos;
    short laserAnmScriptRelated;
    short scriptNumber;
    int idk[110];
    AnmVm vm1; // <0x624>
    AnmVm vm2; // <0xa58>

    static int createOrDestroyLaserSegments(LaserLine* This, AnmId anmId, int cancelFlag);
};
// ASSERT_SIZE(LaserLine, 0xe8c);