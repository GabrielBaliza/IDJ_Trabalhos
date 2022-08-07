#pragma once

#define INCLUDE_SDL 
#include "SDL_include.h"

#include "GameObject.h"

#include <string>

class GameObject;

class Component{
    protected:
        GameObject &associated; 
    public:
        Component(GameObject &associated);
        virtual ~Component();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(std::string type) = 0;
        virtual void Start();
};