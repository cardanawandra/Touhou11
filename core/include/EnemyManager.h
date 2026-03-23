#pragma once
#include "AnmLoaded.h"
#include "Chain.h"
#include "Chireiden.h"
#include "EclManager.h"
#include "Macros.h"
#include "Timer.h"


class EnemyManager
{
public:
    uint32_t flags;
    uint32_t idk0;
    ChainElem* chain1;
    ChainElem* onDraw;
    int idk1[12];
    AnmLoaded* bulletAnm;
    AnmLoaded* anmLoadeds[3];
    Timer timer;
    EclManager* enemyController;
    int someStruct2;
    int idk3;
    int someIndicator;
    int idk4;
};
ASSERT_SIZE(EnemyManager, 0x78);