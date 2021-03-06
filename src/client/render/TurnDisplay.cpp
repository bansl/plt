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

        TileSet theCursor(CursorSprite);
      	std::unique_ptr<TileSet> ptr_theCursor (new TileSet(theCursor));
      	tilesets.push_back(move(ptr_theCursor));

        TileSet tilesetWindow(WindowSprite);
      	std::unique_ptr<TileSet> ptr_window (new TileSet(tilesetWindow));
      	tilesets.push_back(move(ptr_window));

        TileSet actionCursor(HandCursorSprite);
        std::unique_ptr<TileSet> ptr_actionCursor (new TileSet(actionCursor));
        tilesets.push_back(move(ptr_actionCursor));
}

void TurnDisplay::initRender(){
        while (!drawchars.empty()){
                drawchars.pop_back();
        }
        while (!drawmaps.empty()){
                drawmaps.pop_back();
        }
        while (!drawcursor.empty()){
                drawcursor.pop_back();
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
                        coord.push_back(move(turnDisplay.getTeams()[i]->getListCharacter()[k]->getPosition().getX()));
                        coord.push_back(move(turnDisplay.getTeams()[i]->getListCharacter()[k]->getPosition().getY()));
                        int temp=0;
                        for (int q=0; q<turnDisplay.rotation; q++){
                                temp=coord[0];
                                coord[0]=turnDisplay.getMap().size()-coord[1]-1;
                                coord[1]=temp;
                        }
                        map_segmentation.push_back(move(coord));
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

                                DrawChar.renderCharacter(turnDisplay,*tilesets[1], turnDisplay.getMap().size(),
                                                                                turnDisplay.getMap()[0].size(),
                                                                                tilesets[1]->getXsize(), tilesets[1]->getYsize(),
                                                                                tilesets[1]->getMargin(),0,k,player);
                                std::unique_ptr<DrawObject> ptr_drawChar (new DrawObject(DrawChar));
                                charframe.push_back(move(ptr_drawChar));
                        for (size_t spriteAnimNumber = 1; spriteAnimNumber < 4; spriteAnimNumber++)
                        {
                                DrawChar.changeCharAnimSpriteNb (spriteAnimNumber, tilesets[1]->getXsize(), tilesets[1]->getYsize(), tilesets[1]->getMargin(), turnDisplay, player, k);
                                std::unique_ptr<DrawObject> ptr_drawChar (new DrawObject(DrawChar));
                                charframe.push_back(move(ptr_drawChar));
                        }
                        drawchars.push_back(move(charframe));
                }
        }
        DrawObject DrawCursor;
        if(DrawCursor.renderCursor(turnDisplay, *tilesets[2],
                                        {(int)turnDisplay.getMap().size(), (int) turnDisplay.getMap()[0].size()},
                                        {tilesets[0]->getXsize(), tilesets[0]->getYsize()})){
                std::unique_ptr<DrawObject> ptr_drawCursor (new DrawObject(DrawCursor));
                drawcursor.push_back(move(ptr_drawCursor));
        }
}

void TurnDisplay::initRender(state::Turn& turn, state::RenderType rendertype){


        if(rendertype==fullRender){

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
                          coord.push_back(move(turn.getTeams()[i]->getListCharacter()[k]->getPosition().getX()));
                          coord.push_back(move(turn.getTeams()[i]->getListCharacter()[k]->getPosition().getY()));
                          int temp=0;
                          for (int q=0; q<turn.rotation; q++){
                                  temp=coord[0];
                                  coord[0]=turn.getMap().size()-coord[1]-1;
                                  coord[1]=temp;
                          }
                          map_segmentation.push_back(move(coord));
                  }
          }
          vector<int> lastcoord;
          lastcoord.push_back(move(turn.getMap().size()));
          lastcoord.push_back(move(turn.getMap()[0].size()));
          map_segmentation.push_back(move(lastcoord));

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
        }

        if((rendertype==fullRender) || rendertype==cursorRender){
                while (!drawcursor.empty()){
                        drawcursor.pop_back();
                }
                DrawObject DrawCursor;
                if(DrawCursor.renderCursor(turn, *tilesets[2],
                                           {(int)turn.getMap().size(), (int) turn.getMap()[0].size()},
                                           {tilesets[0]->getXsize(), tilesets[0]->getYsize()})){
                        std::unique_ptr<DrawObject> ptr_drawCursor (new DrawObject(DrawCursor));
                        drawcursor.push_back(move(ptr_drawCursor));
                }

        }

        if((rendertype==fullRender) || (rendertype==charRender)){
                while (!drawchars.empty()){
                        drawchars.pop_back();
                }
                for (size_t player = 0; player < turn.getTeams().size(); player++){
                        for (int k=0; k< (int) turn.getTeams()[player]->getListCharacter().size(); k++){
                                DrawObject DrawChar;
                                std::vector<std::unique_ptr<render::DrawObject>> charframe;

                                        DrawChar.renderCharacter(turn,*tilesets[1], turn.getMap().size(),
                                                                                        turn.getMap()[0].size(),
                                                                                        tilesets[1]->getXsize(), tilesets[1]->getYsize(),
                                                                                        tilesets[1]->getMargin(),0,k,player);
                                        std::unique_ptr<DrawObject> ptr_drawChar (new DrawObject(DrawChar));
                                        charframe.push_back(move(ptr_drawChar));
                                for (size_t spriteAnimNumber = 1; spriteAnimNumber < 4; spriteAnimNumber++)
                                {
                                        DrawChar.changeCharAnimSpriteNb (spriteAnimNumber, tilesets[1]->getXsize(), tilesets[1]->getYsize(), tilesets[1]->getMargin(), turn, player, k);
                                        std::unique_ptr<DrawObject> ptr_drawChar (new DrawObject(DrawChar));
                                        charframe.push_back(move(ptr_drawChar));
                                }
                                drawchars.push_back(move(charframe));
                        }
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

void TurnDisplay::redraw (state::Turn& turn, sf::RenderWindow& window, state::RenderType rendertype,std::vector<sf::View> views){
	if (rendertype==windowinfoRender) initWindowRender(infobanner);
        else if (rendertype==windowactionRender) initWindowRender(actionselect);
        else initRender(turn,rendertype);
        sf::Time t_anim = sf::seconds(0.1f);
        for (size_t k = 0; k < 3; k++)
        {
                display(window,k,views);
                sf::sleep(t_anim);
        }
}


void TurnDisplay::display (sf::RenderWindow& window, int frame, std::vector<sf::View> views){
	window.clear();
        window.setView(views[0]);
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
        window.draw(*drawcursor[0]);
        // cout << drawchars.size() <<"====="<< endl;
        window.setView(views[2]);
        if (!drawwindows.empty()){
                window.draw(*drawwindows[0]);
                sf::Text message;
                sf::Font font;
                font.loadFromFile("res/COURG___.TTF");
                message.setFont(font);
                message.setColor(sf::Color::White);
                message.setStyle(sf::Text::Bold);
                message.setCharacterSize(15);

                message.setString(drawwindows[0]->getMessage().tiletype);
                message.setPosition(10,520);
                window.draw(message);

                message.setString(drawwindows[0]->getMessage().iscrossable);
                message.setPosition(10,540);
                window.draw(message);

                message.setString(drawwindows[0]->getMessage().isfree);
                message.setPosition(10,560);
                window.draw(message);

                message.setString(drawwindows[0]->getMessage().team);
                message.setPosition(410,520);
                window.draw(message);

                message.setString(drawwindows[0]->getMessage().characterjob);
                message.setPosition(410,540);
                window.draw(message);

                message.setString(drawwindows[0]->getMessage().characterrace);
                message.setPosition(410,560);
                window.draw(message);

                message.setString(drawwindows[0]->getMessage().hp);
                message.setPosition(610,520);
                window.draw(message);

                message.setString(drawwindows[0]->getMessage().mp);
                message.setPosition(610,540);
                window.draw(message);
        }
        window.setView(views[3]);

        for (size_t i = 1; i < drawwindows.size(); i++){
                window.draw(*drawwindows[i]);
                if(i==1){
                  sf::Text message;
                  sf::Font font;
                  font.loadFromFile("res/COURG___.TTF");
                  message.setFont(font);
                  message.setColor(sf::Color::White);
                  message.setStyle(sf::Text::Bold);
                  message.setCharacterSize(15);

                  message.setString("Attack");
                  message.setPosition(250,320);
                  window.draw(message);

                  message.setString("Move");
                  message.setPosition(250,350);
                  window.draw(message);

                  message.setString("Object");
                  message.setPosition(250,380);
                  window.draw(message);

                  message.setString("Defend");
                  message.setPosition(250,410);
                  window.draw(message);

                  message.setString("Skill");
                  message.setPosition(250,440);
                  window.draw(message);

                  message.setString("End Turn");
                  message.setPosition(250,470);
                  window.draw(message);
                }
        }
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

void TurnDisplay::initWindowRender (render::WindowType windowtype){
      if ((windowtype==actionselect)&&(drawwindows.size()>1))   while (drawwindows.size()>1) drawwindows.pop_back();
      else if(windowtype==infobanner) while (!drawwindows.empty()) drawwindows.pop_back();
      Window myWindow;
      if(myWindow.renderWindow(windowtype, *tilesets[3], tilesets[3]->getXsize(),turnDisplay)){
        std::unique_ptr<Window> ptr_drawWindow (new Window(myWindow));
        drawwindows.push_back(move(ptr_drawWindow));
      }
      if (windowtype==actionselect){
        Window myWindow2;
        if(myWindow2.renderActionCursor(selectpos,*tilesets[4])){
          std::unique_ptr<Window> ptr_drawCursorA (new Window(myWindow2));
          drawwindows.push_back(move(ptr_drawCursorA));
        }
      }


}

void TurnDisplay::moveCursorUp (){
    if (selectpos>1) selectpos--;
}

void TurnDisplay::moveCursorDown (){
    if (selectpos<6) selectpos++;
}

void TurnDisplay::engineUpdated(){}

void TurnDisplay::engineUpdating(){}