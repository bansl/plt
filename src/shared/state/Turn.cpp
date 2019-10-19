#include "../state.h"

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

std::vector<state::Team> Turn::getTeams (){
    return teams;
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
