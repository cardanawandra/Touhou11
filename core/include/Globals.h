#pragma once
#include "Chireiden.h"
#include "Shottypes.h"
#include "Timer.h"
#include "RenderVertex.h"
#include "Lzss.h"
#include "Rng.h"
#include "Supervisor.h"
#include "SoundManager.h"
#include "GameConfig.h"
#include "InputManager.h"

class AnmManager;
class Supervisor;
class AsciiManager;
struct Chain;
class Window;
struct PbgArchive;
class Spellcard;
struct FpsCounter;
class Player;

struct Globals
{
    int scoreLimit;
    int currentScore;
    int currentPower;
    int u1;
    int currentPiv;
    int u2;
    int u3;
    Timer timer;
    CharacterId character;
    SubshotId subshot;
    int currentLives;
    int currentLifeFragments;
    int difficulty;
    int u4;
    int currentStage;
    int currentStageCopy;
    int u5;
    int timeInStage;
    int timeInChapter;
    int continuesUsed;
    int alsoContinuesUsed;
    int rank;
    int maxPower;
    int powerPerLevel;
    int livesMaybe;
    int graze;
};
ASSERT_SIZE(Globals, 0x78);

#define X_VAR(type, name, addr) \
    using __Type_##name = type; \
    inline __Type_##name& name = *reinterpret_cast<__Type_##name*>(addr);

#define X_FUNC(ret, name, addr, params) \
    inline auto& name = *reinterpret_cast<ret (*) params>(addr);

#include "symbols.inc"

#undef X_VAR
#undef X_FUNC

extern D3DFORMAT g_d3dFormats[];
extern uint32_t g_bytesPerPixelLookupTable[];

int fileExists(LPCSTR filePath);
int createDirectory(LPCSTR pathName);
int writeToFile(LPCSTR fileName, DWORD numBytes, LPVOID bytes);

// 0x40b9d0
void projectMagnitudeToVectorComponents(D3DXVECTOR3* vec, float theta, float scale);

/**
 * 0x458400
 * @brief  Returns a memory-mapped file
 * @param  filename           EAX:4
 * @param  outSize            Stack[0x4]:4
 * @param  isExternalResource Stack[0x8]:4
 * @return byte*              EAX:4
 */
byte* openFile(const char* filename, size_t* outSize, BOOL isExternalResource);

/**
 * 0x458400
 * @brief  Returns an angle in the range [-PI, PI]
 * @param  inputAngleRadians
 * @param  isExternalResource Stack[0x8]:4
 * @return float
 */
float normalizeAngle(float inputAngleRadians);

// 0x459aa0
void decomposeSpeedMagnitudeIntoVelocityComponents(D3DXVECTOR3* velocity, float angle, float speed);