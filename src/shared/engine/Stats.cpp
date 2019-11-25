#include "../engine.h"
#include "../state.h"

using namespace engine;
using namespace state;

Stats::Stats(state::Character& charac, state::Character& targetchar,int numb):character(charac),targetCharacter(targetchar),number(numb){
  destination={};
}

Stats::Stats(state::Character& charac, state::Character& targetchar):character(charac),targetCharacter(targetchar){
  number=-1;
  destination={};
}

Stats::Stats(state::Character& charac,state::Position dest):character(charac),targetCharacter(targetCharacter),destination(dest){
  number=-1;
  targetCharacter={};
}

Stats::Stats(state::Character& charac):character(charac),targetCharacter(targetCharacter){
 number=-1;
 destination={};
 targetCharacter={};
}

Stats::Stats():character(character),targetCharacter(targetCharacter){
  character={};
  targetCharacter={};
  number=-1;
  destination={};
}

state::Character& Stats::getCharacter(){
  Character & addrCharacter = character;
  return addrCharacter;
}

state::Character& Stats::getTargetCharacter(){
  Character & addrCharacter = targetCharacter;
  return addrCharacter;
}

int Stats::getNumber(){
  return number;
}

state::Position Stats::getDest(){
  return destination;
}
