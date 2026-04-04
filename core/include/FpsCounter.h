#pragma once
#include "Chain.h"
#include "Chireiden.h"
#include "Macros.h"

#pragma pack(push, 1)
class FpsCounter
{
    uint32_t flags;
    uint32_t b;
    uint32_t c;
    ChainElem* chainElem;
    uint32_t d;
    double lastDeltaTime;
    uint32_t lowFpsCounter;
    uint32_t frameCounter;
    double accumulatedFps;
    double timeAccumuator;
    float currentFps;
    uint32_t idk[21];
};
#pragma pack(pop)
ASSERT_SIZE(FpsCounter, 0x8c);