#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file){
    GameObject* tileGO = new GameObject();
	tileSet = new Sprite(*tileGO, file);
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    columns = (tileSet.GetWidth())/tileWidth;
    rows = (tileSet.GetHeight())/tileHeight;
}

void TileSet::RenderTile(unsigned index, int x, int y){
    int nTiles = columns*rows;
    int renderX, renderY;
    if(index <= (unsigned)(nTiles - 1)){
        renderX = (index%columns)*tileWidth;
        renderY = (index/columns)*tileHeight;
        tileSet.SetClip(renderX, renderY, tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth(){
    return tileWidth;
}

int TileSet::GetTileHeight(){
    return tileHeight;
}