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

void TurnDisplay::initRender(int rotation){
        while (!drawchars.empty()){
        drawchars.pop_back();
        }
        while (!drawmaps.empty()){
        drawmaps.pop_back();
        }
        std::vector<std::vector<state::Tile>> rotateMapVector(turnDisplay.getMap());
        DrawObject RotMap;
        for (int i=0; i<rotation; i++){
                rotateMapVector = RotMap.rotateMap(rotateMapVector,rotateMapVector.size());
        }

        vector<vector<int>> map_segmentation;
        for (int k=0; k< (int) turnDisplay.getTeams()[0]->getListCharacter().size(); k++) {
                vector<int> coord;
                coord.push_back(turnDisplay.getTeams()[0]->getListCharacter()[k]->getPosition().getX());
                coord.push_back(turnDisplay.getTeams()[0]->getListCharacter()[k]->getPosition().getY());
                map_segmentation.push_back(coord);
        }
        vector<int> lastcoord;
        lastcoord.push_back(turnDisplay.getMap().size());
        lastcoord.push_back(turnDisplay.getMap()[0].size());
        map_segmentation.push_back(lastcoord);

        sort(map_segmentation.begin(),map_segmentation.end());
        for (int k=0; k< (int) map_segmentation.size(); k++) {
                cout << "map_segmentation "<< k <<" x: " << map_segmentation[k][0] << " | ";
                cout <<" y: " << map_segmentation[k][1] << endl;
        }
        vector<int> segStart(2,0),segEnd(2,0);
        for (int l=0; l< (int) map_segmentation.size(); l++){  
                segStart[0]=segEnd[0],segStart[1]=segEnd[1];
                segEnd[0]=(map_segmentation[l][0]),segEnd[1]=(map_segmentation[l][1]);
                cout << "region begin:"<< segStart[0] <<" | " << segStart[1] << endl;
                cout << "region end:"<< segEnd[0] <<" | " << segEnd[1] << endl;
                for (int k=1; k<4; k++){
                        DrawObject DrawMap;
                        if(DrawMap.renderMapWalls(rotateMapVector,*tilesets[0], {(int)turnDisplay.getMap().size(),
                                                                        (int) turnDisplay.getMap()[0].size()}, 
                                                                        {tilesets[0]->getXsize(), tilesets[0]->getYsize()},
                                                                        tilesets[0]->getMargin(),k,rotation,
                                                                        segStart,segEnd)){
                                std::unique_ptr<DrawObject> ptr_drawMapWallsbis (new DrawObject(DrawMap));
                                drawmaps.push_back(move(ptr_drawMapWallsbis));
                                DrawObject DrawMap;
                                if(DrawMap.renderMapBase(rotateMapVector,*tilesets[0], {(int)turnDisplay.getMap().size(),
                                                                                (int) turnDisplay.getMap()[0].size()}, 
                                                                                {tilesets[0]->getXsize(), tilesets[0]->getYsize()},
                                                                                tilesets[0]->getMargin(),k,rotation,
                                                                                segStart,segEnd)){
                                        std::unique_ptr<DrawObject> ptr_drawMap (new DrawObject(DrawMap));
                                        drawmaps.push_back(move(ptr_drawMap));
                                }
                        }
                }
        }
        for (int k=0; k< (int) turnDisplay.getTeams()[0]->getListCharacter().size(); k++){
                DrawObject DrawChar;
                std::vector<std::unique_ptr<render::DrawObject>> charframe;
                for (size_t i = 0; i < 6; i++)
                {
                        DrawChar.renderCharacter(turnDisplay,*tilesets[1], turnDisplay.getMap().size(),
                                                                            turnDisplay.getMap()[0].size(), 
                                                                            tilesets[1]->getXsize(), tilesets[1]->getYsize(),
                                                                            tilesets[1]->getMargin(),i,k,rotation);
                        std::unique_ptr<DrawObject> ptr_drawChar (new DrawObject(DrawChar));
                        charframe.push_back(move(ptr_drawChar));
                }
                drawchars.push_back(move(charframe));
        }
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
