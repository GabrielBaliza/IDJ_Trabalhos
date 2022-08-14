#include "Game.h"

#define clipOriginX 0
#define clipOriginY 0

Sprite::Sprite(GameObject& associated) : Component::Component(associated), texture(nullptr){
    scale = {1.0, 1.0};
}

Sprite::Sprite(GameObject& associated, std::string file) : Component::Component(associated), texture(nullptr){
    scale = {1.0, 1.0};
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
    SDL_Rect destRect = {x, y, (int)clipRect.w*(int)scale.x, (int)clipRect.h*(int)scale.y};
    if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0){
        std::cout << "Rendering error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
    }

}

int Sprite::GetWidth(){
    return (int)(width*scale.x);
}

int Sprite::GetHeight(){
    return (int)(heigth*scale.y);
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

Vec2 Sprite::GetScale(){
    return scale;
}

void Sprite::SetScale(float scaleX, float scaleY){
    scale.x = (scaleX > 0) ? scaleX : scale.x;
    scale.y = (scaleY > 0) ? scaleY : scale.y;
    Vec2 prevCenter = associated.box.Center();
    associated.box.w = GetWidth();
    associated.box.h = GetHeight();

    associated.box.Centralize(prevCenter);
}