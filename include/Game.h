#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "State.h"
#include "SDL_include.h"
#include <string>


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