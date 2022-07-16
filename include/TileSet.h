#pragma once

#include <string>

#include "Sprite.h"
#include "GameObject.h"

class TileSet{
    private:
        Sprite tileSet; 
        int rows;
        int columns;
        int tileWidth;
        int tileHeight;
    public:
        TileSet(int tileWidth, int tileHeight, std::string file);
        void RenderTile(unsigned index, int x, int y);
        int GetTileWidth();
        int GetTileHeight();
};