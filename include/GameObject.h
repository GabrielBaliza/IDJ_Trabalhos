#pragma once

#include "Rect.h"
#include "Component.h"

#include <string>
#include <vector>
#include <memory>

class Component;

class GameObject{
    private:
        bool isDead;
        std::vector<std::unique_ptr<Component>> components;
    public:
        GameObject();
        ~GameObject();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);
        Rect box;
        bool started;
        void Start();
        double angleDeg;
};