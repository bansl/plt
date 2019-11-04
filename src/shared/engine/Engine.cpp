#include <engine.h>
#include <render.h>
#include <state.h>

#include <iostream>

using namespace state;
using namespace engine;
using namespace render;
using namespace std;


state::Turn& Engine::getTurn (){
	state::Turn& myturn=turn;
	return myturn;
}

void Engine::addCommand (std::unique_ptr<Command> ptr_command){
	commands.push_back(move(ptr_command));
	
}
bool Engine::turnCheckOut(){
	isTurnFinished=true;
	isGameFinished=true;
	for (size_t i = 0; i < turn.getTeams()[currentPlayerId]->getListCharacter().size(); i++)
	{
		if (turn.getTeams()[currentPlayerId]->getListCharacter()[i]->getStatus() == Available){
			isTurnFinished=false;	
		}
		if (turn.getTeams()[currentPlayerId]->getListCharacter()[i]->getStatus() != Dead){
			isGameFinished=false;	
		} 
	}

	if(isGameFinished){
		cout << "GAME OVER\n" << endl;
	}
	return isTurnFinished;
}	

bool Engine::turnCheckIn(){
	if (isTurnFinished) {
		currentPlayerId= (currentPlayerId+1) % turn.getTeams().size();

		for (size_t i = 0; i < turn.getTeams()[currentPlayerId]->getListCharacter().size(); i++){
			turn.getTeams()[currentPlayerId]->getListCharacter()[i]->setStatus(Available);
		}

		isTurnFinished=false;
		return true;
	}
	return false;
}