#pragma once
#include "AnmId.h"
#include "AnmVm.h"
#include "Chain.h"
#include "Chireiden.h"
#include "Macros.h"
#include "Timer.h"
#include "Vectors.h"

#pragma pack(push, 1)
class Spellcard
{
public:
    int unk0[2];
    ChainElem* chainElem0;
    ChainElem* chainElem1;
    AnmVm dualVms[2];
    AnmId anmId1;
    AnmId anmId2;
    AnmId anmId3;
    AnmId anmId4;
    Timer timer_0x888;
    int unk1[16];
    int someValue0;
    uint32_t flags;
    int someInt;
    int someOtherInt;
    int someInt2;
    int unk2;
    int someCounter;
    int unk3;
    double timeOffset;
    double deltaTime;
    int unk4;
    Float3 someVec3;
    int unk5[2];
};
#pragma pack(pop)
ASSERT_SIZE(Spellcard, 0x924);