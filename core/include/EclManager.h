#pragma once
#include "AnmLoaded.h"
#include "AnmManager.h"
#include "Chireiden.h"
#include "EclFile.h"
#include "Macros.h"

// 0x49404c: SptResourceInf_baseVtable
// 0x49404c: int base_vfunc1_scpt_handler(EnemyController* This, EclFile* eclFile);
// 0x494050: int base_vfunc2(EnemyController* This, EclInclude* eclInclude);

// 0x494090: EnemyController_overrideVtable?
// 0x494090: int EnemyController::base_vfunc1_scpt_handler(EnemyController* This,EclFile *eclFile)
// 0x494094: int EnemyController::override_vfunc2_load_func(EnemyController* This, EclInclude* eclInclude)
// 0x494098: int EnemyController::override_vfunc3_eclPathManip(EnemyController *This,LPBYTE eclPath)

// Notes:
// `EnemyManager` is the main thing that handles everything at a high level.
// `EclManager` is dedicated to loading ECL files and managing the alphabetical array. This really should've just been put in `EnemyManager` rather than its own struct. (old documentation called this `EnemyController`)
// `SptResource` is the base class of `EclManager`. There's nothing else that inherits from it and it's never used independently so it's essentially just a glorified set of extra functions that should've been in `EnemyManager`.
// `Enemy` is the full struct representing everything about an enemy with ECL state, motion, bullet data, health, etc.. (Old documentation sometimes called this `EnemyFull`)
// `EclVm` is the base class of `Enemy` and represents specifically the state of the running ECL script without any of the movement, bullets, etc.. In theory it could be used independently of enemies, but ZUN never does this (Previous documentation called this `Enemy` instead)
// `EnemyData` is a struct inside `Enemy` that has most of the fields/methods. I have no idea why most of this needed to be a substruct

// The low opcodes are handled via a type called EclContext and are always the same for everything that could possibly derive from EclVM. But the high opcodes and global variables actually invoke virtual function that the derived class overrides.
class EclManager // : public SptResourceInf (But I don't think we have to bother)
{
public:
    void* vftable; // EnemyController_vtable
    int	fileCount;
    int	size;
    EclFile* eclFiles[32];
    EclSubroutineRef* subroutines;
    uint32_t u0;
    uint32_t u1;
    int someBuffer[1024];

    // 0x45d900 (vfunction1)
    static int parse(EclManager* This, EclFile* eclFile);

    // 0x40ffa0
    // static int base_vfunc2(EnemyController* This, EclInclude* eclInclude);

    // 0x410d50 (vfunction2)
    static int loadInclude(EclManager* This, EclInclude* eclInclude);

    // 0x4104d0 (vfunction3)
    static int cacheAndParse(EclManager* This, const char* eclPath);
};
ASSERT_SIZE(EclManager, 0x1098);