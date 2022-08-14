#include "Minion.h"


Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component::Component(associated), alienCenter(alienCenter){
    
    arc = arcOffsetDeg;

    Sprite* go_sprite = new Sprite(associated, MINION);
    associated.AddComponent(go_sprite);
    
    Vec2 posInicial{200, 0};
    posInicial.GetRotated(arc);
    if(!alienCenter.lock()){
        std::cout << "Null GameObject Pointer Error!" << std::endl;
		associated.RequestDelete();
    }
    else{
        posInicial = this->alienCenter.lock()->box.Center() + posInicial;
        associated.box.Centralize(posInicial.x, posInicial.y);
    }
    
}

void Minion::Update(float dt){
    if(!alienCenter.lock()){
        alienCenter.lock()->RequestDelete();
        return;
    }
    else{
        arc += dt * ANG_VEL;
        Vec2 posInicial{200, 0};
        posInicial.GetRotated(arc);
        posInicial = alienCenter.lock()->box.Center() + posInicial;
        associated.box.Centralize(posInicial.x, posInicial.y);
    }
}

void Minion::Render(){}

bool Minion::Is(std::string type){
    return (type == "Minion");
}

void Minion::Shoot(Vec2 target){
    GameObject* go_bullet = new GameObject();
    Vec2 minionCenter = associated.box.Center();
    go_bullet->box.Centralize(minionCenter);
    float angle = atan2((target.y - minionCenter.y), (target.x - minionCenter.x));
    Bullet* bullet = new Bullet(*go_bullet, angle, BULLETSPEED, MINION_DAMAGE, MAXDIST, BULLET);
    go_bullet->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(go_bullet);
}