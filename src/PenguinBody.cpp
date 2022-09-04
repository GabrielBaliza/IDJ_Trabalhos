#include "PenguinBody.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component::Component(associated){
    speed = 0;
    linearSpeed = 0;
    angle = 0;
    hp = 50;

    Sprite* go_sprite = new Sprite(associated, PENGUIN_BODY);
    associated.AddComponent(go_sprite);

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
        pcannon.lock().get()->RequestDelete();
        associated.RequestDelete();
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