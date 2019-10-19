#include "../render.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace state;
using namespace render;


TurnDisplay::TurnDisplay(state::Turn& turn):turnDisplay(turn){
        TileSet tilesetMap(Maptile);
        std::unique_ptr<TileSet> ptr_tilesetMap (new TileSet(tilesetMap));
        tilesets.push_back(move(ptr_tilesetMap));

}

void TurnDisplay::initRender(){
        DrawObject DrawMap;
        if(DrawMap.renderMap(turnDisplay,*tilesets[0], turnDisplay.getMap().size(), turnDisplay.getMap()[0].size(), tilesets[0]->getXsize(), tilesets[0]->getYsize())){
        std::unique_ptr<DrawObject> ptr_drawMap (new DrawObject(DrawMap));
        drawobjects.push_back(move(ptr_drawMap));
        }

}

std::vector<std::unique_ptr<render::TileSet>>& TurnDisplay::getTilesets (){
        std::vector<std::unique_ptr<TileSet>>& mytilesets = tilesets;
        return mytilesets;
}

std::vector<std::unique_ptr<render::DrawObject>>& TurnDisplay::getDrawobjects (){
        std::vector<std::unique_ptr<DrawObject>>& mydrawobjects = drawobjects;
        return mydrawobjects;
}
