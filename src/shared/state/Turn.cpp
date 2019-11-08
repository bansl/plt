#include "../state.h"
#include <sstream>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include<string>


using namespace state;
using namespace std;


void Turn::nextTurn (){
    turnNumber+=1;
}

int Turn::getTurn (){
    return turnNumber;
}

bool Turn::initCursor (){
    ptrCursor=new Cursor();
    return true;
}

state::Cursor* Turn::getCursor (){
    return ptrCursor;
}

std::vector<std::shared_ptr<Team>>& Turn::getTeams (){
  std::vector<std::shared_ptr<Team>>& myteams = teams;
  return myteams;
}

void Turn::initMap (int row, int column){
    TileFactory tf {};
    vector< vector<state::Tile> > generatedmap;

    for (int i = 0; i < column/2; i++) {
        vector<state::Tile> generatedmaprow;
        for (int j = 0; j < row; j++) {
            generatedmaprow.push_back(tf.getRandomTile());
        }
        generatedmap.push_back(generatedmaprow);
    }
    if(column%2!=0){
        vector<state::Tile> generatedmaprow2;
        for (int j = 0; j < row; j++) {
            generatedmaprow2.push_back(tf.getRandomTile());
        }
        generatedmap.push_back(generatedmaprow2);
    }
    for (int i = 0; i < column/2; i++) {
        generatedmap.push_back(generatedmap[column/2-i-1]);
    }
    this->map=generatedmap;
}

std::vector<std::vector<state::Tile>> Turn::getMap (){
    return map;
}

void Turn::initTeams (){
    std::shared_ptr<state::Team> ptr_team (new Team);
    teams.push_back(ptr_team);
}

void Turn::initMap (int row, int column,std::string seed){

    vector< vector<state::Tile> > generatedmap;

    for (int i = 0; i < column; i++) {
        vector<state::Tile> generatedmaprow;
        for (int j = 0; j < row; j++) {
          if((int) seed.size()<=j*2+row*i*2) break;

          int height=(int) (seed.at(j*2+row*i*2+1)) -48;

          char type=seed.at(j*2+row*i*2);
          Tile newTile;
          newTile.setHeight(height);
          if( type== (char) 'd'){
            newTile.tile=Dirt;
          }
          else if(type== (char) 'g'){
            newTile.tile=Grass;
          }
          else if(type== (char) 'w'){
            newTile.tile=Water;
          }
          else if(type== (char) 's'){
            newTile.tile=Sand;
          }
          else if(type== (char) 'p'){
            newTile.tile=Pound;
          }
          else if(type== (char) 'r'){
            newTile.tile=Rock;
          }
          generatedmaprow.push_back(newTile);


        }
        generatedmap.push_back(generatedmaprow);
    }
    this->map=generatedmap;
}

int Turn::getCharacterHeight(int numberTeam, int numberCharacter){
  return map[getTeams()[numberTeam]->getListCharacter()[numberCharacter]->getPosition().getX()][getTeams()[numberTeam]->getListCharacter()[numberCharacter]->getPosition().getY()].getHeight();
}
