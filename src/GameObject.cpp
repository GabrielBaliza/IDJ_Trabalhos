#include "GameObject.h"

GameObject::GameObject(){
    box = {0, 0, 0, 0};
    isDead = false;
    started = false;
    angleDeg = 0;
}

GameObject::~GameObject(){
    // for(int it = components.size() - 1; it >= 0; it--){}
    components.clear();
}

void GameObject::Update(float dt){
    for(int it = 0; it <= (int)components.size() - 1; it++){
        components[it]->Update(dt);
    }
}

void GameObject::Render(){
    for(int it = 0; it <= (int)components.size() - 1; it++){
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
    if(started == true){
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component* cpt){
    for(int it = components.size() - 1; it != 0; it--){
        if(components[it].get() == cpt){
            components.erase(components.begin()+it);    
            return;
        }       
    }
    
}

Component* GameObject::GetComponent(std::string type){
    for(int it = components.size() - 1; it >= 0; it--){
        if(components[it]->Is(type)){
            return components[it].get();
        }
    }
    return nullptr;

}

void GameObject::Start(){
    for(int it = 0; it <= (int)components.size() - 1; it++){
        components[it]->Start();
    }
    started = true;
}

void GameObject::NotifyCollision(GameObject& other){
    for(int it = components.size() - 1; it >= 0; it--){
        components[it]->NotifyCollision(other);
    }
}