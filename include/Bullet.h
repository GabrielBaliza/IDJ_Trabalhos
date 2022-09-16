#pragma once

#define PI 3.141592

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Collider.h"

#include <iostream>
#include <string>

class Bullet : public Component{
    private:
        Vec2 speed;
        float distanceLeft;
        int damage; 
    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, bool targetsPlayer, int frameCount = 1, float frameTime = 1, Vec2 bulletScale = {1, 1}, Vec2 colliderScale = {1, 1}, Vec2 colliderOffset = {0, 0});
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage(Vec2 target);
        void NotifyCollision(GameObject& other);
        bool targetsPlayer;
};