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
	turn.initBuffer();
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
				engine::Move *pM=dynamic_cast<engine::Move*>(commands[i].get());
				state::StatusList tempStatus=pM->getCharacter().getStatus();
				pM->getCharacter().setStatus(Moving);
				// engine::Move *pM=dynamic_cast<engine::Move*>(commands[i].get());
				// for(size_t j=0;j<pM->getPathToDest().size();j++){
				// 	pM->getCharacter().getPosition().setPos(pM->getPathToDest()[j].getX(),pM->getPathToDest()[j].getY());
				// 	turn.notifyObservers(turn, window,fullRender);
			 	// }
				// commands[i]->action(turn);
				turn.notifyObservers(turn, window,fullRender);
				pM->getCharacter().setStatus(tempStatus);
				position_history.push_back(pM->getPathToDest()[0]);
			}
			else if (commands[i]->commandType!=EndTurncmd) turn.notifyObservers(turn, window,charRender);
			commands[i]->finish(turn);
			turn.notifyObservers(turn, window,charRender);
		}
		command_history_nb.push_back(0);
	while (!commands.empty()){
			command_history.push_back(move(commands.back()));
			command_history_nb.back()++;
			commands.pop_back();
	}
	if(showStatus){
		vector<string> teamlabel(2);
		teamlabel[0]="Blue", teamlabel[1]="Red";
		cout << "###########################" << endl << "# CURRENT STATUS" << endl;
		std::vector<string> jobs = {"Pugilist", "Swordman", "Archer", "Magician"};
		std::vector<string> races = {"Monster", "Beastman", "Demon", "Human"};
		for (size_t k = 0; k < getTurn().getTeams().size(); k++)
		{
			for (size_t i = 0; i < getTurn().getTeams()[k]->getListCharacter().size(); i++)
			{
				int character_hp_indic=getTurn().getTeams()[k]->getListCharacter()[i]->getCurrentHP();
				int character_hp_indic_max=getTurn().getTeams()[k]->getListCharacter()[i]->getMaxHP();
				int character_mp_indic=getTurn().getTeams()[k]->getListCharacter()[i]->getCurrentMP();
				int character_mp_indic_max=getTurn().getTeams()[k]->getListCharacter()[i]->getMaxMP();
				JobType character_job=getTurn().getTeams()[k]->getListCharacter()[i]->getJob().getJob();
				RaceType character_race=getTurn().getTeams()[k]->getListCharacter()[i]->getRace().getRace();
				cout << "# Character " << teamlabel[k] << " " << i << ": " << "HP:" << character_hp_indic << "/" << character_hp_indic_max << " " << "MP:" << character_mp_indic << "/" << character_mp_indic_max << " | Job: "<< jobs[character_job-1] << " | Race: " << races[character_race-1]<<endl;
			}

		}
		cout << "###########################" << endl;
	}
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

void Engine::userInteraction(sf::Event newEvent, sf::RenderWindow& window, sf::View& view){

	RenderType cursorRefresh(cursorRender);
	if(newEvent.type==sf::Event::KeyPressed ){

		int posXupdate = 0, posYupdate = 0;
		size_t posXcurs=turn.getCursor()->getPosition().getX();
		size_t posYcurs=turn.getCursor()->getPosition().getY();
		size_t mapsize=turn.getMap().size();
		std::vector<sf::Keyboard::Key> direction_keys={sf::Keyboard::Up,sf::Keyboard::Left,sf::Keyboard::Down,sf::Keyboard::Right};
		// direction input
		if (sf::Keyboard::isKeyPressed(direction_keys[turn.rotation%4])){
			if(posXcurs!=0) posXupdate = -1;
			// else posXupdate = mapsize-1 -posXcurs;
		}
		else if (sf::Keyboard::isKeyPressed(direction_keys[(turn.rotation+3)%4])){
			if(posYcurs!=mapsize-1) posYupdate = 1;
			// else posYupdate = -posYcurs;
		}
		else if (sf::Keyboard::isKeyPressed(direction_keys[(turn.rotation+2)%4])){
			if(posXcurs!=mapsize-1) posXupdate = 1;
			// else posXupdate = -posXcurs;
		}
		else if (sf::Keyboard::isKeyPressed(direction_keys[(turn.rotation+1)%4])){
			if(posYcurs!=0) posYupdate = -1;
			// else posYupdate = mapsize-1 -posYcurs;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) view.move(+40, -40),window.setView(view);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) view.move(-40, -40), window.setView(view);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) view.move(-40, +40), window.setView(view);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) view.move(40, 40), window.setView(view);

		// update moved cursor
		if (posXupdate != 0 || posYupdate !=0){
			Position nextPosCurs;
			nextPosCurs.setPos(posXcurs+posXupdate, posYcurs+posYupdate);
			turn.getCursor()->cursorMove(nextPosCurs);
			turn.notifyObservers(turn, window,cursorRefresh);
			posXupdate = 0, posYupdate = 0;
		}



	}
}

bool Engine::revertTurn(sf::RenderWindow& window){
	if (!command_history.empty())
	{
		for (int i = 0; i < command_history_nb.back(); i++)
			{
				if(command_history.back()->commandType==Movecmd) {
					engine::Move *pM=dynamic_cast<engine::Move*>(command_history.back().get());
					pM->getCharacter().getPosition().setPos(position_history.back().getX(),position_history.back().getY());
					position_history.pop_back();
				}
				command_history.back()->revert(turn);
				command_history.pop_back();
			}
		command_history_nb.pop_back();
		turn.notifyObservers(turn, window,fullRender);
		if(showStatus){
			vector<string> teamlabel(2);
			teamlabel[0]="Blue", teamlabel[1]="Red";
			cout << "###########################" << endl << "# CURRENT STATUS" << endl;
			std::vector<string> jobs = {"Pugilist", "Swordman", "Archer", "Magician"};
			std::vector<string> races = {"Monster", "Beastman", "Demon", "Human"};
			for (size_t k = 0; k < getTurn().getTeams().size(); k++)
			{
				for (size_t i = 0; i < getTurn().getTeams()[k]->getListCharacter().size(); i++)
				{
					int character_hp_indic=getTurn().getTeams()[k]->getListCharacter()[i]->getCurrentHP();
					int character_hp_indic_max=getTurn().getTeams()[k]->getListCharacter()[i]->getMaxHP();
					int character_mp_indic=getTurn().getTeams()[k]->getListCharacter()[i]->getCurrentMP();
					int character_mp_indic_max=getTurn().getTeams()[k]->getListCharacter()[i]->getMaxMP();
					JobType character_job=getTurn().getTeams()[k]->getListCharacter()[i]->getJob().getJob();
					RaceType character_race=getTurn().getTeams()[k]->getListCharacter()[i]->getRace().getRace();
					cout << "# Character " << teamlabel[k] << " " << i << ": " << "HP:" << character_hp_indic << "/" << character_hp_indic_max << " " << "MP:" << character_mp_indic << "/" << character_mp_indic_max << " | Job: "<< jobs[character_job-1] << " | Race: " << races[character_race-1]<<endl;
				}

			}
			cout << "###########################" << endl;
		}
		return true;
	}
	return false;
}
