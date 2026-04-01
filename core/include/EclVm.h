#pragma once
#include "Chireiden.h"
#include "EclManager.h"
#include "EclStack.h"
#include "Macros.h"

class Enemy;
struct EclRunContext
{
    float time;
    EclInstruction* currentInstruction;
    EclStack stack;
    int asyncId;
    Enemy* enemy;
    int setByIns20;
    uint8_t difficultyMask;
    int setByIns1819;
};
ASSERT_SIZE(EclRunContext, 0x1024);

struct EclRunContextList
{
    EclRunContext* entry;
    EclRunContextList* next;
    EclRunContextList* prev;
};

class EclVm
{
public:
    // void* vtable; // 0x0
    EclRunContext* currentContext;
    EclRunContext primaryContext;
    void* fileManager;
    EclRunContextList asyncListHead;

    virtual void __thiscall vfunction1();
    virtual void __thiscall vfunction2();
    virtual void __thiscall vfunction3();
    virtual void __thiscall vfunction4();
    virtual void __thiscall vfunction5();
};
ASSERT_SIZE(EclVm, 0x103c);