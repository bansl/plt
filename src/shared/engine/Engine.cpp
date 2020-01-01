#include <engine.h>
#include <render.h>
#include <state.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "json/json.h"

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

void Engine::updateDisplay (sf::RenderWindow& window, std::vector<sf::View> views){
	cout << "werwr" << endl;

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
			else if (commands[i]->commandType!=EndTurncmd) turn.notifyObservers(turn, window,charRender,views);
			commands[i]->finish(turn);
			turn.notifyObservers(turn, window,charRender, views);
		}
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) turn.notifyObservers(turn, window, windowactionRender, views);

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
	for (int i=0;i<turnNumber-1;i++){
		offset+=command_history_nb[i];
	}
	for(int i=0;i<command_history_nb[turnNumber-1];i++){
		if(command_history[i+offset]->commandType==Attackcmd){
			seed.append("a");
			int charaNumber=-1;
			Command * pC=command_history[i+offset].get();
      engine::Attack *pA=dynamic_cast<engine::Attack*>(pC);
			for(int j=0;j<(int)getTurn().getTeams()[1-turnNumber%2]->getListCharacter().size();j++){
				if(getTurn().getTeams()[1-turnNumber%2]->getListCharacter()[j]->idCharacter==pA->getDefender().idCharacter){
					charaNumber=j;
				}
			}
			seed.append(to_string(charaNumber));
		}

		else if(command_history[i+offset]->commandType==Movecmd){
			seed.append("m");
			Command * pC=command_history[i+offset].get();
			engine::Move *pM=dynamic_cast<engine::Move*>(pC);
			Position & pos=pM->getDest();
			seed.append(to_string(pos.getX()));
			seed.append("x");
			seed.append(to_string(pos.getY()));
			seed.append("y");
		}

		else if(command_history[i+offset]->commandType==UseObjectcmd){
			seed.append("o");
			int charaNumber=-1;
			Command * pC=command_history[i+offset].get();
			engine::UseObject *pO=dynamic_cast<engine::UseObject*>(pC);
			for(int j=0;j<(int)getTurn().getTeams()[turnNumber%2]->getListCharacter().size();j++){
				if(getTurn().getTeams()[turnNumber%2]->getListCharacter()[j]->idCharacter==pO->getTargetCharacter().idCharacter){
					charaNumber=j;
				}
			}
			seed.append(to_string(charaNumber));
			seed.append(to_string(pO->getNumberObject()));
		}

		else if(command_history[i+offset]->commandType==Defendcmd){
			seed.append("d");
		}

		else if(command_history[i+offset]->commandType==UseSkillcmd){
			seed.append("s");
			int charaNumber=-1;
			Command * pC=command_history[i+offset].get();
			engine::UseSkill *pS=dynamic_cast<engine::UseSkill*>(pC);
			for(int j=0;j<(int)getTurn().getTeams()[1-turnNumber%2]->getListCharacter().size();j++){
				if(getTurn().getTeams()[1-turnNumber%2]->getListCharacter()[j]->idCharacter==pS->getTargetCharacter().idCharacter){
					charaNumber=j;
				}
			}
			seed.append(to_string(charaNumber));
			seed.append(to_string(pS->getSkillNumber()));
		}

		else if(command_history[i+offset]->commandType==EndTurncmd){
			seed.append("e");
		}
	}
	return seed;
}

void Engine::loadCommands(std::string seed, int turnNumber){
	int i=0, charaNumber=0;
	int teamNumber=turnNumber%2;
	while(i<(int)seed.size()){
		char type=seed.at(i);

		if(type==(char)'a'){
			Attack attack(*getTurn().getTeams()[teamNumber]->getListCharacter()[charaNumber],
										*getTurn().getTeams()[1-teamNumber]->getListCharacter()[std::stoi(seed.substr(i+1,1))]);
			attack.validate(getTurn());
			unique_ptr<Command> ptr_command(new Attack(attack));
			addCommand(move(ptr_command));
			i+=2;
			charaNumber++;
		}

		else if(type==(char)'d'){
			Defend defend(*getTurn().getTeams()[teamNumber]->getListCharacter()[charaNumber]);
			defend.validate(getTurn());
			unique_ptr<Command> ptr_command(new Defend(defend));
			addCommand(move(ptr_command));
			i+=1;
			charaNumber++;
		}

		else if(type==(char)'s'){
			UseSkill useSkill(*getTurn().getTeams()[teamNumber]->getListCharacter()[charaNumber],
												*getTurn().getTeams()[1-teamNumber]->getListCharacter()[std::stoi(seed.substr(i+1,1))],
												std::stoi(seed.substr(i+2,1)),
												0);
			useSkill.validate(getTurn());
			unique_ptr<Command> ptr_command(new UseSkill(useSkill));
			addCommand(move(ptr_command));
			i+=3;
			charaNumber++;
		}

		else if(type==(char)'o'){
			UseObject useObject(*getTurn().getTeams()[teamNumber]->getListCharacter()[std::stoi(seed.substr(i+1,1))],
												0,
												teamNumber,
												*getTurn().getTeams()[teamNumber]->getListCharacter()[charaNumber]);
			useObject.validate(getTurn());
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
			int xnumber=0,ynumber=0;
			while((char)seed.at(i+1+xnumber)==(char)'x'){
				xnumber++;
			}
			while((char)seed.at(i+2+xnumber+ynumber)==(char)'y'){
				ynumber++;
			}
			int x=std::stoi(seed.substr(i+1,xnumber));
			int y=std::stoi(seed.substr(i+2+xnumber,ynumber));
			Position dest;
			dest.setPos(x,y);
			Move moveCommand(*getTurn().getTeams()[teamNumber]->getListCharacter()[charaNumber],
								dest);
			moveCommand.validate(getTurn());
			unique_ptr<Command> ptr_command(new Move(moveCommand));
			addCommand(move(ptr_command));
			i+=3+xnumber+ynumber;
		}

	}
}

void Engine::registerGame(){
	Json::Reader reader;
	Json::Value root;
	Json::StyledStreamWriter writer;
	
	std::string text = "{ \"mapSeed\": \""+turn.seedMap()+"\", \"charSeed\": \""+turn.seedTeams()+"\"";
	std::ofstream outFile;


	for (int i=1;i<turn.getTurn();i++){
		text=text+", \"turn"+to_string(i)+"\": \""+seedCommands(i);
	}
	text=text+" }";
	// Parse JSON and print errors if needed
	if(!reader.parse(text, root)) {
		std::cout << reader.getFormattedErrorMessages();
		exit(1);
	}
	else {

		// Write the output to a file
		outFile.open("save.json");
		writer.write(outFile, root);
		outFile.close();
	}
}

void Engine::loadGame(){
	std::ifstream file_input("save.json");
	Json::Reader reader;
	Json::Value root;
	if(!reader.parse(file_input, root)) {
		std::cout << reader.getFormattedErrorMessages();
		exit(1);
	}
	turn.initTurn((int)std::sqrt(root["mapSeed"].toStyledString().size()),root["mapSeed"].toStyledString(),root["charSeed"].toStyledString());
	for(int i=1;i<(int)root.size()-1;i++){
		loadCommands("turn"+to_string(i),i);
	}
}
