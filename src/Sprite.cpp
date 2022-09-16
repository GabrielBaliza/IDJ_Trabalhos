#include "Game.h"

#define clipOriginX 0
#define clipOriginY 0

Sprite::Sprite(GameObject& associated) : Component::Component(associated), texture(nullptr){
    scale = {1.0, 1.0};
}

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component::Component(associated), texture(nullptr), frameCount(frameCount), frameTime(frameTime), secondsToSelfDestruct(secondsToSelfDestruct){
    scale = {1.0, 1.0};
    currentFrame = 0;
    timeElapsed = 0;
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
    SetClip(clipOriginX, clipOriginY, width/frameCount, heigth);
    associated.box.w = GetWidth();
    associated.box.h = GetHeight();

}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect = {x, y, w, h};
}

void Sprite::Render(){
    //Render((int)associated.box.x, (int)associated.box.y);
    Render((int)associated.box.x - Camera::pos.x, (int)associated.box.y - Camera::pos.y);
}

void Sprite::Render(int x, int y){
    //associated.box = {(float) clipOriginX,(float) clipOriginY,(float) clipRect.w,(float) clipRect.h};
    SDL_Rect destRect = {x, y, (int)(clipRect.w*scale.x), (int)(clipRect.h*scale.y)};
    if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0){
        std::cout << "Rendering error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
    }

}

int Sprite::GetWidth(){
    return (int)(width*scale.x/frameCount);
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
    timeElapsed += dt;
    if(timeElapsed >= frameTime){
        currentFrame++;
        timeElapsed = 0;
        if(currentFrame >= frameCount){
            currentFrame = 0;
        }
        SetFrame(currentFrame);
    }
    if(secondsToSelfDestruct > 0){
        selfDestructCount.Update(dt);
        if(selfDestructCount.Get() > secondsToSelfDestruct){
            associated.RequestDelete();
        }
    }
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


void Sprite::SetFrame(int frame){
    currentFrame = frame;
    SetClip(currentFrame*width/frameCount, clipOriginY, width/frameCount, heigth);
}

void Sprite::SetFrameCount(int frameCount){
    this->frameCount = frameCount;
    currentFrame = 0;
    SetFrame(currentFrame);
}

void Sprite::SetFrameTime(float frameTime){
    this->frameTime = frameTime;   
}