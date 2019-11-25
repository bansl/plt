#include "../ai.h"
#include "../engine.h"
#include <random>
#include <iostream>
using namespace std;
using namespace ai;
using namespace engine;
using namespace state;

int HeuristicAI::computeScore(engine::Command& command){
    int score=0;
    if (command.commandType==Attackcmd){
      if((command.stats().getTargetCharacter().getCurrentHP()-command.stats().getCharacter().getAttackPower()+command.stats().getTargetCharacter().getDefense())<=0){
        score+=4;
      }
      else{
        score+=3;
      }
    }
    else if (command.commandType==Defendcmd){
      for(int i=0;i<(int)engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter().size();i++){
        if(command.stats().getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),command.stats().getCharacter().getPosition())==1&&(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Pugilist||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Swordman)){
          score++;
        }
        else if(command.stats().getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),command.stats().getCharacter().getPosition())<=4&&(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Magician||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Archer)){
          score++;
        }
      }
    }
    else if (command.commandType==UseObjectcmd){
      if((command.stats().getTargetCharacter().getCurrentHP()<(int)command.stats().getTargetCharacter().getCurrentHP()/5)&&(command.stats().getTargetCharacter().getCurrentHP()+engine.getTurn().getTeams()[engine.getCurrentPlayerID()]->getItems()[command.stats().getNumber()]->getConsumable().getHealth()>=command.stats().getTargetCharacter().getCurrentHP()/5)){
        score+=3;
      }
      else if((command.stats().getTargetCharacter().getCurrentHP()<(int)command.stats().getTargetCharacter().getCurrentMP()/5)&&(command.stats().getTargetCharacter().getCurrentMP()+engine.getTurn().getTeams()[engine.getCurrentPlayerID()]->getItems()[command.stats().getNumber()]->getConsumable().getMana()>=command.stats().getTargetCharacter().getCurrentMP()/5)){
        score+=2;
      }
      else{
        score++;
      }
    }
    else if (command.commandType==UseSkillcmd){
      if((command.stats().getTargetCharacter().getCurrentHP()-command.stats().getCharacter().getListSkill()[command.stats().getNumber()]->getDamage())<=0){
        score+=3;
      }
      else{
        score+=2;
      }
    }
    if (command.commandType==Movecmd){
      for(int i=0;i<(int)engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter().size();i++){
        if(command.stats().getDest().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),command.stats().getDest())==1&&(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Pugilist||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Swordman)){
          score--;
        }
        else if(command.stats().getDest().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),command.stats().getDest())<=4&&(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Magician||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Archer)){
          score--;
        }
      }
    }
    else{
      for(int i=0;i<(int)engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter().size();i++){
        if(command.stats().getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),command.stats().getCharacter().getPosition())==1&&(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Pugilist||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Swordman)){
          score--;
        }
        else if(command.stats().getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),command.stats().getCharacter().getPosition())<=4&&(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Magician||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Archer)){
          score--;
        }
      }
    }
    return score;
}


void HeuristicAI::heuristicCommandList(engine::Engine& engine, int teamNumber){
  int k=0;
  while(k<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter().size()){
    int maxScore=-500;
    unique_ptr<Command> ptr_command;
    for(int i=0;i<(int)engine.getTurn().getTeams()[1-teamNumber]->getListCharacter().size();i++){
      Attack attacktest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[1-teamNumber]->getListCharacter()[i]);
      if(attacktest.validate(engine.getTurn())){
        engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
        if(maxScore<computeScore(attacktest)){
          maxScore=computeScore(attacktest);
          unique_ptr<Command> ptr_command (new Attack(attacktest));
        }
      }
    }
    for(int x=0;x<(int)engine.getTurn().getMap().size();x++){
      for(int y=0;y<(int)engine.getTurn().getMap().size();y++){
        Position dest;
        dest.setPos(x,y);
        Move movetest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k], dest);
        if(movetest.validate(engine.getTurn())){
          engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
          if(maxScore<computeScore(movetest)){
            maxScore=computeScore(movetest);
            unique_ptr<Command> ptr_command (new Move (movetest));
          }
        }
      }
    }
    Defend deftest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]);
    if(deftest.validate(engine.getTurn())){
      engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
      if(maxScore<computeScore(deftest)){
        maxScore=computeScore(deftest);
        unique_ptr<Command> ptr_deftest (new Defend (deftest));
      }
    }
    for (int o=0;o<(int)engine.getTurn().getTeams()[teamNumber]->getItems().size();o++){
      for (int c=0;c<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter().size();c++){
        UseObject testUseObject(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[c],o,teamNumber,*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]);
  			if(testUseObject.validate(engine.getTurn())){
          engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
          if(maxScore<computeScore(testUseObject)){
            maxScore=computeScore(testUseObject);
  				  unique_ptr<Command> ptr_command (new UseObject(testUseObject));
          }
        }
      }
    }
    for(int p=0;p<(int)engine.getTurn().getTeams()[1-teamNumber]->getListCharacter().size();p++){
      for(int s=0;s<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getListSkill().size();s++){
        UseSkill testUseSkill(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[1-teamNumber]->getListCharacter()[p],s,0);
			  if(testUseSkill.validate(engine.getTurn())){
				      engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
              if(maxScore<computeScore(testUseSkill)){
                maxScore=computeScore(testUseSkill);
                unique_ptr<Command> ptr_command (new UseSkill(testUseSkill));
              }
        }
      }
    }
    if(ptr_command->validate(engine.getTurn())){
      engine.addCommand(move(ptr_command));
      k++;
    }
    else{
      EndTurn endturntest(teamNumber);
			if(endturntest.validate(engine.getTurn())){
				unique_ptr<Command> ptr_endturntest (new EndTurn (endturntest));
				engine.addCommand(move(ptr_endturntest));
				k=engine.getTurn().getTeams()[teamNumber]->getListCharacter().size();
      }
    }
  }
}

void HeuristicAI::runAI(){
	heuristicCommandList(engine,engine.getCurrentPlayerID());
}

HeuristicAI::HeuristicAI(engine::Engine& engine):engine(engine){

}
