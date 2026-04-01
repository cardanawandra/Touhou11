#pragma once
#include "Chireiden.h"
#include "Macros.h"
#include "Vectors.h"

struct Camera
{
    Float3 offset;
    Float3 target;
    Float3 up;
    Float3 v3;
    Float3 callibration;
    Float3 eye;
    float fovY;
    D3DXMATRIX viewMatrix;
    D3DXMATRIX projectionMatrix;
    D3DVIEWPORT9 viewport;
    uint32_t idk;
    float m_globalRenderQuadOffsetX;
    float m_globalRenderQuadOffsetY;
    Float3 interpAmt;
    float fogEnd;
    float fogStart;
    float fogB;
    float fogG;
    float fogR;
    DWORD renderStateValue0;
    DWORD renderStateValue1;
};
ASSERT_SIZE(Camera, 0x118);