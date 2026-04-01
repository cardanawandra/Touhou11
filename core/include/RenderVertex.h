#pragma once
#include "Chireiden.h"
#include "Vectors.h"

struct RenderVertex144
{
    Float3 pos;
    float rhw;
    D3DCOLOR diffuse;
    Float2 uv;
};
ASSERT_SIZE(RenderVertex144, 0x1c);

struct RenderVertexSq
{
    Float3 position;
    Float2 uv;
};
ASSERT_SIZE(RenderVertexSq, 0x14);