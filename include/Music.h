#define INCLUDE_SDL_MIXER

#include "SDL_include.h"

class Music{
    private:
        Mix_Music *music;
    public:
        Music();
        Music(std::string file);
        void play(int time = -1);
        void stop(int msToStop = 1500);
        void open(std::string file);
        bool isOpen();

};