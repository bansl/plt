#include "../engine.h"
#include "../state.h"

using namespace engine;
using namespace state;

Stats::Stats(state::Character& charac, state::Character& targetchar):character(charac),targetCharacter(targetchar){

}

Stats::Stats(state::Character& charac):character(charac),targetCharacter(charac){
 targetCharacter={};
}


Stats::Stats():character(character),targetCharacter(targetCharacter){
 character={};
 targetCharacter={};
}