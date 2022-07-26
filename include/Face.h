#pragma once

#include "Component.h"
#include "Sound.h"
#include "InputManager.h"

#include <iostream>
#include <string>

class Face : public Component{
    private:
        int hitpoints;
    public:
        Face(GameObject& associated);
        void Damage(int damage);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};