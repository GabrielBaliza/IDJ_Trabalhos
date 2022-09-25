#include "PenguinCannon.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component::Component(associated){
    angle = 0;
    pbody = penguinBody;
    
    Sprite* go_sprite = new Sprite(associated, PENGUIN_CANNON);
    Collider *go_collider = new Collider(associated, {0.5, 1}, {-27, 0});
    associated.AddComponent(go_sprite);
    associated.AddComponent(go_collider);
}

void PenguinCannon::Update(float dt){
    cooldown.Update(dt);
    if(!pbody.lock()){
        associated.RequestDelete();
        return;
    }
    associated.box.Centralize(pbody.lock().get()->box.Center());
    Vec2 pCenter = associated.box.Center();
    angle = atan2((InputManager::GetInstance().GetMouseY() - pCenter.y + Camera::pos.y), (InputManager::GetInstance().GetMouseX() - pCenter.x + Camera::pos.x));
    associated.angleDeg = (180.0/PI)*angle;
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) && cooldown.Get() >= COOLDOWNTIME){
        Shoot();
    }
}

void PenguinCannon::Render(){}

bool PenguinCannon::Is(std::string type){
    return (type == "PenguinCannon");
}

void PenguinCannon::Shoot(){
    cooldown.Restart();
    GameObject* go_bullet = new GameObject();
    Bullet* bullet = new Bullet(*go_bullet, angle, PBULLETSPEED, P_DAMAGE, P_MAXDIST, PENGUIN_BULLET, false, 4, 0.5, {1.3, 1.3}, {0.9, 0.9});

    Vec2 pCannonCenter = associated.box.Center();
    go_bullet->box.Centralize(pCannonCenter);

    go_bullet->box.x += 70*cos(angle) - 30;
    go_bullet->box.y += 70*sin(angle) - 30;
    
    go_bullet->AddComponent(bullet);
    Game::GetInstance().GetCurrentState().AddObject(go_bullet);
}

void PenguinCannon::NotifyCollision(GameObject& other){
    auto bullet = (Bullet*)other.GetComponent("Bullet");
    if(bullet && bullet->targetsPlayer){
        PenguinBody* tpbody = (PenguinBody*)pbody.lock().get()->GetComponent("PenguinBody");
        tpbody->ExternalDamage(bullet->GetDamage({0,0}));
    }
}