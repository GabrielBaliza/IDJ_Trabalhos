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
#include <stack>

class State;
class Game{
    private:
        int frameStart;
        float dt;
        static Game *instance;
        State *storedState;
        SDL_Window *window;
        SDL_Renderer *renderer;
        std::stack<std::unique_ptr<State>> stateStack;        
        void CalculateDeltaTime();
    public:
        Game(std::string title, int width, int height);
        ~Game();
        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();   
        void Push(State* state);
        void Run();
        float GetDeltaTime();     
};