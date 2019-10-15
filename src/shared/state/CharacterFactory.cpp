#include "../state.h"

using namespace std;
using namespace state;

state::Character CharacterFactory::createCharacter(){
  Character newCharacter {};
  RandomJobFactory rjf {};
  RandomRaceFactory rrf {};
  Race newRace {};
  Job newJob {};
  newRace.setRace(rrf.getRandomRace());
  newJob.setJob(rjf.getRandomJob());
  newCharacter.setJob(newJob);
  newCharacter.setRace(newRace);
  return newCharacter;
}
