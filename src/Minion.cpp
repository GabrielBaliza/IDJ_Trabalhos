#include "Minion.h"


Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component::Component(associated), alienCenter(*alienCenter.lock()){
    Sprite* go_sprite = new Sprite(associated, MINION);
    associated.AddComponent(go_sprite);
    associated.box.w = go_sprite->GetWidth();
    associated.box.h = go_sprite->GetHeight();
    
    arc = arcOffsetDeg;
    
    Vec2 posInicial{200, 0};
    posInicial.GetRotated(arc);
    posInicial = this->alienCenter.box.Center() + posInicial;
    associated.box.Centralize(posInicial.x, posInicial.y);
}

void Minion::Update(float dt){
    if(alienCenter.IsDead()){
        alienCenter.RequestDelete();
        return;
    }
    arc += dt* ANG_VEL;
    Vec2 posInicial{200, 0};
    posInicial.GetRotated(arc);
    posInicial = alienCenter.box.Center() + posInicial;
    associated.box.Centralize(posInicial.x, posInicial.y);
}

void Minion::Render(){}

bool Minion::Is(std::string type){
    return (type == "Minion");
}

void Minion::Shoot(Vec2 target){

}