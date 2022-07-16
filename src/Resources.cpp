#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

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