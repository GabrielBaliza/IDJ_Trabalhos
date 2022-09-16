#include "Minion.h"


Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component::Component(associated), alienCenter(alienCenter){
    
    arc = arcOffsetDeg;
    associated.angleDeg = 90;

    Sprite* go_sprite = new Sprite(associated, MINION);
    float randSize = (rand() % 51 + 100)/100.0;
    go_sprite->SetScale(randSize, randSize);
    Collider *go_collider = new Collider(associated, {0.75, 0.75}, {0, 0});
    
    associated.AddComponent(go_sprite);
    associated.AddComponent(go_collider);
    
    Vec2 posInicial{150, 0};
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
        associated.RequestDelete();
        return;
    }
    else{
        arc += dt * ANG_VEL;
        associated.angleDeg = arc;
        Vec2 posInicial{150, 0};
        posInicial.GetRotated(arc);
        associated.angleDeg = (180/PI)*arc;
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
    float angle = atan2((target.y - minionCenter.y), (target.x - minionCenter.x));
    Bullet* bullet = new Bullet(*go_bullet, angle, BULLETSPEED, MINION_DAMAGE, MAXDIST, BULLET, true, 3, 0.3, {2, 2}, {0.5, 0.6}, {14, 0});
    go_bullet->box.Centralize(minionCenter);
    go_bullet->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(go_bullet);
}

void Minion::NotifyCollision(GameObject& other){
    auto bullet = (Bullet*)other.GetComponent("Bullet");
    if(bullet && !bullet->targetsPlayer){
        Alien* pAlien = (Alien*)alienCenter.lock().get()->GetComponent("Alien");
        pAlien->MinionHit(associated);

        State& state = Game::GetInstance().GetState();
        GameObject* explosion = new GameObject();
        Sprite* go_sprite = new Sprite(*explosion, MINION_DEATH, 4, 0.3, 1.2);
        explosion->box = associated.box;
        explosion->AddComponent(go_sprite);
        state.AddObject(explosion);

        associated.RequestDelete();
        std::cout << "Acertou o Minion" << std::endl;
    }
}