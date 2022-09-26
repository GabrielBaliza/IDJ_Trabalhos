#include "Text.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) : Component::Component(associated), fontFile(fontFile), fontSize(fontSize), style(style), text(text), color(color){
    texture = nullptr;
    RemakeTexture();
}

Text::~Text(){
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt){}

void Text::Render(){
    SDL_Rect clipRect = {0, 0, (int)associated.box.w, (int)associated.box.h};
    SDL_Rect destRect = {(int)(associated.box.x + Camera::pos.x), (int)(associated.box.y + Camera::pos.y), clipRect.w, clipRect.h};
    if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0){
        std::cout << "Font rendering error" << std::endl;
        std::cout << SDL_GetError() << std::endl;
    }
    
}

bool Text::Is(std::string type){
    return(type == "Text");
}

void Text::SetText(std::string text){
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color){
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style){
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile){
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize){
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture(){
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    font = Resources::GetFont(fontFile, fontSize);
    SDL_Surface *surface = nullptr;
    if(style == TextStyle::SOLID){
        surface = TTF_RenderText_Solid(font, text.c_str(), color);
    }
    else if(style == TextStyle::SHADED){
        surface = TTF_RenderText_Shaded(font, text.c_str(), color, {0, 0, 0, 255});
    }
    else if(style == TextStyle::BLENDED){
        surface = TTF_RenderText_Blended(font, text.c_str(), color);
    }
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    SDL_SetTextureAlphaMod(texture, color.a);
    if(surface) {
        associated.box.w = surface->w;
        associated.box.h = surface->h;
    }
    SDL_FreeSurface(surface);

}