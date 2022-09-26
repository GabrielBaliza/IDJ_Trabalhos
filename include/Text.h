#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF 
#include "SDL_include.h"

#include "Component.h"
#include "GameObject.h"
#include "Camera.h"
#include "Game.h"

#include <iostream>
#include <string>

class Text : public Component{
    public:
        enum TextStyle{SOLID, SHADED, BLENDED};
        Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
        ~Text();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void SetText(std::string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontFile(std::string fonrFile);
        void SetFontSize(int fontSize);
    private:
        std::string fontFile;
        int fontSize;
        TextStyle style;
        std::string text;
        SDL_Color color;
        TTF_Font* font;
        SDL_Texture* texture;
        void RemakeTexture();
    
};