#pragma once

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <vector>
#include <memory>
#include <iostream>

#include "Sprite.h"
#include "Music.h"
#include "Vec2.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.h"
#include "State.h"

class StageState : public State{
    private:
        Music backgroundMusic;
        TileSet* tileSet;
    public:
        StageState();
        ~StageState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
};