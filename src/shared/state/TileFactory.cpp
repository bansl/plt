#include "../state.h"
#include <cstdlib>
using namespace std;
using namespace state;


state::Tile getRandomTile (){
  int i=rand()%6+1;
  Tile randomtile {};
  if (i==1) {
    randomtile.tile=Dirt;
    randomtile.height=1;
    return randomtile;
  }
  else if (i==2) {
    randomtile.tile=Grass;
    randomtile.height=1;
    return randomtile;
  }
  else if (i==3) {
    randomtile.tile=Water;
    randomtile.height=1;
    return randomtile;
  }
  else if (i==4) {
    randomtile.tile=Sand;
    randomtile.height=1;
    return randomtile;
  }
  else if (i==5) {
    randomtile.tile=Pound;
    randomtile.height=1;
    return randomtile;
  }
  else if (i==6) {
    randomtile.tile=Rock;
    randomtile.height=1;
    return randomtile;
  }
  exit(EXIT_FAILURE);
}