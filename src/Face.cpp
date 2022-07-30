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
        if(associated.box.Contains(InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
                Damage(std::rand() % 10 + 10);
        }

        
    }
}

void Face::Render(){

}

bool Face::Is(std::string type){
    return (type == "Face");
    
}