#pragma once

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Resources.h"
#include "State.h"
#include "InputManager.h"

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

class State;
class Game{
    private:
        static Game *instance;
        SDL_Window *window;
        SDL_Renderer *renderer;
        State *state;
        int frameStart;
        float dt;
        void CalculateDeltaTime();
        Game(std::string title, int width, int height);
    public:
        void Run();
        float GetDeltaTime();
        ~Game();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();

};