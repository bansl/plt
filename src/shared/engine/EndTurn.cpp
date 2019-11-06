#include "../engine.h"

using namespace engine;
using namespace state;


bool EndTurn::action(state::Turn& turn){

  for (size_t i = 0; i < turn.getTeams()[currentPlayerId]->getListCharacter().size(); i++)
  {
    if (turn.getTeams()[currentPlayerId]->getListCharacter()[i]->getStatus() == Available){
        turn.getTeams()[currentPlayerId]->getListCharacter()[i]->setStatus(Used);
    }
  }
  
  return true;
}

bool EndTurn::validate(state::Turn& turn){
  return true;
}

EndTurn::EndTurn (int playerId):currentPlayerId(playerId){
    commandType= EndTurncmd;
}