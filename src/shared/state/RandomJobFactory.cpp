#include "../state.h"
#include <random>
#include <iostream>
using namespace std;
using namespace state;

state::JobType RandomJobFactory::getRandomJob(){
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> distribution(1,4);
  int i=distribution(rng);
  if (i==1) {
    return Pugilist;
  }
  else if (i==2) {
    return Swordman;
  }
  else if (i==3) {
    return Archer;
  }
  else if (i==4) {
    return Magician;
  }
  exit(EXIT_FAILURE);
}
