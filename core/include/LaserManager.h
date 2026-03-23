#pragma once
#include "AnmVm.h"
#include "AnmLoaded.h"
#include "Chain.h"
#include "Chireiden.h"
#include "LaserData.h"
#include "LaserSegment.h"
#include "Macros.h"

class LaserManager
{
public:
    AnmLoaded laserAnm;
    uint32_t unk[2];
    ChainElem* chainElem0;
    ChainElem* chainElem1;
    LaserData laserData;
    void* vfunc; // need to verify  
    int someCountdown;
    int someLimit;
    uint32_t unk1[8];
};
// ASSERT_SIZE(LaserManager, 0x47c);