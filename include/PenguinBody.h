#pragma once

#define PENGUIN_BODY "./assets/img/penguin.png"
#define PENGUIN_DEATH "./assets/img/penguindeath.png"
#define BOOM "./assets/audio/boom.wav"
#define PLAYER_HP 100
#define MAXSPEED 350
#define ANG_SPEED 1.570796
#define ACCELERATION 100
#define DESACCELERATION 50
#define DMGCOLL 10

#include "Vec2.h"
#include "GameObject.h"
#include "Game.h"
#include "State.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Collider.h"
#include "Camera.h"
#include "Sound.h"
#include "Minion.h"
#include "Alien.h"

#include <iostream>
#include <string>
#include <memory>

class PenguinBody : public Component
{
    private:
        std::weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;
    public:
        static PenguinBody* player;
        PenguinBody(GameObject& associated);
        ~PenguinBody();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void NotifyCollision(GameObject& other);
        void ExternalDamage(int damage);
        Vec2 PlayerPos();
        
};