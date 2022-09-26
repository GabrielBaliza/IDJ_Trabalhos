#pragma once

#define SPEED 150
#define ALIEN "./assets/img/alien.png"
#define ALIEN_DEATH "./assets/img/aliendeath.png"
#define MAXHP 50
#define PI2 6.283185307
#define ALIEN_ANG_VEL 25
#define RESTINGCOOLDOWN 0.75

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Minion.h"
#include "Game.h"
#include "State.h"
#include "Collider.h"
#include "Timer.h"
#include "PenguinBody.h"

#include <iostream>
#include <string>
#include <memory>
#include <queue>
#include <vector>
#include <cmath>

class Alien : public Component{
    private:
        enum AlienState{MOVING, RESTING};
        AlienState state;
        Timer restTimer;
        Vec2 destination;
        Vec2 speed;
        int hp;
        float timeOffset;
        std::vector<std::weak_ptr<GameObject>> minionArray;
    public:
        static int alienCount;
        Alien(GameObject& associated, int nMinions, float offset);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void NotifyCollision(GameObject& other);
        void MinionHit(GameObject& minion);
};