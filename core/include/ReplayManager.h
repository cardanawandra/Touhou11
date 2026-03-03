#pragma once
#include "Chireiden.h"
#include "Macros.h"
#include "Chain.h"
#include "GameConfig.h"
#include <Vectors.h>

struct ReplayStageData
{
    int t11r;
    uint32_t someUnion;
    uint32_t e;
    uint32_t d;
    int someSize;
    int f;
    int g;
    int size;
    size_t decompressedSize;
};
ASSERT_SIZE(ReplayStageData, 0x24);

#pragma pack(push)
struct ReplayGameConfig
{
    short index;
    short e;
    short f;
    short h;
    short m;
    short g;
    __time64_t time64;
    int currentScore;
    GameConfig embeddedGameConfig;
    int b;
    int file;
    int character;
    int subshot;
    int difficulty;
    int stageClearMode;
    int continuesUsed;
};
#pragma pack(pop)
ASSERT_SIZE(ReplayGameConfig, 0x70);

struct ReplayPlayerData
{
    short currentStage;
    short rngTime;
    int idk0;
    int idk1;
    int currentScore;
    int currentPower;
    int piv;
    short currentLives;
    short currentLifeFragments;
    int rank;
    Int2 playerSubpixel;
    int continuesUsed;
    int livesMaybe;
    BOOL playerIsFocused;
    int graze;
    int marisaBFormation;
    int idk3[20];
    int frameSkipFlagProbably;
};
ASSERT_SIZE(ReplayPlayerData, 0x90);

struct ReplayDataChunk;
struct ReplayNode
{
    ReplayDataChunk* owner;
    ReplayNode* next;
    ReplayNode* prev;
};

struct ReplayDataChunk
{
    uint8_t inputData[5400];
    ReplayDataChunk* selfPtr;
    uint8_t auxData[900];
    uint8_t* auxDataPtr;
    ReplayNode replayNode;
};

class ReplayManager
{
    int idk0[2];
    ChainElem* onTick0b;
    ChainElem* onTick_00436d80;
    int someMode;
    ReplayStageData* stageData;
    ReplayGameConfig* gameConfig;
    ReplayPlayerData* playerData;
    int idk2[7];
    ReplayNode stageDataHeads[7];
    int idk3[3];
    int currentStage;
    int chunkCount;
    ReplayStageData replayStageDatas[8];
    byte* replayFileContents;
    short idk4;
    short idk5;
    ChainElem* chainElem1;
    ChainElem* onTick1b;
    int replayStageDataIndex;
    uint32_t flags;
    int idk6[64];
};
ASSERT_SIZE(ReplayManager, 0x2dc);