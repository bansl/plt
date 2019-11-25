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
      else if((command.stats().getTargetCharacter().getCurrentHP()==command.stats().getTargetCharacter().getMaxHP()&&engine.getTurn().getTeams()[engine.getCurrentPlayerID()]->getItems()[command.stats().getNumber()]->getConsumable().getHealth()>0)||(command.stats().getTargetCharacter().getCurrentMP()==command.stats().getTargetCharacter().getMaxMP()&&engine.getTurn().getTeams()[engine.getCurrentPlayerID()]->getItems()[command.stats().getNumber()]->getConsumable().getMana()>0)){
        score+=-5;
      }
      else{
        score++;
      }
    }
    else if (command.commandType==UseSkillcmd){
      if((command.stats().getTargetCharacter().getCurrentHP()-command.stats().getCharacter().getSkillList()[command.stats().getNumber()]->getDamage())<=0){
        score+=3;
      }
      else{
        score+=2;
      }
    }
    if (command.commandType==Movecmd){
      for(int i=0;i<(int)engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter().size();i++){
        if((command.stats().getDest().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),command.stats().getDest())==1)&&(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Pugilist||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Swordman)){
          score--;
          cout<<"testPos"<<endl;
        }
        else if((command.stats().getDest().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),command.stats().getDest())<=4)&&(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Magician||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Archer)){
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
  cout<<"Team Number "<<teamNumber<<" is playing"<<endl;
  int k=0;
  while(k<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter().size()){
    cout<<"Character Number "<<k<<" is playing"<<endl;
    int maxScore=-500;
    UseSkill commandnull(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],500,0);
    unique_ptr<Command> ptr_command (new UseSkill(commandnull));

    for(int i=0;i<(int)engine.getTurn().getTeams()[1-teamNumber]->getListCharacter().size();i++){
      Attack attacktest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[1-teamNumber]->getListCharacter()[i]);
      if(attacktest.validate(engine.getTurn())){
        cout<<"ici"<<endl;
        engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
        cout<<"la"<<endl;
        if(maxScore<computeScore(attacktest)){
          cout<<"non ici"<<endl;
          maxScore=computeScore(attacktest);
          cout<<"maxscore: "<<maxScore<<endl;
          unique_ptr<Command> ptr_command (new Attack(attacktest));
          cout<<"par ici"<<endl;
        }
      }
    }
    cout<<"Attack"<<endl;

    // for(int x=1;x<(int)engine.getTurn().getMap().size()-1;x++){
    //   for(int y=1;y<(int)engine.getTurn().getMap().size()-1;y++){
    //     Position dest;
    //     dest.setPos(x,y);
    //     Move movetest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k], dest);
    //     cout<<"x : "<<x<<";y :"<<y<<endl;
    //     if(movetest.validate(engine.getTurn())){
    //       cout<<"la"<<endl;
    //       engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
    //       cout<<"ici"<<endl;
    //       if(maxScore<computeScore(movetest)){
    //         cout<<"non ici"<<endl;
    //         maxScore=computeScore(movetest);
    //         cout<<"maxscore: "<<maxScore<<endl;
    //         unique_ptr<Command> ptr_command (new Move (movetest));
    //         cout<<"par ici"<<endl;
    //       }
    //     }
    //   }
    // }
    // cout<<"Move"<<endl;
    //
    // Defend deftest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]);
    // if(deftest.validate(engine.getTurn())){
    //   cout<<"ici"<<endl;
    //   engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
    //   cout<<"la"<<endl;
    //   if(maxScore<computeScore(deftest)){
    //     cout<<"non ici"<<endl;
    //     maxScore=computeScore(deftest);
    //     cout<<"maxscore: "<<maxScore<<endl;
    //     unique_ptr<Command> ptr_command (new Defend (deftest));
    //     cout<<"par ici"<<endl;
    //   }
    // }
    // cout<<"Defend"<<endl;

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
    cout<<"UseObject"<<endl;

    for(int p=0;p<(int)engine.getTurn().getTeams()[1-teamNumber]->getListCharacter().size();p++){
      for(int s=0;s<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getSkillList().size();s++){
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
    cout<<"UseSkill"<<endl;

    if(ptr_command->validate(engine.getTurn())){
      engine.addCommand(move(ptr_command));
      if (ptr_command->commandType==Attackcmd){
				cout << "->attack instruction added " << endl;
      }
      else if (ptr_command->commandType==Movecmd){
        cout << "->move instruction added " << endl;
      }
      else if (ptr_command->commandType==Defendcmd){
        cout << "->defend instruction added " << endl;
      }
      else if (ptr_command->commandType==UseSkillcmd){
        cout << "->useskill instruction added " << endl;
      }
      else if (ptr_command->commandType==UseObjectcmd){
        cout << "->useobject instruction added " << endl;
      }
      k++;
    }
    else{
      EndTurn endturntest(teamNumber);
			if(endturntest.validate(engine.getTurn())){
				unique_ptr<Command> ptr_endturntest (new EndTurn (endturntest));
				engine.addCommand(move(ptr_endturntest));
				k=engine.getTurn().getTeams()[teamNumber]->getListCharacter().size();
        cout << "->endturn instruction added " << endl;
      }
    }
  }
}

void HeuristicAI::runAI(){
	heuristicCommandList(engine,engine.getCurrentPlayerID());
}

HeuristicAI::HeuristicAI(engine::Engine& engine):engine(engine){

}
