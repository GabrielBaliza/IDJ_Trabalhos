#include <iostream>
#include "TileMap.h"

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component::Component(associated){

}

void TileMap::Load(std::string file){
    return;
}

void TileMap::SetTileSet(TileSet* tileSet){
    return;
}

int& TileMap::At(int x, int y, int z){
    return x;
}

void TileMap::Render(){
    return;
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    return;
}

int TileMap::GetWidth(){
    return mapWidth;
}

int TileMap::GetHeight(){
    return mapHeight;
}

int TileMap::GetDepth(){
    return mapDepth;
}

void TileMap::Update(float dt){
    return;
}

bool TileMap::Is(std::string type){
    if(type == "TileMap"){
        return true;
    }
    else{
        return false;
    }
    
}