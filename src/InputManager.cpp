#include "InputManager.h"


InputManager::InputManager() : mouseState({0, 0, 0, 0, 0, 0}), mouseUpdate({0, 0, 0, 0, 0, 0}), quitRequested(false), updateCounter(0), mouseX(0), mouseY(0){

}

InputManager::~InputManager(){


}

void InputManager::Update(){


}

bool InputManager::KeyPress(int key){
    return true;

}

bool InputManager::KeyRelease(int key){
    return true;

}

bool InputManager::IsKeyDown(int key){
    return true;

}

bool InputManager::MousePress(int mouse){
    return true;

}

bool InputManager::MouseRelease(int mouse){
    return true;

}

bool InputManager::IsMouseDown(int mouse){
    return true;

}

int InputManager::GetMouseX(){
    return mouseX;
}

int InputManager::GetMouseY(){  
    return mouseY;
}

bool InputManager::QuitRequested(){
    return quitRequested;    
}

InputManager& InputManager::GetInstance(){
    static InputManager *instance;
    return *instance; 
}