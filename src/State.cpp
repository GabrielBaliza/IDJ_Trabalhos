#include "State.h"

#define BACKGROUND_AUDIO "./assets/audio/stageState.ogg"
#define BACKGROUND_FRAME "./assets/img/ocean.jpg"
#define MUSIC_TIMESTOPLAY -1 //-1 to continuous

#define clipOriginX 0
#define clipOriginY 0


State::State(){
    quitRequested = false;
    music = Music();
    bg = Sprite();
    LoadAssets();
    music.Play(MUSIC_TIMESTOPLAY);
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::LoadAssets(){
    bg.Open(BACKGROUND_FRAME);
    music.Open(BACKGROUND_AUDIO);
}

void State::Update(float dt){
    if(SDL_QuitRequested() == true){
        quitRequested = true;
    }
    SDL_Delay(dt);
}

void State::Render(){
    bg.Render(clipOriginX ,clipOriginY);
}