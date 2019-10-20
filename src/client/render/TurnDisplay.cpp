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

        TileSet tilesetPersonnages(CharaSpritesheet);
	std::unique_ptr<TileSet> ptr_tilesetPersonnages (new TileSet(tilesetPersonnages));
	tilesets.push_back(move(ptr_tilesetPersonnages));
}

void TurnDisplay::initRender(){
        DrawObject DrawMap;
        if(DrawMap.renderMapBase(turnDisplay,*tilesets[0], turnDisplay.getMap().size(), turnDisplay.getMap()[0].size(), tilesets[0]->getXsize(), tilesets[0]->getYsize(),tilesets[0]->getMargin())){
                std::unique_ptr<DrawObject> ptr_drawMap (new DrawObject(DrawMap));
                drawmaps.push_back(move(ptr_drawMap));
                if(DrawMap.renderMapWalls(turnDisplay,*tilesets[0], turnDisplay.getMap().size(), turnDisplay.getMap()[0].size(), tilesets[0]->getXsize(), tilesets[0]->getYsize(),tilesets[0]->getMargin(),0)){
                        std::unique_ptr<DrawObject> ptr_drawMapWalls (new DrawObject(DrawMap));
                        drawmaps.push_back(move(ptr_drawMapWalls));
                        if(DrawMap.renderMapWalls(turnDisplay,*tilesets[0], turnDisplay.getMap().size(), turnDisplay.getMap()[0].size(), tilesets[0]->getXsize(), tilesets[0]->getYsize(),tilesets[0]->getMargin(),1)){
                                std::unique_ptr<DrawObject> ptr_drawMapWallsbis (new DrawObject(DrawMap));
                                drawmaps.push_back(move(ptr_drawMapWallsbis));
                        }
                }
        }
        DrawObject DrawChar;
        std::vector<std::unique_ptr<render::DrawObject>> charframe;
        for (size_t i = 0; i < 4; i++)
        {
                DrawChar.renderCharacter(turnDisplay,*tilesets[1], turnDisplay.getMap().size(), turnDisplay.getMap()[0].size(), tilesets[1]->getXsize(), tilesets[1]->getYsize(),tilesets[1]->getMargin());
                std::unique_ptr<DrawObject> ptr_drawChar (new DrawObject(DrawChar));
                charframe.push_back(move(ptr_drawChar));
        }
        drawchars.push_back(move(charframe));
                
}

std::vector<std::unique_ptr<render::TileSet>>& TurnDisplay::getTilesets (){
        std::vector<std::unique_ptr<TileSet>>& mytilesets = tilesets;
        return mytilesets;
}

std::vector<std::unique_ptr<render::DrawObject>>& TurnDisplay::getDrawmaps (){
        std::vector<std::unique_ptr<DrawObject>>& mydrawobjects = drawmaps;
        return mydrawobjects;
}

std::vector<std::vector<std::unique_ptr<render::DrawObject>>>& TurnDisplay::getDrawchars (){
        std::vector<std::vector<std::unique_ptr<DrawObject>>>& mydrawobjects = drawchars;
        return mydrawobjects;
}