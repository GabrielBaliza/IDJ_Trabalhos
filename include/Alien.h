#pragma once

#define SPEED 100
#define ALIEN "./assets/img/alien.png"

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "InputManager.h"

#include <iostream>
#include <string>
#include <memory>
#include <queue>
#include <vector>
#include <cmath>

class Alien : public Component{
    private:
        class Action{
            public:
            enum ActionType{MOVE, SHOOT};
            Action(ActionType type, float x, float y);
            ActionType type;
            Vec2 pos;
        };
        Vec2 speed;
        int hp;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;
    public:
        Alien(GameObject& associated, int nMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};