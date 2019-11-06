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
        while (!drawchars.empty()){
        drawchars.pop_back();
        }
        while (!drawmaps.empty()){
        drawmaps.pop_back();
        }
        std::vector<std::vector<state::Tile>> rotateMapVector(turnDisplay.getMap());
        DrawObject RotMap;
        for (int i=0; i<turnDisplay.rotation; i++){
                rotateMapVector = RotMap.rotateMap(rotateMapVector,rotateMapVector.size());
        }
        
        vector<vector<int>> map_segmentation;
        for (size_t i = 0; i < turnDisplay.getTeams().size(); i++){
                for (int k=0; k< (int) turnDisplay.getTeams()[i]->getListCharacter().size(); k++) {
                        vector<int> coord;
                        coord.push_back(turnDisplay.getTeams()[i]->getListCharacter()[k]->getPosition().getX());
                        coord.push_back(turnDisplay.getTeams()[i]->getListCharacter()[k]->getPosition().getY());
                        int temp=0;
                        for (int q=0; q<turnDisplay.rotation; q++){
                                temp=coord[0];
                                coord[0]=turnDisplay.getMap().size()-coord[1]-1;
                                coord[1]=temp;
                        }
                        map_segmentation.push_back(coord);
                }
        }
        vector<int> lastcoord;
        lastcoord.push_back(turnDisplay.getMap().size());
        lastcoord.push_back(turnDisplay.getMap()[0].size());
        map_segmentation.push_back(lastcoord);

        sort(map_segmentation.begin(),map_segmentation.end());
        // for (int k=0; k< (int) map_segmentation.size(); k++) {
        //         cout << "map_segmentation "<< k <<" x: " << map_segmentation[k][0] << " | ";
        //         cout <<" y: " << map_segmentation[k][1] << endl;
        // }
        vector<int> segStart(2,0),segEnd(2,0);
        for (int l=0; l< (int) map_segmentation.size(); l++){
                segStart[0]=segEnd[0],segStart[1]=segEnd[1];
                segEnd[0]=(map_segmentation[l][0]),segEnd[1]=(map_segmentation[l][1]);
                // cout << "region begin:"<< segStart[0] <<" | " << segStart[1] << endl;
                // cout << "region end:"<< segEnd[0] <<" | " << segEnd[1] << endl;
                for (int k=1; k<4; k++){
                        DrawObject DrawMap;
                        if(DrawMap.renderMapWalls(rotateMapVector,*tilesets[0], {(int)turnDisplay.getMap().size(),
                                                                        (int) turnDisplay.getMap()[0].size()},
                                                                        {tilesets[0]->getXsize(), tilesets[0]->getYsize()},
                                                                        tilesets[0]->getMargin(),k,
                                                                        segStart,segEnd)){
                                std::unique_ptr<DrawObject> ptr_drawMapWallsbis (new DrawObject(DrawMap));
                                drawmaps.push_back(move(ptr_drawMapWallsbis));
                                DrawObject DrawMap;
                                if(DrawMap.renderMapBase(rotateMapVector,*tilesets[0], {(int)turnDisplay.getMap().size(),
                                                                                (int) turnDisplay.getMap()[0].size()},
                                                                                {tilesets[0]->getXsize(), tilesets[0]->getYsize()},
                                                                                tilesets[0]->getMargin(),k,
                                                                                segStart,segEnd)){
                                        std::unique_ptr<DrawObject> ptr_drawMap (new DrawObject(DrawMap));
                                        drawmaps.push_back(move(ptr_drawMap));
                                }
                        }
                }
        }
        for (size_t player = 0; player < turnDisplay.getTeams().size(); player++){
                for (int k=0; k< (int) turnDisplay.getTeams()[player]->getListCharacter().size(); k++){
                        DrawObject DrawChar;
                        std::vector<std::unique_ptr<render::DrawObject>> charframe;
                        for (size_t spriteAnimNumber = 0; spriteAnimNumber < 6; spriteAnimNumber++)
                        {
                                DrawChar.renderCharacter(turnDisplay,*tilesets[1], turnDisplay.getMap().size(),
                                                                                turnDisplay.getMap()[0].size(),
                                                                                tilesets[1]->getXsize(), tilesets[1]->getYsize(),
                                                                                tilesets[1]->getMargin(),spriteAnimNumber,k,player);
                                std::unique_ptr<DrawObject> ptr_drawChar (new DrawObject(DrawChar));
                                charframe.push_back(move(ptr_drawChar));
                        }
                        drawchars.push_back(move(charframe));
                }
        }
}

void TurnDisplay::initRender(state::Turn& turn){
        while (!drawchars.empty()){
        drawchars.pop_back();
        }
        while (!drawmaps.empty()){
        drawmaps.pop_back();
        }
        std::vector<std::vector<state::Tile>> rotateMapVector(turn.getMap());
        DrawObject RotMap;
        for (int i=0; i<turn.rotation; i++){
                rotateMapVector = RotMap.rotateMap(rotateMapVector,rotateMapVector.size());
        }

        vector<vector<int>> map_segmentation;
        for (size_t i = 0; i < turn.getTeams().size(); i++){
                for (int k=0; k< (int) turn.getTeams()[i]->getListCharacter().size(); k++) {
                        vector<int> coord;
                        coord.push_back(turn.getTeams()[i]->getListCharacter()[k]->getPosition().getX());
                        coord.push_back(turn.getTeams()[i]->getListCharacter()[k]->getPosition().getY());
                        int temp=0;
                        for (int q=0; q<turn.rotation; q++){
                                temp=coord[0];
                                coord[0]=turn.getMap().size()-coord[1]-1;
                                coord[1]=temp;
                        }
                        map_segmentation.push_back(coord);
                }
        }
        vector<int> lastcoord;
        lastcoord.push_back(turn.getMap().size());
        lastcoord.push_back(turn.getMap()[0].size());
        map_segmentation.push_back(lastcoord);

        sort(map_segmentation.begin(),map_segmentation.end());
        // for (int k=0; k< (int) map_segmentation.size(); k++) {
        //         cout << "map_segmentation "<< k <<" x: " << map_segmentation[k][0] << " | ";
        //         cout <<" y: " << map_segmentation[k][1] << endl;
        // }
        vector<int> segStart(2,0),segEnd(2,0);
        for (int l=0; l< (int) map_segmentation.size(); l++){
                segStart[0]=segEnd[0],segStart[1]=segEnd[1];
                segEnd[0]=(map_segmentation[l][0]),segEnd[1]=(map_segmentation[l][1]);
                // cout << "region begin:"<< segStart[0] <<" | " << segStart[1] << endl;
                // cout << "region end:"<< segEnd[0] <<" | " << segEnd[1] << endl;
                for (int k=1; k<4; k++){
                        DrawObject DrawMap;
                        if(DrawMap.renderMapWalls(rotateMapVector,*tilesets[0], {(int)turn.getMap().size(),
                                                                        (int) turn.getMap()[0].size()},
                                                                        {tilesets[0]->getXsize(), tilesets[0]->getYsize()},
                                                                        tilesets[0]->getMargin(),k,
                                                                        segStart,segEnd)){
                                std::unique_ptr<DrawObject> ptr_drawMapWallsbis (new DrawObject(DrawMap));
                                drawmaps.push_back(move(ptr_drawMapWallsbis));
                                DrawObject DrawMap;
                                if(DrawMap.renderMapBase(rotateMapVector,*tilesets[0], {(int)turn.getMap().size(),
                                                                                (int) turn.getMap()[0].size()},
                                                                                {tilesets[0]->getXsize(), tilesets[0]->getYsize()},
                                                                                tilesets[0]->getMargin(),k,
                                                                                segStart,segEnd)){
                                        std::unique_ptr<DrawObject> ptr_drawMap (new DrawObject(DrawMap));
                                        drawmaps.push_back(move(ptr_drawMap));
                                }
                        }
                }
        }
        for (size_t player = 0; player < turn.getTeams().size(); player++){
                for (int k=0; k< (int) turn.getTeams()[player]->getListCharacter().size(); k++){
                        DrawObject DrawChar;
                        std::vector<std::unique_ptr<render::DrawObject>> charframe;
                        for (size_t spriteAnimNumber = 0; spriteAnimNumber < 6; spriteAnimNumber++)
                        {
                                DrawChar.renderCharacter(turn,*tilesets[1], turn.getMap().size(),
                                                                                turn.getMap()[0].size(),
                                                                                tilesets[1]->getXsize(), tilesets[1]->getYsize(),
                                                                                tilesets[1]->getMargin(),spriteAnimNumber,k,player);
                                std::unique_ptr<DrawObject> ptr_drawChar (new DrawObject(DrawChar));
                                charframe.push_back(move(ptr_drawChar));
                        }
                        drawchars.push_back(move(charframe));
                }
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

void TurnDisplay::redraw (state::Turn& turn, sf::RenderWindow& window){
	initRender(turn);
        // cout << "====redraw" << endl;
}

void TurnDisplay::display (sf::RenderWindow& window, int frame){
	window.clear();
	size_t j=0;
        vector< vector<int> >  indexlist=charPrintOrder();
        for (size_t i = 0; i < drawmaps.size(); i++){
                window.draw(*drawmaps[i]);
                if((i+1)%6==0 && j<drawchars.size()){
                        int order=0;
                        for (int k = 0; k < indexlist[j][1]; k++)
                        {
                                order+=turnDisplay.getTeams()[k]->getListCharacter().size();
                                
                        }
                        order+=indexlist[j][0];
                        // cout << "order:" << order << endl;
                        window.draw(*drawchars[order][frame]);
                        j++;
                }
        }
        // cout << drawchars.size() <<"====="<< endl;
	window.display();
}

std::vector<std::vector<int>> TurnDisplay::charPrintOrder(){

    vector<pair<Character, vector<int> >> vp;

    for (size_t i = 0; i < turnDisplay.getTeams().size(); i++)
    {
        for (size_t j = 0; j < turnDisplay.getTeams()[i]->getListCharacter().size(); j++)
        {
                vector<int> indexes;
                indexes.push_back(j);
                indexes.push_back(i);
                vp.push_back(make_pair(*turnDisplay.getTeams()[i]->getListCharacter()[j], indexes));
        }

    }
        std::sort(vp.begin(),  vp.end(), [&]( pair<Character, vector<int>>  a, pair<Character, vector<int>>  b) -> bool
        {
                int aPosX=a.first.getPosition().getX(),bPosX=b.first.getPosition().getX();
                int aPosY=a.first.getPosition().getY(),bPosY=b.first.getPosition().getY();
                int atemp=0,btemp=0;
                for (int q=0; q<turnDisplay.rotation; q++){
                        atemp=aPosX,btemp=bPosX;
                        aPosX=turnDisplay.getMap().size()-aPosY-1,bPosX=turnDisplay.getMap().size()-bPosY-1;
                        aPosY=atemp,bPosY=btemp;
                }
                //    cout << "a get X" << a.first.getPosition().getX() << "|" << "b get X" << b.first.getPosition().getX() << endl;
                if(aPosX == bPosX){
                        return aPosY < bPosY;
                }
                return aPosX < bPosX;
        });

    vector< vector<int> > indexlist;
    for (size_t i = 0; i < vp.size(); i++) {
        vector<int> indexes(2,0);
        indexes[0]= vp[i].second[0],indexes[1]= vp[i].second[1];
        // cout << vp[i].second[0] << "|" << vp[i].second[1] << endl;
        indexlist.push_back(indexes);
    }

    return indexlist;
}
