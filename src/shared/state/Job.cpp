#include "../state.h"

using namespace state;
using namespace std;

void Job::setJob(state::JobType job){
  this->job=job;
}

state::JobType Job::getJob(){
  return job;
}
