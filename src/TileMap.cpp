#include "TileMap.h"

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component::Component(associated){
    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load(std::string file){
    std::fstream mapa;
    std::string line;
    int count = 0;
    mapa.open(file, std::fstream::in);
    if(mapa.is_open()){
        std::getline(mapa, line, ',');
        mapWidth = std::stoi(line);
        std::getline(mapa, line, ',');
        mapHeight = std::stoi(line);
        std::getline(mapa, line, ',');
        mapDepth = std::stoi(line);
        while(count < mapDepth*mapHeight*mapWidth){
            std::getline(mapa, line, ',');
            tileMatrix.push_back(std::stoi(line) - 1);  
            count++;
        }
        mapa.close();
    }
    else{
        std::cout << "Erro ao abrir mapa" << std::endl;
    }
    
}

void TileMap::SetTileSet(TileSet* tileSet){
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
    int position = x + mapWidth*y + z*mapWidth*mapHeight;
    return tileMatrix[position];
}

void TileMap::Render(){
    for(int layer = 0; layer < mapDepth; layer++){
        RenderLayer(layer, Camera::pos.x + Camera::pos.x*layer*0.5, Camera::pos.y + Camera::pos.y*layer*0.5);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    for(int tileX = 0; tileX < mapWidth; tileX++){
        for(int tileY = 0; tileY < mapHeight; tileY++){
            tileSet->RenderTile(At(tileX, tileY, layer), (tileX + cameraX)*tileSet->GetTileWidth(), (tileY + cameraY)*tileSet->GetTileHeight());
        }
    }
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
    return(type == "TileMap");
    
}