#include "../state.h"

using namespace std;
using namespace state;

state::Character CharacterFactory::createCharacter(){
  Character newCharacter {};
  RandomJobFactory rjf {};
  RandomRaceFactory rrf {};
  newCharacter.getJob().setJob(rjf.getRandomJob());
  newCharacter.getRace().setRace(rrf.getRandomRace());
  newCharacter.setStatus(Available);
  return newCharacter;
}
