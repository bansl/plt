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

void Turn::initMap (){
    TileFactory tf {};
    vector< vector<state::Tile> > generatedmap;

    for (int i = 0; i < 50; i++) {
        vector<state::Tile> generatedmaprow; 
        for (int j = 0; j < 50; j++) {
            generatedmaprow.push_back(tf.getRandomTile());
        }
        generatedmap.push_back(generatedmaprow);
    }
    this->map=generatedmap;
}