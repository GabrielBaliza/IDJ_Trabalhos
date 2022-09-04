#include "PenguinCannon.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component::Component(associated){
    angle = 0;
    pbody = penguinBody;
    Sprite* go_sprite = new Sprite(associated, PENGUIN_CANNON);
    associated.AddComponent(go_sprite);
}

void PenguinCannon::Update(float dt){
    if(!pbody.lock()){
        associated.RequestDelete();
        return;
    }
    associated.box.Centralize(pbody.lock().get()->box.Center());
    Vec2 pCenter = associated.box.Center();
    angle = atan2((InputManager::GetInstance().GetMouseY() - pCenter.y + Camera::pos.y), (InputManager::GetInstance().GetMouseX() - pCenter.x + Camera::pos.x));
    associated.angleDeg = (180.0/PI)*angle;
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        Shoot();
    }
}

void PenguinCannon::Render(){}

bool PenguinCannon::Is(std::string type){
    return (type == "PenguinCannon");
}

void PenguinCannon::Shoot(){
    GameObject* go_bullet = new GameObject();
    Bullet* bullet = new Bullet(*go_bullet, angle, PBULLETSPEED, P_DAMAGE, P_MAXDIST, PENGUIN_BULLET, 4, 0.5);

    Vec2 pCannonCenter = associated.box.Center();
    go_bullet->box.Centralize(pCannonCenter);

    go_bullet->box.x += 70*cos(angle) - 30;
    go_bullet->box.y += 70*sin(angle) - 30;
    
    go_bullet->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(go_bullet);
}