#pragma once

#define YOUWIN_BG "./assets/img/win.jpg"
#define YOUWIN_MUSIC "./assets/audio/endStateWin.ogg"
#define YOULOSE_BG "./assets/img/lose.jpg"
#define YOULOSE_MUSIC "./assets/audio/endStateLose.ogg"
#define FONT "./assets/font/Call me maybe.ttf"

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <vector>
#include <memory>
#include <iostream>

#include "Sprite.h"
#include "Music.h"
#include "InputManager.h"
#include "Camera.h"
#include "State.h"
#include "GameData.h"
#include "Timer.h"
#include "Text.h"

class EndState : public State{
    private:
        Music backgroundMusic;
        Timer instructionTimer;
        GameObject* instructionText;
    public:
        EndState();
        ~EndState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
};