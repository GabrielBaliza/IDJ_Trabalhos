#include "Alien.h"

Alien::Alien(GameObject& associated, int nMinions) : Component::Component(associated){
    Sprite* go_sprite = new Sprite(associated, ALIEN);
    associated.AddComponent(go_sprite);
    speed = {0, 0};
    hp = MAXHP;
    minionArray.resize(nMinions);
}

Alien::~Alien(){
    minionArray.clear();
}

Alien::Action::Action(ActionType type, float x, float y) : type(type), pos({x, y}){}

void Alien::Start(){
    State& state = Game::GetInstance().GetState();
    for(int i = 0; i < (int) minionArray.size(); i++){
        float distribute = PI2*i/minionArray.size();
        GameObject* go = new GameObject();
        Minion* go_Minion = new Minion(*go, state.GetObjectPtr(&associated), distribute);
        go->AddComponent(go_Minion);
        minionArray[i] = state.AddObject(go);
    }
}

void Alien::Update(float dt){
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        Action objAction(Action::ActionType::SHOOT, InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y);
        taskQueue.push(objAction);
    }
    if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)){
        Action objAction(Action::ActionType::MOVE, InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y);
        taskQueue.push(objAction);
    }
    if(taskQueue.size() >= 1){
        if(taskQueue.front().type == Action::ActionType::MOVE){
            float dist;
            dist = sqrt(pow((taskQueue.front().pos.x - (associated.box.x + associated.box.w/2)), 2.0) + pow((taskQueue.front().pos.y - (associated.box.y + associated.box.h/2)), 2.0));
            speed.x = SPEED*(taskQueue.front().pos.x - (associated.box.x + associated.box.w/2))/dist;
            speed.y = SPEED*(taskQueue.front().pos.y - (associated.box.y + associated.box.h/2))/dist;
            associated.box.x += dt*speed.x;
            associated.box.y += dt*speed.y;
            if(dist <= dt * SPEED){
                associated.box.x = taskQueue.front().pos.x - associated.box.w/2;
                associated.box.y = taskQueue.front().pos.y - associated.box.h/2;
                taskQueue.pop();
            }
        }
        else if(taskQueue.front().type == Action::ActionType::SHOOT){
            if(minionArray.size() > 0){
                int randMinion = std::rand() % minionArray.size();
                Minion* cMinion = (Minion*)minionArray[randMinion].lock().get()->GetComponent("Minion");
                cMinion->Shoot(taskQueue.front().pos);
            }
            taskQueue.pop();    
        }
    }
    associated.angleDeg -= dt * ALIEN_ANG_VEL;
    if(hp <= 0){
        associated.RequestDelete();
    }
}

void Alien::Render(){}

bool Alien::Is(std::string type){
    return (type == "Alien");
}