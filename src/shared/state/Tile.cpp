#include "../state.h"

using namespace state; 
using namespace std;

int Tile::getHeight (){
    return height;
}
void Tile::setHeight (int height){
    this->height=height;
}
state::TileType Tile::getTile (){
    return tile;
}