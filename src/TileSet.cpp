#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file){
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    GameObject* tileGO = new GameObject();
	tileSet = new Sprite(*tileGO, file);
    columns = (tileSet->GetWidth())/tileWidth;
    rows = (tileSet->GetHeight())/tileHeight;
}

void TileSet::RenderTile(unsigned index, int x, int y){
    int nTiles = columns*rows;
    int renderX, renderY;
    if(index <= (unsigned)(nTiles - 1)){
        renderX = index%columns + 1;
        renderY = index/rows;
        tileSet->SetClip(renderX, renderY, tileWidth, tileHeight);
        tileSet->Render(x, y);
    }
}

int TileSet::GetTileWidth(){
    return tileWidth;
}

int TileSet::GetTileHeight(){
    return tileHeight;
}