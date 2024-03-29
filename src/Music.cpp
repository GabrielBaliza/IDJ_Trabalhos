#include "Music.h"


#define FADE_RATE 2000

Music::Music(){
    music = nullptr;
}

Music::Music(std::string file){
    music = nullptr;
    Open(file);
}

Music::~Music(){
    if(IsOpen()){
        Stop(FADE_RATE);
    }
}

void Music::Play(int times){
    if(IsOpen()){
        Mix_PlayMusic(music, times);
    }
    else{
        std::cout << "Music playing error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }
}

void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}


void Music::Open(std::string file){
    music = Resources::GetMusic(file);
    if(!IsOpen()){
        std::cout << "Music Openning error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }

}

bool Music::IsOpen(){
    if(music != nullptr){
        return true;
    }
    else{
        return false;
    }
}
