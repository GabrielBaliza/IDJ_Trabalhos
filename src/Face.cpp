#include "Face.h"
 
Face::Face(GameObject &associated) : Component::Component(associated), hitpoints(30){}

void Face::Damage(int damage){
    hitpoints -= damage;
    if(hitpoints <= 0){
        Sound* sound = (Sound *)associated.GetComponent("Sound");
        if (sound != nullptr){
            sound->Play();
        }
        associated.RequestDelete();
    }
}

void Face::Update(float dt){
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        if(InputManager::GetInstance().GetMouseX() > associated.box.x && InputManager::GetInstance().GetMouseX() < associated.box.x+associated.box.w){
            if(InputManager::GetInstance().GetMouseY() > associated.box.y && InputManager::GetInstance().GetMouseY() < associated.box.y+associated.box.h){
                Damage(std::rand() % 10 + 10);
            }

        }
    }
}

void Face::Render(){
    return;
}

bool Face::Is(std::string type){
    if(type == "Face"){
        return true;
    }
    else{
        return false;
    }
    
}