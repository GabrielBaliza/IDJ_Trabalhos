#pragma once

#define PENGUIN_CANNON "./assets/img/cubngun.png"
#define PENGUIN_BULLET "./assets/img/penguinbullet.png"
#define PBULLETSPEED 200
#define P_DAMAGE 5
#define P_MAXDIST 250

#include "GameObject.h"
#include "Sprite.h"
#include "Rect.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Game.h"
#include "Collider.h"

#include <iostream>
#include <string>
#include <math.h>

class PenguinCannon : public Component{
    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot();
        void NotifyCollision(GameObject& other);

};