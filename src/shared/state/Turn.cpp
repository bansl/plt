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

void Turn::revertTurn (){
    turnNumber-=1;
}

int Turn::getTurn (){
    return turnNumber;
}

bool Turn::initCursor (){
    ptrCursor=new Cursor();
    Position nextPosCurs;
    nextPosCurs.setPos(map.size()/2,map.size()/2);
    ptrCursor->cursorMove(nextPosCurs);
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

void Turn::skipTurn(){
  isTurnSkipped=!isTurnSkipped;
}

bool Turn::getIsSkipped(){
  return isTurnSkipped;
}

std::vector<std::unique_ptr<state::Position>>& Turn::getBuffer(){
  std::vector<std::unique_ptr<state::Position>> & addrBuff=bufferPosition;
  return addrBuff;
}

void Turn::initBuffer(){
  while (!bufferPosition.empty()){
          bufferPosition.pop_back();
  }
}

void Turn::addToBuffer(std::unique_ptr<state::Position> pos){
  bufferPosition.push_back(move(pos));
}

std::string Turn::seedMap(){
  std::string seed;
  std::vector<std::string> tileLabel (6);
  tileLabel[0]="d",tileLabel[1]="g",tileLabel[2]="w",tileLabel[3]="s",tileLabel[4]="p",tileLabel[5]="r";
  std::vector<std::string> tileHeight (3);
  tileHeight[0]="1",tileHeight[1]="2",tileHeight[2]="3";
  for(int i=0;i<(int)getMap().size();i++){
    for(int j=0;j<(int)getMap().size();j++){
      seed.append(tileLabel[getMap()[i][j].getTile()-1]);
      seed.append(tileHeight[getMap()[i][j].getHeight()-1]);
    }
  }
  return seed;
}

std::string Turn::seedTeams(){
  std::string seed;
  seed.append(std::to_string(getTeams().size()));
  std::vector<std::string> raceLabel (4);
  raceLabel[0]="m",raceLabel[1]="b",raceLabel[2]="d",raceLabel[3]="h";
  std::vector<std::string> jobLabel (4);
  jobLabel[0]="p",jobLabel[1]="s",jobLabel[2]="a",jobLabel[3]="m";
  for(int i=0;i<(int)getTeams().size();i++){
    for(int j=0;j<(int)getTeams()[0]->getListCharacter().size();j++){
      seed.append(raceLabel[teams[i]->getListCharacter()[j]->getRace().getRace()-1]);
      seed.append(jobLabel[teams[i]->getListCharacter()[j]->getJob().getJob()-1]);
    }
  }
  return seed;
}

void Turn::initTeams(std::string seed, int mapSize){
  vector<vector< int >> basepos  { {1,mapSize/2-1},{1,mapSize/2},{1,mapSize/2+1},
                                   {2,mapSize/2-1},{2,mapSize/2},{2,mapSize/2+1} };
  int nbTeams=std::stoi(seed.substr(0,1));
  int nbChar=(seed.length()-1)/(2*nbTeams);
  for(int i=0;i<nbTeams;i++){
    initTeams();
    for(int j=0;j<nbChar;j++){
      teams[i]->addCharacter();

      char race=seed.at(1+j*2+i*nbChar);
      if( race== (char) 'd'){
        teams[i]->getListCharacter()[j]->getRace().setRace(Demon);
      }
      else if(race== (char) 'b'){
        teams[i]->getListCharacter()[j]->getRace().setRace(Beastman);
      }
      else if(race== (char) 'h'){
        teams[i]->getListCharacter()[j]->getRace().setRace(Human);
      }
      else if(race== (char) 'm'){
        teams[i]->getListCharacter()[j]->getRace().setRace(Monster);
      }

      char job=seed.at(2+j*2+i*nbChar);
      if( job== (char) 'p'){
        teams[i]->getListCharacter()[j]->getJob().setJob(Pugilist);
      }
      else if(job== (char) 's'){
        teams[i]->getListCharacter()[j]->getJob().setJob(Swordman);
      }
      else if(job== (char) 'a'){
        teams[i]->getListCharacter()[j]->getJob().setJob(Archer);
      }
      else if(job== (char) 'm'){
        teams[i]->getListCharacter()[j]->getJob().setJob(Magician);
      }
      int tempPosX=basepos[j][0],tempPosY=basepos[j][1];
      int temp=0;
      for (int q=0; q<2*i; q++){
          temp=tempPosX;
          tempPosX=map.size()-tempPosY-1;
          tempPosY=temp;
      }
      teams[i]->getListCharacter()[j]->getPosition().setPos(tempPosX,tempPosY);
    }
  }

}

void Turn::initTurn(int mapSize, std::string charSeed){
  while(!teams.empty())teams.pop_back();

  while(!map.empty())map.pop_back();
  
  initTeams(charSeed,mapSize);
  initTurn(mapSize,0,0);
}

void Turn::initTurn(int mapSize, std::string charSeed, std::string mapSeed){
  initTeams(charSeed,mapSize);
  initTurn(mapSize,0,0,mapSeed);
}

void Turn::initTurn(int mapSize, int teamNb, int characterNb){

  initMap(mapSize,mapSize);
  initTurn(mapSize,teamNb,characterNb,seedMap());
}

void Turn::initTurn (int mapSize, int teamNb, int characterNb, std::string mapSeed){

  vector<vector< int >> basepos  { {1,mapSize/2-1},{1,mapSize/2},{1,mapSize/2+1},
                                   {2,mapSize/2-1},{2,mapSize/2},{2,mapSize/2+1} };

  initMap(mapSize,mapSize,mapSeed);
  for (int i = 0; i < teamNb; i++)
  {
    initTeams();
    for (int j = 0; j < characterNb; j++)
    {
      teams[i]->addCharacter();
    }
  }
  for (int i = 0; i <(int) getTeams().size(); i++)
  {
    for (int j = 0; j <(int) teams[i]->getListCharacter().size(); j++)
    {
      int tempPosX=basepos[j][0],tempPosY=basepos[j][1];
      int temp=0;
      for (int q=0; q<2*i; q++){
          temp=tempPosX;
          tempPosX=map.size()-tempPosY-1;
          tempPosY=temp;
      }
      teams[i]->getListCharacter()[j]->getPosition().setPos(tempPosX,tempPosY);
    }
  }
  initCursor();
  initBuffer();
}
