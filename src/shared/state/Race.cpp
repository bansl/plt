#include "../state.h"

using namespace state;
using namespace std;

void Race::setRace(state::RaceType race){
  this->race=race;
}

state::RaceType Race::getRace(){
  return race;
}
