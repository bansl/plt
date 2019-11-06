#include "../state.h"
#include <sstream>
#include <iostream>
#include <cstring>
#include <stdio.h>

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

std::vector<std::unique_ptr<Team>>& Turn::getTeams (){
  std::vector<std::unique_ptr<Team>>& myteams = teams;
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
    std::unique_ptr<state::Team> ptr_team (new Team);
    teams.push_back(move( ptr_team));
}

void Turn::initMap (int row, int column,std::string seed){

    vector< vector<state::Tile> > generatedmap;
    int position=row*column*8-1;
    for (int i = 0; i < column; i++) {
        vector<state::Tile> generatedmaprow;
        for (int j = 0; j < row; j++) {
          char * type;
          *type=seed.at(i*2+row*j*2);
          int height=(int)seed.at(i*2+row*j*2+1);
          //char type=seed.at(i*2+row*j*2);
          Tile newTile;
          newTile.setHeight(height);
          if(strcmp(type,"d")==0){
            newTile.tile=Dirt;
          }
          else if(strcmp(type,"g")==0){
            newTile.tile=Grass;
          }
          else if(strcmp(type,"w")==0){
            newTile.tile=Water;
          }
          else if(strcmp(type,"s")==0){
            newTile.tile=Sand;
          }
          else if(strcmp(type,"p")==0){
            newTile.tile=Pound;
          }
          else if(strcmp(type,"r")==0){
            newTile.tile=Rock;
          }
          generatedmaprow.push_back(newTile);
          position+=-8;
        }
        generatedmap.push_back(generatedmaprow);
    }
    this->map=generatedmap;
}
