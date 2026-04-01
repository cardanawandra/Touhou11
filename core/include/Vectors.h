#pragma once
#include "Chireiden.h"

struct Float3 : public D3DXVECTOR3
{
    Float3()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Float3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Float3 operator+(const Float3& rhs) const
    {
        return Float3(x + rhs.x, y + rhs.y, z + rhs.z);
    }
};

struct Float2 : public D3DXVECTOR2 {};

struct Int3 
{
    int x, y, z;
};

struct Int2
{
    int x, y;
};