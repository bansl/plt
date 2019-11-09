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

void Engine::addCommand (std::shared_ptr<Command> ptr_command){
	commands.push_back(ptr_command);

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
	for (size_t i = 0; i < turn.getTeams()[currentPlayerId]->getListCharacter().size(); i++)
	{
		if(turn.getTeams()[currentPlayerId]->getListCharacter()[i]->getCurrentHP()<=0){
			turn.getTeams()[currentPlayerId]->getListCharacter()[i]->setStatus(Dead);
		}
		if (turn.getTeams()[currentPlayerId]->getListCharacter()[i]->getStatus() == Available){
			isTurnFinished=false;
		}
		if (turn.getTeams()[currentPlayerId]->getListCharacter()[i]->getStatus() != Dead){
			isGameFinished=false;
		}
	}

	if(isTurnFinished){
		for(size_t i=0; i<commands.size();i++){
			commands[i]->action(turn);
			sf::Time t1 = sf::seconds(0.01f);
			sf::sleep(t1);
			turn.notifyObservers(turn, window);
			sf::sleep(t1);
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
