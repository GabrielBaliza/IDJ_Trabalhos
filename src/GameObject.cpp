#include "GameObject.h"

GameObject::GameObject(){
    box = {0, 0, 0, 0};
    isDead = false;
}

GameObject::~GameObject(){
    // for(unsigned short int it = components.size() - 1; it != 0; it--){}
    components.clear();
}

void GameObject::Update(float dt){
    for(unsigned short int it = components.size() - 1; it != 0; it--){
        components[it]->Update(dt);
    }
}

void GameObject::Render(){
    for(unsigned short int it = components.size() - 1; it != 0; it--){
        components[it]->Render();
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(Component* cpt){
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt){
    for(unsigned short int it = components.size() - 1; it != 0; it--){
        if(components[it].get() == cpt){
            components.erase(components.begin()+it);    
            return;
        }       
    }
    
}

Component* GameObject::GetComponent(std::string type){
    for(unsigned short int it = components.size() - 1; it != 0; it--){
        if(components[it]->Is(type)){
            return components[it].get();
        }
    }
    return nullptr;

}

