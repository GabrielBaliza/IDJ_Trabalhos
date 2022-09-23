#include "PenguinBody.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component::Component(associated){
    speed = 0;
    linearSpeed = 0;
    angle = 0;
    hp = 50;

    Sprite* go_sprite = new Sprite(associated, PENGUIN_BODY);
    Collider *go_collider = new Collider(associated, {0.75, 0.75}, {-5, 0});
    associated.AddComponent(go_sprite);
    associated.AddComponent(go_collider);

    player = this;
}

PenguinBody::~PenguinBody(){
    player = nullptr;
}

void PenguinBody::Start(){
    GameObject* go = new GameObject();
    State& state = Game::GetInstance().GetState();
    PenguinCannon* go_pcannon = new PenguinCannon(*go, state.GetObjectPtr(&associated));
    go->AddComponent(go_pcannon);
    pcannon = state.AddObject(go);
}

void PenguinBody::Update(float dt){
    if(hp <= 0){
        State& state = Game::GetInstance().GetState();
        GameObject* explosion = new GameObject();
        Sprite* go_sprite = new Sprite(*explosion, PENGUIN_DEATH, 5, 0.2, 1);
        Sound* boom = new Sound(*explosion, BOOM);
        explosion->box = associated.box;
        explosion->AddComponent(go_sprite);
        explosion->AddComponent(boom);
        state.AddObject(explosion);
        boom->Play();
        pcannon.lock().get()->RequestDelete();
        associated.RequestDelete();
        Camera::Unfollow();
        return;
    }
    if(InputManager::GetInstance().IsKeyDown(W_KEY)){
        linearSpeed += ACCELERATION*dt;
        if(linearSpeed > MAXSPEED){
            linearSpeed = MAXSPEED;
        }
    }
    else if(InputManager::GetInstance().IsKeyDown(S_KEY)){
        linearSpeed -= ACCELERATION*dt;
        if(linearSpeed < -1*MAXSPEED){
            linearSpeed = -1*MAXSPEED;
        }
    }
    else{
        if(linearSpeed > 0){
            linearSpeed -= DESACCELERATION*dt;
        }
        if(linearSpeed < 0){
            linearSpeed += DESACCELERATION*dt;
        }

    }
    if(InputManager::GetInstance().IsKeyDown(A_KEY)){
        angle -= ANG_SPEED * dt;
    }
    else if(InputManager::GetInstance().IsKeyDown(D_KEY)){
        angle += ANG_SPEED * dt;
    }

    speed = {linearSpeed, 0};
    speed.GetRotated(angle);
    associated.angleDeg = (180/PI)*angle;
    associated.box.x += speed.x*dt;
    associated.box.y += speed.y*dt;
}

void PenguinBody::Render(){}

bool PenguinBody::Is(std::string type){
    return (type == "PenguinBody");
}

void PenguinBody::ExternalDamage(int damage){
    hp -= damage;
    std::cout << "Baby hit!" << std::endl;
    std::cout << "Player HP: " << hp << std::endl;
}

void PenguinBody::NotifyCollision(GameObject& other){
    auto bullet = (Bullet*)other.GetComponent("Bullet");
    auto minion = (Minion*)other.GetComponent("Minion");
    auto alien = (Alien*)other.GetComponent("Alien");
    if(bullet && bullet->targetsPlayer){
        hp -= bullet->GetDamage({0,0});
        std::cout << "Player HP: " << hp << std::endl;
    }
    if(alien || minion){
        hp -= DMGCOLL;
        std::cout << "Player HP: " << hp << std::endl;
    }

}

Vec2 PenguinBody::PlayerPos(){
    return associated.box.Center();
}