#include "../state.h"

using namespace state; 
using namespace std;

std::string Entity::getName(){
    return name;
}
state::Position Entity::getPosition (){
    return position;
}

state::Tile Entity::getTile (){
    return tile;
}
