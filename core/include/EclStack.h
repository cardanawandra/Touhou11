#pragma once
#include "Chireiden.h"
#include "Macros.h"

struct EclStack
{
    int data[1024];
    int stackOffset;
    int baseOffset;
};
ASSERT_SIZE(EclStack, 0x1008);