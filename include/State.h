#pragma once

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include <vector>
#include <memory>
#include <iostream>

#include "SDL_include.h"

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h" 
#include "Vec2.h"
#include "Face.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"

class State{
    private:
        //Sprite bg;
        Music music;
        bool quitRequested;
        std::vector<std::unique_ptr<GameObject>> objectArray;
        void Input();
        void AddObject(int mouseX, int mouseY);
    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();

};