#include "../state.h"
#include <random>
#include <iostream>
using namespace std;
using namespace state;


state::Tile TileFactory::getRandomTile (){
  random_device dev;
  mt19937 rng(dev());
  uniform_int_distribution<std::mt19937::result_type> distribution(1,6);
  int i=distribution(rng);
  mt19937 rng2(dev());
  uniform_int_distribution<std::mt19937::result_type> distributionHeight(1,3);
  int randomHeight=distributionHeight(rng2);
  Tile randomtile {};
  if (i==1) {
    randomtile.tile=Dirt;
    randomtile.setHeight(randomHeight);
    return randomtile;
  }
  else if (i==2) {
    randomtile.tile=Grass;
    randomtile.setHeight(randomHeight);
    return randomtile;
  }
  else if (i==3) {
    randomtile.tile=Water;
    randomtile.setHeight(randomHeight);
    return randomtile;
  }
  else if (i==4) {
    randomtile.tile=Sand;
    randomtile.setHeight(randomHeight);
    return randomtile;
  }
  else if (i==5) {
    randomtile.tile=Pound;
    randomtile.setHeight(randomHeight);
    return randomtile;
  }
  else if (i==6) {
    randomtile.tile=Rock;
    randomtile.setHeight(randomHeight);
    return randomtile;
  }
  exit(EXIT_FAILURE);
}