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
bool Engine::turnCheckOut(sf::RenderWindow& window, int rotation){
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

		for(size_t i=0; i<commands.size();i++){
			commands[i]->action(turn);
			cout << "action #" << i <<" done" <<endl;
			turn.notifyObservers(turn, rotation, window);
			// sf::Time t1 = sf::seconds(1.0f);
			// sf::sleep(t1);
		}
		while (!commands.empty()){
			commands.pop_back();
		}
	}

	if(isGameFinished){
		cout << "GAME OVER" << endl;
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

Engine::Engine(state::Turn& turn):turn(turn){
	isGameFinished=false;
	isTurnFinished=false;
	currentPlayerId=0;
}