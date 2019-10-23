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

void Turn::rotateMap(int N){
  for (int x = 0; x < N / 2; x++)
    {   // Consider elements in group of 4 in current square
        for (int y = x; y < N-x-1; y++)
        {   // store current cell in temp variable
            state::Tile temp = this->map[x][y];
            // move values from right to top
            this->map[x][y] = this->map[y][N-1-x];
            // move values from bottom to right
            this->map[y][N-1-x] = this->map[N-1-x][N-1-y];
            // move values from left to bottom
            this->map[N-1-x][N-1-y] = this->map[N-1-y][x];
            // assign temp to left
            this->map[N-1-y][x] = temp;
        }
    }
}
