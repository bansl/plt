#include "../state.h"
#include <random>
#include <iostream>
using namespace std;
using namespace state;

state::RaceType RandomRaceFactory::getRandomRace(){
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> distribution(1,4);
  int i=distribution(rng);
  if (i==1) {
    return Monster;
  }
  else if (i==2) {
    return Beastman;
  }
  else if (i==3) {
    return Demon;
  }
  else if (i==4) {
    return Human;
  }
  exit(EXIT_FAILURE);
}
