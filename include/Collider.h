#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Rect.h"

#include <iostream>
#include <string>

class Collider : public Component{
    private:
        Vec2 scale;
        Vec2 offset;
    public:
        Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void SetScale(Vec2 scale);
        void SetOffset(Vec2 offset);
        Rect box;
};