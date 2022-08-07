#include "Alien.h"

Alien::Alien(GameObject& associated, int nMinions) : Component::Component(associated){
    Sprite* go_sprite = new Sprite(associated, ALIEN);
    associated.AddComponent(go_sprite);
    associated.box.w = go_sprite->GetWidth();
    associated.box.h = go_sprite->GetHeight();
    speed = {0, 0};
    hp = 100;
}

Alien::~Alien(){
    minionArray.clear();
}

Alien::Action::Action(ActionType type, float x, float y) : type(type), pos({x, y}){}

void Alien::Start(){}

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
            //std::cout << "Mouse X: " << InputManager::GetInstance().GetMouseX() << "   Mouse Y: " << InputManager::GetInstance().GetMouseY() << std::endl;
            taskQueue.pop();
        }
    }
    if(hp <= 0){
        associated.RequestDelete();
    }
}

void Alien::Render(){}

bool Alien::Is(std::string type){
    return (type == "Alien");
}