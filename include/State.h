#include "Sprite.h"
#include "Music.h"

class State{
    private:
        Sprite bg;
        Music music;
        bool quitRequested;
    public:
        State();
        bool quitRequested();
        void loadAssets();
        void update(float dt);
        void render();

};