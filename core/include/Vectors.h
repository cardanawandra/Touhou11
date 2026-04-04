#pragma once
#include "Chireiden.h"

struct Float3 : public D3DXVECTOR3
{
    Float3() = default;

    Float3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Float3 operator+(const Float3& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
    Float3 operator-(const Float3& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
    Float3 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar }; }
    Float3 operator/(float scalar) const { return { x / scalar, y / scalar, z / scalar }; }

    Float3& operator+=(const Float3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
    Float3& operator-=(const Float3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
    Float3& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
    Float3& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

    // Vector Operations
    static float dot(const Float3& a, const Float3& b) 
    { 
        return a.x * b.x + a.y * b.y + a.z * b.z; 
    }

    static Float3 cross(const Float3& a, const Float3& b) 
    {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    float lengthSq() const { return x * x + y * y + z * z; }
    float length() const { return std::sqrt(lengthSq()); }

    Float3 normalized() const 
    {
        float len = length();
        return (len > 0.0f) ? (*this / len) : Float3(0, 0, 0);
    }
};

struct Float2 : public D3DXVECTOR2
{
    Float2() = default;

    Float2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Float2 operator+(const Float2& rhs) const { return { x + rhs.x, y + rhs.y }; }
    Float2 operator-(const Float2& rhs) const { return { x - rhs.x, y - rhs.y }; }
    Float2 operator*(float scalar) const { return { x * scalar, y * scalar }; }
    Float2 operator/(float scalar) const { return { x / scalar, y / scalar }; }

    Float2& operator+=(const Float2& rhs) { x += rhs.x; y += rhs.y; return *this; }
    Float2& operator-=(const Float2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    Float2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    Float2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

    // Vector Operations
    static float dot(const Float2& a, const Float2& b) 
    { 
        return a.x * b.x + a.y * b.y; 
    }

    static float cross(const Float2& a, const Float2& b) 
    {
        return a.x * b.y - a.y * b.x;
    }

    float lengthSq() const { return x * x + y * y; }
    float length() const { return std::sqrt(lengthSq()); }

    Float2 normalized() const 
    {
        float len = length();
        return (len > 0.0f) ? (*this / len) : Float2(0, 0);
    }
};

struct Int3 
{
    int x, y, z;
};

struct Int2
{
    int x, y;
};