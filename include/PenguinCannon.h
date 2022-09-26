#pragma once

#define PENGUIN_CANNON "./assets/img/cubngun.png"
#define PENGUIN_BULLET "./assets/img/penguinbullet.png"
#define PBULLETSPEED 250
#define P_DAMAGE 10
#define P_MAXDIST 500
#define COOLDOWNTIME 0.5

#include "GameObject.h"
#include "Sprite.h"
#include "Rect.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Game.h"
#include "Collider.h"
#include "Timer.h"
#include "PenguinBody.h"

#include <iostream>
#include <string>
#include <math.h>

class PenguinCannon : public Component{
    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
        Timer cooldown;
    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot();
        void NotifyCollision(GameObject& other);

};