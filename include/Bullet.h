#pragma once

#define PI 3.141592

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"

#include <iostream>
#include <string>

class Bullet : public Component{
    private:
        Vec2 speed;
        float distanceLeft;
        int damage; 
    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount = 1, float frameTime = 1);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage(Vec2 target);
};