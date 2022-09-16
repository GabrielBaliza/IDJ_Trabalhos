#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include "Game.h"
#include <iostream>

int main (int argc, char** argv) {
    Game &jogoT1 = Game::GetInstance();
    jogoT1.Run();
    return 0;
}
