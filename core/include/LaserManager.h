#pragma once
#include "AnmVm.h"
#include "AnmLoaded.h"
#include "Chain.h"
#include "Chireiden.h"
#include "LaserBase.h"
#include "LaserInfinite.h"
#include "LaserLine.h"
#include "LaserSegment.h"
#include "Macros.h"

class LaserManager
{
public:
    uint32_t unk[2];
    ChainElem* chainElem0;
    ChainElem* chainElem1;
    LaserBase laserData;
    LaserBase* pLaserData;
    int numLasersMaybe;
    int someLimit;
    D3DXVECTOR3 playerPos;
    int idk[3];
    AnmLoaded* laserAnm;
    int idk2;

    static int allocateNewLaser(BOOL isLaserLine);
};
ASSERT_SIZE(LaserManager, 0x47c);