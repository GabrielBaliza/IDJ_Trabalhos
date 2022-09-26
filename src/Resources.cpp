#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;

SDL_Texture* Resources::GetImage(std::string file){
    std::unordered_map<std::string, SDL_Texture*>::const_iterator it = imageTable.find(file);
    SDL_Texture *texture;
    if(it==imageTable.end()){
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if(texture != nullptr){
            imageTable.emplace(file, texture);
        }
            return texture;
    }
    else{
        return it->second;
    }
}

void Resources::ClearImages(){
    for (auto it : imageTable){
		SDL_DestroyTexture(it.second);
	}
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file){
    std::unordered_map<std::string, Mix_Music*>::const_iterator it = musicTable.find(file);
    Mix_Music *music;
    if(it == musicTable.end()){
        music = Mix_LoadMUS(file.c_str());
        if(music != nullptr){
            musicTable.emplace(file, music);
        }
        return music;
    }
    else{
        return it->second;
    }
}

void Resources::ClearMusics(){
    for (auto it : musicTable) {
		Mix_FreeMusic(it.second);
	}
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file){
    std::unordered_map<std::string, Mix_Chunk*>::const_iterator it = soundTable.find(file);
    Mix_Chunk *chunk;
    if(it == soundTable.end()){
        chunk = Mix_LoadWAV(file.c_str());
        if(chunk != nullptr){
            soundTable.emplace(file, chunk);
        }
        return chunk;
    }
    else{
        return it->second;
    }
}

void Resources::ClearSound(){
    for (auto it : soundTable) {
		Mix_FreeChunk(it.second);
	}
    soundTable.clear();
}

TTF_Font* Resources::GetFont(std::string file, int ptsize){
    std::string key = file + std::to_string(ptsize);
    std::unordered_map<std::string, TTF_Font*>::const_iterator it = fontTable.find(key);
    TTF_Font *font;
    if(it == fontTable.end()){
        font = TTF_OpenFont(file.c_str(), ptsize);
        if(font != nullptr){
            fontTable.emplace(key, font);
        }
        return font;
    }
    else{
        return it->second;
    }
}

void Resources::ClearFonts(){
    for (auto it : fontTable) {
		TTF_CloseFont(it.second);
	}
    fontTable.clear();
}