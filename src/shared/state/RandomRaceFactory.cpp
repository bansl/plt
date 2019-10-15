#include "../state.h"
#include <cstdlib>
using namespace std;
using namespace state;

Race RandomRaceFactory::getRace (){
  int i=std::rand()%3+1;
  i=1;//For test purpose
  Race randomrace {};
  if (i==1) {
    randomrace.race=Monster;
    return randomrace;
  }
  else if (i==2) {
    randomrace.race=Beastman;
    return randomrace;
  }
  else if (i==3) {
    randomrace.race=Demon;
    return randomrace;
  }
  else if (i==4) {
    randomrace.race=Human;
    return randomrace;
  }
  exit(EXIT_FAILURE);
}
