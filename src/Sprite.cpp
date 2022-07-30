#include "Game.h"

#define clipOriginX 0
#define clipOriginY 0

Sprite::Sprite(GameObject& associated) : Component::Component(associated), texture(nullptr){}

Sprite::Sprite(GameObject& associated, std::string file) : Component::Component(associated), texture(nullptr){
    Open(file);
}

Sprite::~Sprite(){}

void Sprite::Open(std::string file){
    texture = Resources::GetImage(file);
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
    associated.box.w = w;
    associated.box.h = h;
}

void Sprite::Render(){
    //Render((int)associated.box.x, (int)associated.box.y);
    Render((int)associated.box.x - Camera::pos.x, (int)associated.box.y - Camera::pos.y);
}

void Sprite::Render(int x, int y){
    //associated.box = {(float) clipOriginX,(float) clipOriginY,(float) clipRect.w,(float) clipRect.h};
    SDL_Rect destRect = {x, y, clipRect.w, clipRect.h};
    if(SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect) != 0){
        std::cout << "Rendering error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
    }

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

void Sprite::Update(float dt){
    return;
}

bool Sprite::Is(std::string type){
    return(type == "Sprite");
}