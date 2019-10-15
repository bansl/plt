#include "../state.h"
#include <cstdlib>
using namespace std;
using namespace state;

Job RandomJobFactory::getJob (){
  int i=std::rand()%3+1;
  i=1;//For test purpose
  Job randomjob {};
  if (i==1) {
    randomjob.job=Pugilist;
    return randomjob;
  }
  else if (i==2) {
    randomjob.job=Swordman;
    return randomjob;
  }
  else if (i==3) {
    randomjob.job=Archer;
    return randomjob;
  }
  else if (i==4) {
    randomjob.job=Magician;
    return randomjob;
  }
  exit(EXIT_FAILURE);
}
