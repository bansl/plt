#include "../state.h"
#include <random>
#include <iostream>
using namespace std;
using namespace state;


state::Tile TileFactory::getRandomTile (){
  random_device dev;
  mt19937 rng(dev());
  uniform_int_distribution<std::mt19937::result_type> distribution(1,65);
  int i=distribution(rng);
  mt19937 rng2(dev());
  uniform_int_distribution<std::mt19937::result_type> distributionHeight(1,20);
  
  int randomHeight;
  if (distributionHeight(rng2)<10)
  {
    randomHeight=1;
  }
  else if (distributionHeight(rng2)<16)
  {
    randomHeight=2; //2
  }
  else{
    randomHeight=3;//3
  }
  
  Tile randomtile{};
  if (i<10) {
    randomtile.tile=Dirt;
    randomtile.setHeight(randomHeight);
    return randomtile;
  }
  else if (i<30) {
    randomtile.tile=Grass;
    randomtile.setHeight(randomHeight);
    return randomtile;
  }
  else if (i<35) {
    randomtile.tile=Water;
    randomtile.setHeight(1);
    return randomtile;
  }
  else if (i<45) {
    randomtile.tile=Sand;
    randomtile.setHeight(randomHeight);
    return randomtile;
  }
  else if (i<50) {
    randomtile.tile=Pound;
    randomtile.setHeight(randomHeight);
    return randomtile;
  }
  else if (i<=65) {
    randomtile.tile=Rock;
    randomtile.setHeight(randomHeight);
    return randomtile;
  }
  exit(EXIT_FAILURE);
}