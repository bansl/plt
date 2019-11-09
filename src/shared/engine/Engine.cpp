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

	if(isGameFinished){
		cout << "GAME OVER" << endl;
	}

	if(isTurnFinished){
		turn.nextTurn();
		cout << "TURN END" << endl << endl;
	}
	return isTurnFinished;
}

void Engine::updateDisplay (sf::RenderWindow& window){

	isTurnFinished=true;
	isGameFinished=true;
	StatusList status;
	for (size_t i = 0; i < turn.getTeams()[currentPlayerId]->getListCharacter().size(); i++)
	{
		status=turn.getTeams()[currentPlayerId]->getListCharacter()[i]->getStatus();
		if(turn.getTeams()[currentPlayerId]->getListCharacter()[i]->getCurrentHP()<=0){
			turn.getTeams()[currentPlayerId]->getListCharacter()[i]->setStatus(Dead);
		}
		if (status== Available){
			isTurnFinished=false;
		}
		if (status != Dead){
			isGameFinished=false;
		}

	}

	if(isTurnFinished){
		for(size_t i=0; i<commands.size();i++){
			commands[i]->action(turn);
			
			turn.notifyObservers(turn, window);
			commands[i]->finish(turn);
			turn.notifyObservers(turn, window);
		}
	while (!commands.empty()){
			commands.pop_back();
		}
	}
}

bool Engine::turnCheckIn(){
	if (isTurnFinished) {
		currentPlayerId= (currentPlayerId+1) % turn.getTeams().size();

		for (size_t i = 0; i < turn.getTeams()[currentPlayerId]->getListCharacter().size(); i++){
			turn.getTeams()[currentPlayerId]->getListCharacter()[i]->setStatus(Available);
		}
		cout << "NEW TURN " << endl;
		cout << "====TURN " << turn.getTurn() << ": ====" << endl;
		isTurnFinished=false;
		return true;
	}
	return false;
}

Engine::Engine(state::Turn& turn):turn(turn){
	isGameFinished=false;
	isTurnFinished=false;
	currentPlayerId=0;
}
