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
		return false;
	}
	turn.nextTurn();
	return true;
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
		isTurnBegin=false;
		turn.notifyObservers(turn, window,charRender);
		cout << "====TURN " << turn.getTurn() << ": ====" << endl;
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
	vector<string> teamlabel(2);
	teamlabel[0]="Blue", teamlabel[1]="Red";
	cout << "###########################" << endl << "# CURRENT STATUS" << endl;
	for (size_t k = 0; k < getTurn().getTeams().size(); k++)
	{	
		for (size_t i = 0; i < getTurn().getTeams()[k]->getListCharacter().size(); i++)
		{
			int character_hp_indic=getTurn().getTeams()[k]->getListCharacter()[i]->getCurrentHP();
			int character_hp_indic_max=getTurn().getTeams()[k]->getListCharacter()[i]->getMaxHP();
			int character_mp_indic=getTurn().getTeams()[k]->getListCharacter()[i]->getCurrentMP();
			int character_mp_indic_max=getTurn().getTeams()[k]->getListCharacter()[i]->getMaxMP();
			cout << "# Character " << teamlabel[k] << " " << i << ": " << "HP:" << character_hp_indic << "/" << character_hp_indic_max << " " << "MP:" << character_mp_indic << "/" << character_mp_indic_max << endl;
		}
		
	}
	cout << "###########################" << endl;	
	if(turnCheckOut()) isTurnFinished=true;
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
	isTurnFinished=true;
	isTurnBegin=false;
	currentPlayerId=0;
}

int Engine::getCurrentPlayerID(){
	return currentPlayerId;
}