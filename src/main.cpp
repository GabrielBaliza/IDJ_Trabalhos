#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include "Game.h"
#include "StageState.h"
#include <iostream>

int main (int argc, char** argv) {
    Game &jogo = Game::GetInstance();
    jogo.Push(new StageState);
    jogo.Run();
    return 0;
}
