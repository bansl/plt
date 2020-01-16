#include <engine.h>
#include <render.h>
#include <state.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "json/json.h"

using namespace state;
using namespace engine;
using namespace render;
using namespace std;

int actiontype=1;
int playeraction=-1;
Character *playingcharaddr;

Character& find_selected_char(state::Turn& turn){
	Position posCurs=turn.getCursor()->getPosition();
	for (size_t team = 0; team < turn.getTeams().size(); team++)
		for (size_t character = 0; character < turn.getTeams()[team]->getListCharacter().size(); character++)
			if (posCurs.distanceBetween(posCurs,turn.getTeams()[team]->getListCharacter()[character]->getPosition())==0) {
				Character & refchar=*turn.getTeams()[team]->getListCharacter()[character];
				return refchar;
			}
	Character c;
	Character& refc=c;
	return 	refc;
}

Character& find_selected_char(state::Turn& turn, int team){
	Position posCurs=turn.getCursor()->getPosition();
	for (size_t character = 0; character < turn.getTeams()[team]->getListCharacter().size(); character++)
		if (posCurs.distanceBetween(posCurs,turn.getTeams()[team]->getListCharacter()[character]->getPosition())==0) {
			Character & refchar=*turn.getTeams()[team]->getListCharacter()[character];
			return refchar;
		}
	Character c;
	Character& refc=c;
	return 	refc;
}

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

void Engine::updateDisplay (sf::RenderWindow& window, std::vector<sf::View> views){

	if(isTurnBegin){
		isTurnBegin=false;
		turn.notifyObservers(turn, window,charRender, views);
		cout << "====TURN " << turn.getTurn() << ": ====" << endl;
		notifyUpdated();
		return;
	}

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

	if(updateisTurnFinished){

		for(size_t i=0; i<commands.size();i++){

				if(!isPlayerPlaying){
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
						turn.notifyObservers(turn, window,fullRender, views);
						pM->getCharacter().setStatus(tempStatus);
						position_history.push_back(pM->getPathToDest()[0]);
					}

					else if (commands[i]->commandType==Attackcmd){
						engine::Attack *pA=dynamic_cast<engine::Attack*>(commands[i].get());
						defending_history.push_back(pA->getDefender().getStatus()==Defending);
					}
				}
				else if (commands[i]->commandType!=EndTurncmd) turn.notifyObservers(turn, window,charRender,views);
				commands[i]->finish(turn);
				turn.notifyObservers(turn, window,charRender, views);

		}
		isPlayerPlaying=false;
		command_history_nb.push_back(0);
		while (!commands.empty()){
				command_history.push_back(move(commands.back()));
				command_history_nb.back()++;
				commands.pop_back();
		}
		if(showStatus){
			vector<string> teamlabel= {"Blue","Red"};
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
		if(turnCheckOut())
		{
			isTurnFinished=true;
			notifyUpdated();
		}

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

void Engine::userInteraction(sf::Event newEvent, sf::RenderWindow& window, std::vector<sf::View>& views){

	if(newEvent.type==sf::Event::KeyPressed ){

		if(!action_bool){ // Move Cursor on The Map
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) views[0].move(+40, -40),window.setView(views[0]);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) views[0].move(-40, -40), window.setView(views[0]);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) views[0].move(-40, +40), window.setView(views[0]);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) views[0].move(40, 40), window.setView(views[0]);

			// update moved cursor
			if (posXupdate != 0 || posYupdate !=0){
				Position nextPosCurs;
				nextPosCurs.setPos(posXcurs+posXupdate, posYcurs+posYupdate);
				turn.getCursor()->cursorMove(nextPosCurs);
				turn.notifyObservers(turn, window, cursorRender, views);
				turn.notifyObservers(turn, window, windowinfoRender, views);
				posXupdate = 0, posYupdate = 0;
			}
			if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && (playeraction==Movecmd) ) {
				cout<<"destination selected"<<endl;
				Position dest=turn.getCursor()->getPosition();
				Move movePlayer(*playingcharaddr, dest);
				if(movePlayer.validate(turn)){
					movePlayer.action(turn);
					turn.notifyObservers(turn, window,fullRender, views);
					unique_ptr<Command> ptr_movePlayer (new Move (movePlayer));
					addCommand(move(ptr_movePlayer));
					cout << "->[SUCCESS]move instruction added " << endl;
					// unique_ptr<Command> ptr_movePlayerQueue (new Move (movePlayer));
					// queuePlayer.push(move(ptr_movePlayerQueue));
				}
				else cout << "->[FAILED]no move instruction added" << endl;
				playeraction=-1;
			}
			if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && (playeraction==Attackcmd) ) {
				cout<<"target selected"<<endl;
				Attack attackPlayer(*playingcharaddr,find_selected_char(turn));
				if(attackPlayer.validate(turn)){
					attackPlayer.action(turn);
					turn.notifyObservers(turn, window,charRender, views);
					unique_ptr<Command> ptr_attackPlayer (new Attack (attackPlayer));
					addCommand(move(ptr_attackPlayer));
					cout << "->[SUCCESS]attack instruction added " << endl;
					// unique_ptr<Command> ptr_attackPlayerQueue (new Attack (attackPlayer));
					// queuePlayer.push(move(ptr_attackPlayerQueue));
				}
				else cout << "->[FAILED]no attack instruction added" << endl;
				playeraction=-1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) playeraction=-1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){ // Enter Action Menu Selection

			if(!action_bool && (find_selected_char(turn,currentPlayerId).getCurrentHP()>0)){
				turn.notifyObservers(turn, window, windowactionRender, views);
				action_bool=!action_bool;
			}
			else if (action_bool){
				turn.notifyObservers(turn, window, windowinfoRender, views);
				action_bool=!action_bool;
			}
		}

		if(action_bool){ // Navigation through the Action Menu Selection
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				if(actiontype>1){
					notifySelectCursorMove(UP);
					actiontype--;
					turn.notifyObservers(turn, window, windowactionRender, views);
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				if(actiontype<6){
					notifySelectCursorMove(DOWN);
					actiontype++;
					turn.notifyObservers(turn, window, windowactionRender, views);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
				cout << "actionselected: " << actiontype<<endl;
				action_bool=!action_bool;
				turn.notifyObservers(turn, window, windowinfoRender, views);
				if (actiontype-1==Movecmd){
					cout << "Move cmd " <<endl;
					playeraction=Movecmd;
					playingcharaddr=&find_selected_char(turn);
				}
				if (actiontype-1==Attackcmd){
					cout << "Attack cmd " <<endl;
					playeraction=Attackcmd;
					playingcharaddr=&find_selected_char(turn);
				}
				if (actiontype-1==Defendcmd){
					cout << "Defend cmd " <<endl;
					playeraction=-1;
					Defend defPlayer(find_selected_char(turn));
					if(defPlayer.validate(turn)){
						defPlayer.action(turn);
						unique_ptr<Command> ptr_defPlayer (new Defend (defPlayer));
						turn.notifyObservers(turn, window,fullRender, views);
						addCommand(move(ptr_defPlayer));
						cout << "->[SUCCESS]defend instruction added " << endl;
						// unique_ptr<Command> ptr_defPlayerQueue (new Defend (defPlayer));
						// queuePlayer.push(move(ptr_defPlayerQueue));
					}
					else cout << "->[FAILED]no defend instruction added" << endl;
				}
				if (actiontype-1==EndTurncmd){
					cout << "Endturn cmd " <<endl;
					playeraction=-1;
					EndTurn endturntest(1);
					if(endturntest.validate(turn)){
						endturntest.action(turn);
						unique_ptr<Command> ptr_endturntest (new EndTurn (endturntest));
						addCommand(move(ptr_endturntest));
						turn.notifyObservers(turn, window,fullRender, views);
						cout << "->[SUCCESS]endturn instruction added " << endl;
						// unique_ptr<Command> ptr_endturnQueue (new EndTurn (endturntest));
						// queuePlayer.push(move(ptr_endturnQueue));
						isPlayerPlaying=true;
						updateDisplay(window,views);
						// revertTurn(window,views);
						// for(int i=0;i<(int)queuePlayer.size();i++){
						// 	unique_ptr<Command> ptr_commandtemp;
					  //   if (queuePlayer.front()->Commandtype==Attackcmd){
					  //     ptr_commandtemp.reset(new Attack(queuePlayer.front()));
					  //   }
					  //   else if (queuePlayer.front()->Commandtype==Movecmd){
					  //     ptr_commandtemp.reset(new Move(queuePlayer.front()));
					  //   }
					  //   else if (queuePlayer.front()->Commandtype==Defendcmd){
					  //     ptr_commandtemp.reset(new Defend(queuePlayer.front()));
					  //   }
					  //   else if (queuePlayer.front()->Commandtype==UseObjectcmd){
					  //     ptr_commandtemp.reset(new UseObject(queuePlayer.front()));
					  //   }
					  //   else if (queuePlayer.front()->Commandtype==UseSkillcmd){
					  //     ptr_commandtemp.reset(new UseSkill(queuePlayer.front()));
					  //   }
						// 	else if (queuePlayer.front()->Commandtype==EndTurncmd){
					  //     ptr_commandtemp.reset(new EndTurn(queuePlayer.front()));
					  //   }
					  //   ptr_commandtemp->validate(turn);
					  //   addCommand(move(ptr_commandtemp));
						// 	queuePlayer.pop();
						// }
						// updateDisplay(window,views);

					}
					else cout << "->[FAILED]no endturn instruction added" << endl;
				}

			}
		}

	}
}

bool Engine::revertTurn(sf::RenderWindow& window, std::vector<sf::View> views){
	if (!command_history.empty())
	{
		turn.revertTurn();
		for (int i = 0; i < command_history_nb.back(); i++)
			{
				if(command_history.back()->commandType==Movecmd) {
					engine::Move *pM=dynamic_cast<engine::Move*>(command_history.back().get());
					pM->getCharacter().getPosition().setPos(position_history.back().getX(),position_history.back().getY());
					position_history.pop_back();
				}
				else if(command_history.back()->commandType==Attackcmd) {
					engine::Attack *pA=dynamic_cast<engine::Attack*>(command_history.back().get());
					if (defending_history.back()) pA->getDefender().setStatus(Defending);
					defending_history.pop_back();
				}
				command_history.back()->revert(turn);
				command_history.pop_back();
			}
		command_history_nb.pop_back();
		turn.notifyObservers(turn, window,fullRender, views);
		if(showStatus){
			vector<string> teamlabel= {"Blue","Red"};
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

std::string Engine::seedCommands(int turnNumber){
	int offset=0;
	std::string seed;
	for (int i=0;i<turnNumber;i++){
		offset+=command_history_nb[i];
	}
	for(int i=0;i<command_history_nb[turnNumber-1];i++){
		if(command_history[offset-1-i]->commandType==Attackcmd){
			seed.append("a");
			int charaNumber=-1;
			Command * pC=command_history[offset-1-i].get();
      engine::Attack *pA=dynamic_cast<engine::Attack*>(pC);
			for(int j=0;j<(int)getTurn().getTeams()[1-turnNumber%2]->getListCharacter().size();j++){
				if(getTurn().getTeams()[1-turnNumber%2]->getListCharacter()[j]->idCharacter==pA->getDefender().idCharacter){
					charaNumber=j;
				}
			}
			seed.append(to_string(charaNumber));
		}

		else if(command_history[offset-1-i]->commandType==Movecmd){
			seed.append("m");
			Command * pC=command_history[offset-1-i].get();
			engine::Move *pM=dynamic_cast<engine::Move*>(pC);
			Position & pos=pM->getDest();
			seed.append(to_string(pos.getX()));
			seed.append("x");
			seed.append(to_string(pos.getY()));
			seed.append("y");
		}

		else if(command_history[offset-1-i]->commandType==UseObjectcmd){
			seed.append("o");
			int charaNumber=-1;
			Command * pC=command_history[offset-1-i].get();
			engine::UseObject *pO=dynamic_cast<engine::UseObject*>(pC);
			for(int j=0;j<(int)getTurn().getTeams()[turnNumber%2]->getListCharacter().size();j++){
				if(getTurn().getTeams()[turnNumber%2]->getListCharacter()[j]->idCharacter==pO->getTargetCharacter().idCharacter){
					charaNumber=j;
				}
			}
			seed.append(to_string(charaNumber));
			seed.append(to_string(pO->getNumberObject()));
		}

		else if(command_history[offset-1-i]->commandType==Defendcmd){
			seed.append("d");
		}

		else if(command_history[offset-1-i]->commandType==UseSkillcmd){
			seed.append("s");
			int charaNumber=-1;
			Command * pC=command_history[offset-1-i].get();
			engine::UseSkill *pS=dynamic_cast<engine::UseSkill*>(pC);
			for(int j=0;j<(int)getTurn().getTeams()[1-turnNumber%2]->getListCharacter().size();j++){
				if(getTurn().getTeams()[1-turnNumber%2]->getListCharacter()[j]->idCharacter==pS->getTargetCharacter().idCharacter){
					charaNumber=j;
				}
			}
			seed.append(to_string(charaNumber));
			seed.append(to_string(pS->getSkillNumber()));
		}

		else if(command_history[offset-1-i]->commandType==EndTurncmd){
			seed.append("e");
		}
	}
	return seed;
}

std::string Engine::seedCommandsPlayer(int turnNumber){
	//cout<<"Start seeding"<<endl;
	int offset=0;
	std::string seed;
	int ennemyTeam=1-turnNumber%2;
	int team=turnNumber%2;
	for (int i=0;i<turnNumber;i++){
		offset+=command_history_nb[i];
	}
	for(int nbChara=0;nbChara<(int)getTurn().getTeams()[team]->getListCharacter().size();nbChara++){
		//cout<<"Start Character Number : "<<nbChara<<" /"<<(int)getTurn().getTeams()[team]->getListCharacter().size()-1<<endl;
		bool hasAdd=false;
		for(int i=0;i<command_history_nb[turnNumber-1];i++){

			if(command_history[offset-1-i]->commandType==Attackcmd){
				Command * pC=command_history[offset-1-i].get();
	      engine::Attack *pA=dynamic_cast<engine::Attack*>(pC);
				if(getTurn().getTeams()[team]->getListCharacter()[nbChara]->idCharacter==pA->getAttacker().idCharacter){
					seed.append("a");
					int charaNumber=-1;
					for(int j=0;j<(int)getTurn().getTeams()[ennemyTeam]->getListCharacter().size();j++){
						if(getTurn().getTeams()[ennemyTeam]->getListCharacter()[j]->idCharacter==pA->getDefender().idCharacter){
							charaNumber=j;
						}
					}
					seed.append(to_string(charaNumber));
					hasAdd=true;
					break;
				}
			}

			else if(command_history[offset-1-i]->commandType==Movecmd){
				Command * pC=command_history[offset-1-i].get();
				engine::Move *pM=dynamic_cast<engine::Move*>(pC);
				if(getTurn().getTeams()[team]->getListCharacter()[nbChara]->idCharacter==pM->getCharacter().idCharacter){
					seed.append("m");
					Position & pos=pM->getDest();
					seed.append(to_string(pos.getX()));
					seed.append("x");
					seed.append(to_string(pos.getY()));
					seed.append("y");
					hasAdd=true;
				}
			}

			else if(command_history[offset-1-i]->commandType==UseObjectcmd){
				Command * pC=command_history[offset-1-i].get();
				engine::UseObject *pO=dynamic_cast<engine::UseObject*>(pC);
				if(getTurn().getTeams()[team]->getListCharacter()[nbChara]->idCharacter==pO->getCharacter().idCharacter){
					seed.append("o");
					int charaNumber=-1;
					for(int j=0;j<(int)getTurn().getTeams()[team]->getListCharacter().size();j++){
						if(getTurn().getTeams()[team]->getListCharacter()[j]->idCharacter==pO->getTargetCharacter().idCharacter){
							charaNumber=j;
						}
					}
					seed.append(to_string(charaNumber));
					seed.append(to_string(pO->getNumberObject()));
					hasAdd=true;
					break;
				}
			}

			else if(command_history[offset-1-i]->commandType==Defendcmd){
				Command * pC=command_history[offset-1-i].get();
				engine::Defend *pD=dynamic_cast<engine::Defend*>(pC);
				if(getTurn().getTeams()[team]->getListCharacter()[nbChara]->idCharacter==pD->getCharacter().idCharacter){
					seed.append("d");
					hasAdd=true;
					break;
				}
			}

			else if(command_history[offset-1-i]->commandType==UseSkillcmd){
				Command * pC=command_history[offset-1-i].get();
				engine::UseSkill *pS=dynamic_cast<engine::UseSkill*>(pC);
				if(getTurn().getTeams()[team]->getListCharacter()[nbChara]->idCharacter==pS->getCharacter().idCharacter){
					seed.append("s");
					int charaNumber=-1;
					for(int j=0;j<(int)getTurn().getTeams()[ennemyTeam]->getListCharacter().size();j++){
						if(getTurn().getTeams()[ennemyTeam]->getListCharacter()[j]->idCharacter==pS->getTargetCharacter().idCharacter){
							charaNumber=j;
						}
					}
					seed.append(to_string(charaNumber));
					seed.append(to_string(pS->getSkillNumber()));
					hasAdd=true;
					break;
				}
			}

		}
		if(!hasAdd){
			seed.append("p");
			//cout<<"Add P!"<<endl;
		}
		//cout<<"Ending Character Number : "<<nbChara<<" /"<<(int)getTurn().getTeams()[team]->getListCharacter().size()-1<<endl;
	}
	//if(command_history[offset-command_history_nb[turnNumber]-1]->commandType==EndTurncmd){
		seed.append("e");
	//}
	//cout<<"End seeding"<<endl;
	return seed;
}

void Engine::loadCommands(std::string seed, int turnNumber,sf::RenderWindow& window, std::vector<sf::View> views){
	// if(turnCheckIn()){
		// updateDisplay(window,views);
		int i=0, charaNumber=0;
		int teamNumber=turnNumber%2;
		while(i<(int)seed.size()){
			char type=seed.at(i);
			if(type==(char)'a'){
				Attack attack(*getTurn().getTeams()[teamNumber]->getListCharacter()[charaNumber],
											*getTurn().getTeams()[1-teamNumber]->getListCharacter()[std::atoi(seed.substr(i+1,1).c_str())]);
				attack.validate(getTurn());
				cout<<"charaNumber : "<<std::atoi(seed.substr(i+1,1).c_str())<<endl;
				unique_ptr<Command> ptr_command(new Attack(attack));

				addCommand(move(ptr_command));
				i+=2;
				charaNumber++;
			}

			else if(type==(char)'d'){
				Defend defend(*turn.getTeams()[teamNumber]->getListCharacter()[charaNumber]);
				defend.validate(turn);
				unique_ptr<Command> ptr_command(new Defend(defend));
				addCommand(move(ptr_command));
				i+=1;
				charaNumber++;
			}

			else if(type==(char)'s'){
				UseSkill useSkill(*getTurn().getTeams()[teamNumber]->getListCharacter()[charaNumber],
													*getTurn().getTeams()[1-teamNumber]->getListCharacter()[std::atoi(seed.substr(i+1,1).c_str())],
													std::atoi(seed.substr(i+2,1).c_str()),
													0);
				useSkill.validate(getTurn());
				cout<<"charaNumber : "<<std::atoi(seed.substr(i+1,1).c_str())<<endl;
				unique_ptr<Command> ptr_command(new UseSkill(useSkill));
				addCommand(move(ptr_command));
				i+=3;
				charaNumber++;
			}

			else if(type==(char)'o'){
				UseObject useObject(*getTurn().getTeams()[teamNumber]->getListCharacter()[std::atoi(seed.substr(i+1,1).c_str())],
													0,
													teamNumber,
													*getTurn().getTeams()[teamNumber]->getListCharacter()[charaNumber]);
				useObject.validate(getTurn());
				cout<<"charaNumber : "<<std::atoi(seed.substr(i+1,1).c_str())<<endl;
				unique_ptr<Command> ptr_command(new UseObject(useObject));
				addCommand(move(ptr_command));
				i+=3;
				charaNumber++;
			}

			else if(type==(char)'e'){
				EndTurn endTurn(getCurrentPlayerID());
				endTurn.validate(getTurn());
				unique_ptr<Command> ptr_command(new EndTurn(endTurn));
				addCommand(move(ptr_command));
				i+=1;
			}

			else if(type==(char)'m'){
				int xnumber=seed.find("x",i), ynumber=seed.find("y",i);
				int x=atoi(seed.substr(i+1,xnumber).c_str());
				int y=atoi(seed.substr(xnumber+1,ynumber).c_str());
				cout<<"x : "<<x<<";y : "<<y<<endl;
				Position dest;
				dest.setPos(x,y);
				Move moveCommand(*turn.getTeams()[teamNumber]->getListCharacter()[charaNumber],
								 dest);
				cout << "move validate begin" << endl;
				if(moveCommand.validate(turn)){
					cout << "move validate end" << endl;
					unique_ptr<Command> ptr_command(new Move(moveCommand));
					addCommand(move(ptr_command));
				}
				i+=ynumber+1;
			}
			else if(type==(char)'p'){
				i+=1;
				charaNumber++;
			}

		}

	// }
	updateDisplay(window,views);
}

void Engine::registerGame(){
	Json::Reader reader;
	Json::Value root;
	Json::StyledStreamWriter writer;

	std::string text = "{ \"mapseed\": \""+turn.seedMap()+"\", \"charseed\": \""+turn.seedTeams()+"\"";
	std::ofstream outFile;


	for (int i=1;i<turn.getTurn();i++){
		text=text+", \"turn"+to_string(i)+"\": \""+seedCommandsPlayer(i)+"\"";
	}
	text=text+" }";
	// Parse JSON and print errors if needed
	if(!reader.parse(text, root)) {
		std::cout << reader.getFormattedErrorMessages();
		exit(1);
	}
	else {

		// Write the output to a file
		outFile.open("replay.txt");
		writer.write(outFile, root);
		outFile.close();
	}
}

void Engine::loadGame(sf::RenderWindow& window, std::vector<sf::View> views){
	cout << "start Loading the game"<< endl;
	std::ifstream file_input("replay.txt");//, std::ifstream::binary);
	Json::Value root;
	file_input >> root;
	cout << "loading Map and Characters"<<endl;

	turn.initTurn(((int)sqrt(root.get("mapseed","").asString().size()/2)),
					root.get("charseed","").asString(),
					root.get("mapseed","").asString());
	cout << ": done"<< endl;

	cout << "start Loading actions"<< endl;
	for(int i=1;i<=(int)root.size()-2;i++){
		cout << "actions no. "<< i <<endl;
		cout << root.get("turn"+to_string(i),"").asString() << endl;
		if(turnCheckIn()){
			loadCommands(root.get("turn"+to_string(i),"").asString(),i,window,views);
		}
	}
}
