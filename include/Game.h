#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include "State.h"

class Game{
    private:
        static Game *intance;
        SDL_Window *window;
        SDL_Renderer *renderer;
        State *state;
        Game(std::string title, int whidth, int height);
    public:
        void run();
        ~Game();
        SDL_Renderer *getRenderer();
        State &getState();
        static Game &getInstance();

};