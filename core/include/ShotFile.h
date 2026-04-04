#pragma once

struct Shooter;
struct ShotFile
{
    int idk0;
    float hurtboxSize;
    float float_0x8;
    float itemAttractBoxSize;
    float speedSubpixel;
    float focusedSpeedSubpixel;
    float normalizedSpeedSubpixel;
    float normalizedFocusedSpeedSubpixel;
    int maxPowerMultiplier;
    int powerPerLevel;
    int idk2[144];
    Shooter* shooters;
};