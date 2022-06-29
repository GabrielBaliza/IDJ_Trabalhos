#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"

class State{
    private:
        SDL_Texture *texture;
        int width;
        int heigth;
        SDL_Rect clipRect;
    public:
        Sprite();
        Sprite(std::string file);
        ~Sprite();
        void open(std::string);
        void setClip(int x, int y, int w, int h);
        void render(int x, int y);
        int getWidth();
        int getHeight();
        bool isOpen();

};