#pragma once

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Component.h"

#include "Resources.h"

#include <iostream>
#include <string>

class Sprite : public Component{
    private:
        SDL_Texture *texture;
        int width;
        int heigth; 
        SDL_Rect clipRect;
    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file);
        ~Sprite();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render();
        void Render(int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Update(float dt);
        bool Is(std::string type);
};