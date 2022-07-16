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
    return;
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