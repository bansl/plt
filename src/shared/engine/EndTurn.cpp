#include "../engine.h"

using namespace engine;
using namespace state;


bool EndTurn::action(state::Turn& turn){
  return true;
}

bool EndTurn::validate(state::Turn& turn){
  return true;
}

EndTurn::EndTurn (state::Character& character):character(character){
    commandType= EndTurncmd;
}