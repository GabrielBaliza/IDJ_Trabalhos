#include "Game.h" //Game.h inclui State que inclui Sprite.h
#include <iostream>

#define clipOriginX 0
#define clipOriginY 0

Sprite::Sprite(){
    texture = nullptr;
}

Sprite::Sprite(std::string file){
    texture = nullptr;
    Open(file);
}


Sprite::~Sprite(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file){
    if(IsOpen()){
        SDL_DestroyTexture(texture);
    }
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if(!IsOpen()){
        std::cout << "Texture Loading error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }
    else{
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &heigth);
    }   
    SetClip(clipOriginX, clipOriginY, width, heigth);

}


void Sprite::SetClip(int x, int y, int w, int h){
    clipRect = {x, y , w, h};
}

void Sprite::Render(int x, int y){
    SDL_Rect destRect = {x, y, clipRect.w, clipRect.h};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect);
}

int Sprite::GetWidth(){
    return width;
}

int Sprite::GetHeight(){
    return heigth;
}

bool Sprite::IsOpen(){
    if(texture != nullptr){
        return true;
    }
    else{
        return false;
    }
}

