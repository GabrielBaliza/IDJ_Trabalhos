#include <iostream>
#include "Sound.h"

Sound::Sound(GameObject& associated) : Component::Component(associated), chunk(nullptr){}

Sound::Sound(GameObject& associated, std::string file) : Sound::Sound(associated){
    Open(file);
}

Sound::~Sound(){
    if(IsOpen()){
        Stop();
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times){
    channel = Mix_PlayChannel(-1, chunk, (times-1));
    if (channel == -1){
        std::cout << "Sound/Channel playing error" << std::endl;
        std::cout << SDL_GetError() << std::endl;   
    }
}

void Sound::Stop(){
    if(IsOpen()){
        Mix_HaltChannel(channel);
    }
    
}

void Sound::Open(std::string file){
    chunk = Mix_LoadWAV(file.c_str());
    if(!IsOpen()){
        std::cout << "Sound Openning error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }
}

bool Sound::IsOpen(){
    if(chunk != nullptr){
        return true;
    }
    else{
        return false;
    }
}

void Sound::Update(float dt){
    return;
}

void Sound::Render(){
    return;
}

bool Sound::Is(std::string type){
    if(type == "Sound"){
        return true;
    }
    else{
        return false;
    }
    
}