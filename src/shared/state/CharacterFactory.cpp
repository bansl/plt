#include "../state.h"
#include <random>

using namespace std;
using namespace state;

state::Character CharacterFactory::createCharacter(){
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> distribution(1,1000000);
  Character newCharacter {};
  RandomJobFactory rjf {};
  RandomRaceFactory rrf {};
  newCharacter.getJob().setJob(rjf.getRandomJob());
  newCharacter.getRace().setRace(rrf.getRandomRace());
  newCharacter.initializeSkill();
  newCharacter.setStatus(Available);
  newCharacter.setFacing(Down);
  newCharacter.initHPMP();
  newCharacter.idCharacter=distribution(rng);;
  return newCharacter;
}
