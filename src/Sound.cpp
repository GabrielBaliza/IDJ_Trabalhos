#include "Sound.h"

Sound::Sound(GameObject& associated) : Component::Component(associated), chunk(nullptr){}

Sound::Sound(GameObject& associated, std::string file) : Sound::Sound(associated){
    Open(file);
}

Sound::~Sound(){
    if(IsOpen() && !IsPlaying()){
        Stop();
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
    chunk = Resources::GetSound(file);
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

bool Sound::IsPlaying(){
    if(channel >= 0){
        if(Mix_Playing(channel) != 0){
            return true;
        }
    }
    return false;
}

void Sound::Update(float dt){
    return;
}

void Sound::Render(){
    return;
}

bool Sound::Is(std::string type){
    return(type == "Sound");
    
}