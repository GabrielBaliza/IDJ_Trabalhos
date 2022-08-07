#pragma once

#define MINION "./assets/img/minion.png"
#define ANG_VEL 0.785398

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"

#include <iostream>
#include <string>
#include <memory>

class Minion : public Component{
    private:
        GameObject& alienCenter;
        float arc;
    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);
};