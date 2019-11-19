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
	}
	return isTurnFinished;
}

void Engine::updateDisplay (sf::RenderWindow& window){
	isGameFinished=true;
	bool updateisTurnFinished=true;
	StatusList status;
	for (size_t i = 0; i < turn.getTeams()[currentPlayerId]->getListCharacter().size(); i++)
	{
		status=turn.getTeams()[currentPlayerId]->getListCharacter()[i]->getStatus();
		if(turn.getTeams()[currentPlayerId]->getListCharacter()[i]->getCurrentHP()<=0){
			turn.getTeams()[currentPlayerId]->getListCharacter()[i]->setStatus(Dead);
		}
		if (status== Available){
			updateisTurnFinished=false;
		}
		if (status != Dead){
			isGameFinished=false;
		}

	}

	if(turn.getIsSkipped()){
		updateisTurnFinished=true;
		turn.skipTurn();
	}
	if(isTurnBegin){
		turn.notifyObservers(turn, window,charRender);
		cout << "====TURN " << turn.getTurn() << ": ====" << endl;
		isTurnBegin=false;
	}
	if(updateisTurnFinished){
		
		for(size_t i=0; i<commands.size();i++){

			commands[i]->action(turn);
			if (commands[i]->commandType==Movecmd){
				
				// engine::Move *pM=dynamic_cast<engine::Move*>(commands[i].get());
				// for(size_t j=0;j<pM->getPathToDest().size();j++){
				// 	pM->getCharacter().getPosition().setPos(pM->getPathToDest()[j].getX(),pM->getPathToDest()[j].getY());
				// 	turn.notifyObservers(turn, window,fullRender);
			 	// }
				// commands[i]->action(turn);
				turn.notifyObservers(turn, window,fullRender);
			}
			else if (commands[i]->commandType!=EndTurncmd) turn.notifyObservers(turn, window,charRender);
			commands[i]->finish(turn);
			turn.notifyObservers(turn, window,charRender);
		}
	while (!commands.empty()){
			commands.pop_back();
		}
	isTurnFinished=true;
	turnCheckOut();
	int characterblue_hp_indic=getTurn().getTeams()[0]->getListCharacter()[0]->getCurrentHP();
    int characterblue_hp_indic_max=getTurn().getTeams()[0]->getListCharacter()[0]->getMaxHP();
    cout << "HP of Character Blue: " << characterblue_hp_indic << "/" << characterblue_hp_indic_max << endl;
	}
}

bool Engine::turnCheckIn(){
	if (isTurnFinished) {
		isTurnFinished=false;
		currentPlayerId= (currentPlayerId+1) % turn.getTeams().size();

		for (size_t i = 0; i < turn.getTeams()[currentPlayerId]->getListCharacter().size(); i++){
			turn.getTeams()[currentPlayerId]->getListCharacter()[i]->setStatus(Available);
		}
		isTurnBegin=true;
		return true;
	}
	return false;
}

Engine::Engine(state::Turn& turn):turn(turn){
	isGameFinished=false;
	isTurnFinished=false;
	isTurnBegin=true;
	currentPlayerId=0;
}

int Engine::getCurrentPlayerID(){
	return currentPlayerId;
}