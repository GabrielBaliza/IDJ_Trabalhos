#pragma once

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Resources.h"

#include <string>
#include <iostream>

class Music{
    private:
        Mix_Music *music;
    public:
        Music();
        Music(std::string file);
        ~Music();
        void Play(int time = -1);
        void Stop(int msToStop = 1500);
        void Open(std::string file);
        bool IsOpen();

};