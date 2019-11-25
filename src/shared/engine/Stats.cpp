#include "../engine.h"
#include "../state.h"

using namespace engine;
using namespace state;

Stats::Stats(state::Character& charac, state::Character& targetchar,int numb):character(charac),targetCharacter(targetchar),number(numb),destination(destination){
  destination={};
}

Stats::Stats(state::Character& charac, state::Character& targetchar):character(charac),targetCharacter(targetchar),destination(destination){
  number=-1;
  destination={};
}

Stats::Stats(state::Character& charac,state::Position dest):character(charac),targetCharacter(targetCharacter),destination(dest){
  number=-1;
  targetCharacter={};
}

Stats::Stats(state::Character& charac):character(charac),targetCharacter(targetCharacter),destination(destination){
 number=-1;
 destination={};
 targetCharacter={};
}

Stats::Stats():character(character),targetCharacter(targetCharacter),destination(destination){
  character={};
  targetCharacter={};
  number=-1;
  destination={};
}

state::Character& Stats::getCharacter(){
  // Character & addrCharacter = character;
  // return addrCharacter;
  return character;
}

state::Character& Stats::getTargetCharacter(){
  // Character & addrCharacter = targetCharacter;
  // return addrCharacter;
  return targetCharacter;
}

int Stats::getNumber(){
  return number;
}

state::Position& Stats::getDest(){
  // Position & addrPosition=destination;
  // return addrPosition;
  return destination;
}
