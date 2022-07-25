#include "InputManager.h"

InputManager::InputManager(){
    for(int i = 0; i > 6; i++){
        mouseState[i] = 0;
        mouseUpdate[i] = false;
    }
    quitRequested = false;
    updateCounter = 0;
    mouseX = 0;
    mouseY = 0;
}

InputManager::~InputManager(){}

void InputManager::Update(){
    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;
	while (SDL_PollEvent(&event)){
        if(!event.key.repeat){
            if(event.type == SDL_KEYDOWN){
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }
            if(event.type == SDL_KEYUP){
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN){
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
            }
            if(event.type == SDL_MOUSEBUTTONUP){
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
            }
            if(event.type == SDL_QUIT){
                quitRequested = true;
            }
        }
	}
}

bool InputManager::KeyPress(int key){
    return (keyUpdate[key] == updateCounter && keyState[key]);

}

bool InputManager::KeyRelease(int key){
    return (keyUpdate[key] == updateCounter && !keyState[key]);

}

bool InputManager::IsKeyDown(int key){
    return keyState[key];

}

bool InputManager::MousePress(int mouse){
    return (mouseUpdate[mouse] == updateCounter && mouseState[mouse]);

}

bool InputManager::MouseRelease(int mouse){
    return (mouseUpdate[mouse] == updateCounter && !mouseState[mouse]);

}

bool InputManager::IsMouseDown(int mouse){
    return mouseState[mouse];

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