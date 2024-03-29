#pragma once
#define PI 3.141592

#include <math.h>
#include <cstdlib>

class Vec2{
    public:
        float x, y;
        Vec2(float x = 0, float y = 0);
        Vec2 GetRotated(float ang);
        Vec2 operator+(const Vec2&);
        Vec2 operator-(const Vec2&) const;
        Vec2 operator*(const float) const;
};