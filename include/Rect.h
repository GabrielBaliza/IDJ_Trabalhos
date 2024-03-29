#pragma once

#include "Vec2.h"

class Rect{
    public:
        float x, y, w, h;
        Rect(float x = 0, float y = 0, float w = 0, float h = 0);
        bool Contains(float x1, float y1);
        void Centralize(float x, float y);
        void Centralize(Vec2 center);
        Vec2 Center();
};