#pragma once

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Component.h"
#include "Resources.h"

#include <iostream>
#include <string>

class Sound : public Component{
    private:
        Mix_Chunk *chunk;
        int channel;
    public:
        Sound(GameObject& associated);
        Sound(GameObject& associated, std::string file);
        ~Sound();
        void Play(int times = 1);
        void Stop();
        void Open(std::string file);
        bool IsOpen();
        bool IsPlaying();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        
};