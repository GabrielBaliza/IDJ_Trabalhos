#pragma once

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER


#include "SDL_include.h"
#include "Resources.h"
#include "State.h"

#include <string>
#include <cstdlib>
#include <ctime>

class State;
class Game{
    private:
        static Game *instance;
        SDL_Window *window;
        SDL_Renderer *renderer;
        State *state;
        Game(std::string title, int width, int height);
    public:
        void Run();
        ~Game();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();

};