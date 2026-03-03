#pragma once
#include <stdint.h>

struct InputManager
{
    uint16_t currentState;      // 0x00
    uint16_t padding;
    uint16_t previousState;     // 0x04
    uint16_t padding2;
    int autoRepeatState;        // 0x08 (Bits pulse on/off during hold)
    int triggerState;           // 0x0C (Pressed this frame)
    int releaseState;           // 0x10 (Released this frame)
    int durationCounters[32];   // 0x14 (Counters for each of the 32 input bits)
    int shortHoldState;

    static void update(InputManager* This);
};

enum InputBits
{
    SHOOT = 0x0001,
    BOMB = 0x0002,
    UNK_2 = 0x0004,
    FOCUS = 0x0008,
    UP = 0x0010,
    DOWN = 0x0020,
    LEFT = 0x0040,
    RIGHT = 0x0080,
    ESC = 0x0100,
    SKIP = 0x0200,
    PAUSE = 0x0100,
    Q = 0x0400,
    S = 0x0800,
    HOME_P = 0x1000,
    ENTER = 0x2000,
    D = 0x4000,
    R = 0x8000,
    F10 = 0x10000
};
