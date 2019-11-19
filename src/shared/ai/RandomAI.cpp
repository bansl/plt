#include "../ai.h"
#include "../engine.h"
#include <random>
#include <iostream>
using namespace std;
using namespace ai;
using namespace engine;
using namespace state;

void RandomAI::randomCommandList(engine::Engine& engine, int teamNumber){
	size_t k=0;
	cout << "team playing:" << teamNumber << endl;
	while(k<engine.getTurn().getTeams()[teamNumber]->getListCharacter().size()){  
		std::random_device dev;
  		std::mt19937 rng(dev());
  		std::uniform_int_distribution<std::mt19937::result_type> distribution(1,6);
		std::uniform_int_distribution<std::mt19937::result_type> distributionPos(0,engine.getTurn().getMap().size()-1);
  		std::uniform_int_distribution<std::mt19937::result_type> distributionTeam(0,engine.getTurn().getTeams().size()-1);
		int rndCommandtype=distribution(rng);
		int rndPosX=distributionPos(rng);
		int rndPosY=distributionPos(rng);
		int rndTeam=distributionTeam(rng);
		std::uniform_int_distribution<std::mt19937::result_type> distributionChar(0,engine.getTurn().getTeams()[rndTeam]->getListCharacter().size()-1);
		int rndCharacter=distributionChar(rng);

		Position dest;
		dest.setPos(rndPosX,rndPosY);
		
		// cout << "cmd type:" << rndCommandtype << endl;
		// cout << "rndPosX:" << rndPosX << endl;
		// cout << "rndPosY:" << rndPosY << endl;
		// cout << "rndteam:" << rndTeam << endl;
		// cout << "charact:" << rndCharacter << endl;

		switch (rndCommandtype)
		{
		case 1: 
		{
			/* ATTACK */
			// cout << "Attacking" << endl;
			Attack attacktest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[rndTeam]->getListCharacter()[rndCharacter]);
			if(attacktest.validate(engine.getTurn())){
				unique_ptr<Command> ptr_attacktest (new Attack (attacktest));
				engine.addCommand(move(ptr_attacktest));
				cout << "->[SUCCESS]attack instruction added " << endl;
				k++;
			}
			// else cout << "->[FAILED]no attack instruction added" << endl;
			break;	
		}
		case 2: 
		{
			/* MOVE */
			// cout << "Moving" << endl;
			Move movetest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k], dest);
			if(movetest.validate(engine.getTurn())){
				unique_ptr<Command> ptr_movetest (new Move (movetest));
				engine.addCommand(move(ptr_movetest));
				cout << "->[SUCCESS]move instruction added " << endl;
				k++;
			}
			// else cout << "->[FAILED]no move instruction added" << endl;
			break;
		}
		case 3: 
		{
			/* USE OBJECT */
			// cout << "Using an object" << endl;
			UseObject testUseItem(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],0,0,*engine.getTurn().getTeams()[rndTeam]->getListCharacter()[rndCharacter]);
			if(testUseItem.validate(engine.getTurn())){
				unique_ptr<Command> ptr_testUseItem (new UseObject (testUseItem));
				engine.addCommand(move(ptr_testUseItem));
				cout << "->[SUCCESS]objectuse instruction added " << endl;
				k++;
			}
			// else cout << "->[FAILED]no objectuse instruction added" << endl;
			break;
		}
		case 4: 
		{
			/* DEFEND */
			// cout << "Defending" << endl;
			Defend deftest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]);
			if(deftest.validate(engine.getTurn())){
				unique_ptr<Command> ptr_deftest (new Defend (deftest));
				engine.addCommand(move(ptr_deftest));
				cout << "->[SUCCESS]defend instruction added " << endl;
				k++;
			}
			// else cout << "->[FAILED]no defend instruction added" << endl;
			break;
		}
		case 5: 
		{
			/* USE SKILL */
			// cout << "Using a Skill" << endl;
			UseSkill testUseSkill(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[rndTeam]->getListCharacter()[rndCharacter],0,0);
			if(testUseSkill.validate(engine.getTurn())){
				std::unique_ptr<UseSkill> ptr_testUseSkill (new UseSkill(testUseSkill));
				engine.addCommand(move(ptr_testUseSkill));
				cout << "->[SUCCESS]skilluse instruction added " << endl;
				k++;
			}
			// else cout << "->[FAILED]no skilluse instruction added" << endl;
			break;
		}
		case 6: 
		{
			/* END TURN */
			// cout << "Skipping Turn" << endl;
			EndTurn endturntest(teamNumber);
			if(endturntest.validate(engine.getTurn())){
				unique_ptr<Command> ptr_endturntest (new EndTurn (endturntest));
				engine.addCommand(move(ptr_endturntest));
				cout << "->[SUCCESS]endturn instruction added " << endl;
				k=engine.getTurn().getTeams()[teamNumber]->getListCharacter().size();
			}
			// else cout << "->[FAILED]no endturn instruction added" << endl;			
			break;
		}
		default:
			break;
		}
	}
	
}

void RandomAI::runAI(){
	randomCommandList(engine,engine.getCurrentPlayerID());
}

RandomAI::RandomAI(engine::Engine& engine):engine(engine){
	
}