#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"

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