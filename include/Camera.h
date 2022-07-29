#pragma once

#include "Vec2.h"
#include "InputManager.h"
#include "GameObject.h"



class Camera{
    private:
        static GameObject* focus;
    public:
        static Vec2 pos;
        static Vec2 speed;
        static void Update(float dt);
        static void Unfollow();
        static void Follow(GameObject* newFocus);
};