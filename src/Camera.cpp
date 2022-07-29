#define MOV_SPEED 20
#define HSQRT2 0.707

#include "Camera.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos;
Vec2 Camera::speed;

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;    
}

void Camera::Update(float dt){
    speed.x = 0;
    speed.y = 0;
    if(focus != nullptr){
        pos.x = focus->box.x;
        pos.y = focus->box.y;
    }
    else{
        if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) && InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
            speed.x = MOV_SPEED * HSQRT2;
            speed.y = MOV_SPEED * (-HSQRT2);
            //std::cout<< "RU" << std::endl;
        }
        if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) && InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
            speed.x = MOV_SPEED * HSQRT2;
            speed.y = MOV_SPEED * HSQRT2;
            //std::cout<< "RD" << std::endl;
        }
        if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY) && InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
            speed.x = MOV_SPEED * (-HSQRT2);
            speed.y = MOV_SPEED * (-HSQRT2);
            //std::cout<< "LU" << std::endl;
        }
        if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY) && InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
            speed.x = MOV_SPEED * (-HSQRT2);
            speed.y = MOV_SPEED * HSQRT2;
            //std::cout<< "LD" << std::endl;
        }
        if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)){
            speed.x = MOV_SPEED;
            speed.y = 0;
            //std::cout<< "R" << std::endl;
        }
        if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)){
            speed.x = MOV_SPEED * (-1); 
            speed.y = 0;
            //std::cout<< "L" << std::endl;
        }
        if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
            speed.x = 0; 
            speed.y = MOV_SPEED * (-1); 
            //std::cout<< "U" << std::endl;
        }
        if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
            speed.x = 0;
            speed.y = MOV_SPEED;
            //std::cout<< "D" << std::endl;
        }
        pos.x += dt * speed.x;
        pos.y += dt * speed.y;
    }
}
