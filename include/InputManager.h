#pragma once

#define LEFT_ARROW_KEY
#define RIGHT_ARROW_KEY
#define UP_ARROW_KEY
#define DOWN_ARROW_KEY
#define ESCAPE_KEY
#define LEFT_MOUSE_BUTTON
#define SDLK_LEFT
#define SDLK_RIGHT
#define SDLK_UP
#define SDLK_DOWN
#define SDLK_ESCAPE
#define SDL_BUTTON_LEFT

#include <unordered_map>

class InputManager{
    private:
        bool mouseState[6];
        int mouseUpdate[6];
        std::unordered_map<int, bool> keyState;
        std::unordered_map<int, int> keyUpdate;
        bool quitRequested;
        int updateCounter;
        int mouseX;
        int mouseY;
    public:
        InputManager();
        ~InputManager();
        static InputManager& GetInstance();
        void Update();
        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);
        bool MousePress(int mouse);
        bool MouseRelease(int mouse);
        bool IsMouseDown(int mouse);
        int GetMouseX();
        int GetMouseY();
        bool QuitRequested();
};