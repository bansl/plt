#include "../ai.h"
#include "../engine.h"
#include <iostream>
using namespace std;
using namespace ai;
using namespace engine;
using namespace state;

int HeuristicAI::computeScore(engine::Command& command){
    int score=0;
    if (command.commandType==Attackcmd){
      Command * pC=&command;
      engine::Attack *pA=dynamic_cast<engine::Attack*>(pC);
      if((pA->getDefender().getCurrentHP()-pA->getAttacker().getAttackPower()+pA->getDefender().getDefense())<=0){
        score+=8;
      }
      else{
        score+=5;
      }
      for(int i=0;i<(int)engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter().size();i++){
        if(pA->getAttacker().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pA->getAttacker().getPosition())<=6){
          if(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Pugilist||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Swordman){
            score--;
          }
        }
        else if(pA->getAttacker().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pA->getAttacker().getPosition())<=9){
          if(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Magician||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Archer){
            score--;
          }
        }
      }
    }
    else if (command.commandType==Defendcmd){
      Command * pC=&command;
      engine::Defend *pD=dynamic_cast<engine::Defend*>(pC);
      for(int i=0;i<(int)engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter().size();i++){
        if(pD->getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pD->getCharacter().getPosition())<=6){
          if(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Pugilist||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Swordman){
            score+=2;
          }
        }
        else if(pD->getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pD->getCharacter().getPosition())<=9){
          if(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Magician||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Archer){
            score+=2;
          }
        }
      }
      for(int i=0;i<(int)engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter().size();i++){
        if(pD->getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pD->getCharacter().getPosition())<=6){
          if(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Pugilist||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Swordman){
            score--;
          }
        }
        else if(pD->getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pD->getCharacter().getPosition())<=9){
          if(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Magician||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Archer){
            score--;
          }
        }
      }
    }
    else if (command.commandType==UseObjectcmd){
      Command * pC=&command;
      engine::UseObject *pUO=dynamic_cast<engine::UseObject*>(pC);
      if((pUO->getTargetCharacter().getCurrentHP()<(int)pUO->getTargetCharacter().getCurrentHP()/5)&&(pUO->getTargetCharacter().getCurrentHP()+engine.getTurn().getTeams()[engine.getCurrentPlayerID()]->getItems()[pUO->getNumberObject()]->getConsumable().getHealth()>=pUO->getTargetCharacter().getCurrentHP()/5)){
        score+=5;
      }
      else if((pUO->getTargetCharacter().getCurrentHP()<(int)pUO->getTargetCharacter().getCurrentMP()/5)&&(pUO->getTargetCharacter().getCurrentMP()+engine.getTurn().getTeams()[engine.getCurrentPlayerID()]->getItems()[pUO->getNumberObject()]->getConsumable().getMana()>=pUO->getTargetCharacter().getCurrentMP()/5)){
        score+=3;
      }
      else if((pUO->getTargetCharacter().getCurrentHP()==pUO->getTargetCharacter().getMaxHP()&&engine.getTurn().getTeams()[engine.getCurrentPlayerID()]->getItems()[pUO->getNumberObject()]->getConsumable().getHealth()>0)||(pUO->getTargetCharacter().getCurrentMP()==pUO->getTargetCharacter().getMaxMP()&&engine.getTurn().getTeams()[engine.getCurrentPlayerID()]->getItems()[pUO->getNumberObject()]->getConsumable().getMana()>0)){
        score+=-5;
      }
      else{
        score++;
      }
      for(int i=0;i<(int)engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter().size();i++){
        if(pUO->getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pUO->getCharacter().getPosition())<=6){
          if(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Pugilist||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Swordman){
            score--;
          }
        }
        else if(pUO->getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pUO->getCharacter().getPosition())<=9){
          if(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Magician||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Archer){
            score--;
          }
        }
      }
    }
    else if (command.commandType==UseSkillcmd){
      Command * pC=&command;
      engine::UseSkill *pUS=dynamic_cast<engine::UseSkill*>(pC);
      if((pUS->getTargetCharacter().getCurrentHP()-pUS->getCharacter().getSkillList()[pUS->getSkillNumber()]->getDamage())<=0){
        score+=3;
      }
      else{
        score+=2;
      }
      for(int i=0;i<(int)engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter().size();i++){
        if(pUS->getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pUS->getCharacter().getPosition())<=6){
          if(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Pugilist||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Swordman){
            score--;
          }
        }
        else if(pUS->getCharacter().getPosition().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pUS->getCharacter().getPosition())<=9){
          if(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Magician||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Archer){
            score--;
          }
        }
      }
    }
    else if (command.commandType==Movecmd){
      Command * pC=&command;
      engine::Move *pM=dynamic_cast<engine::Move*>(pC);
      bool onlyOne=true;
      for(int i=0;i<(int)engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter().size();i++){
        if((pM->getDest().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pM->getDest())<=6)&&(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Pugilist||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Swordman)){
          score+=-1;
        }
        else if((pM->getDest().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pM->getDest())<=9)&&(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Magician||engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getJob().getJob()==Archer)){
          score+=-1;
        }
        else{
          score+=1;
        }
        if((pM->getDest().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pM->getDest())<=4)&&(pM->getCharacter().getJob().getJob()==Magician||pM->getCharacter().getJob().getJob()==Archer)){
          if(onlyOne){
            score+=6+(pM->getDest().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pM->getDest()));
            onlyOne=false;
          }
        }
        else if((pM->getDest().distanceBetween(engine.getTurn().getTeams()[1-engine.getCurrentPlayerID()]->getListCharacter()[i]->getPosition(),pM->getDest())<=1)&&(pM->getCharacter().getJob().getJob()==Swordman||pM->getCharacter().getJob().getJob()==Pugilist)){
          if(onlyOne){
            score+=7;
            onlyOne=false;
          }
        }
      }
    }
    return score;
}


void HeuristicAI::heuristicCommandList(engine::Engine& engine, int teamNumber){
  heuristicCommandList(engine,teamNumber,0,true);
}

void HeuristicAI::runAI(){
	heuristicCommandList(engine,engine.getCurrentPlayerID());
}

void HeuristicAI::runAI(int numberNextCharacter, bool hasNotMoved){
  heuristicCommandList(engine,engine.getCurrentPlayerID(),numberNextCharacter,hasNotMoved);
}

HeuristicAI::HeuristicAI(engine::Engine& engine):engine(engine){

}

void HeuristicAI::heuristicCommandList(engine::Engine& engine,int teamNumber,int numberNextCharacter, bool hasNotMoved){
  int k=numberNextCharacter;
  bool hNM=hasNotMoved;
  while(k<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter().size()){
    if(hasNotMoved){
      if(showText) cout<<"Character Number "<<k<<" is playing"<<endl;
    }
    int maxScore=-500;
    UseSkill commandnull(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],500,0);
    unique_ptr<Command> ptr_command (new UseSkill(commandnull));

    // cout<<"Start Attack scoring"<<endl;
    for(int i=0;i<(int)engine.getTurn().getTeams()[1-teamNumber]->getListCharacter().size();i++){
      Attack attacktest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[1-teamNumber]->getListCharacter()[i]);
      if(attacktest.validate(engine.getTurn())){
        engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
        if(maxScore<computeScore(attacktest)){
          maxScore=computeScore(attacktest);
          // cout<<"New MaxScore: "<<maxScore<<endl;
          ptr_command.reset(new Attack(attacktest));
        }
      }
    }
    // cout<<"End Attack scoring"<<endl;

    cout<<"Start Move scoring"<<endl;
    if(hNM){
      int tempX=engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getX();
      int tempY=engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getY();
        for(int x=max((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getX()-5,1);x<min((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getX()+5,(int)engine.getTurn().getMap().size()-1);x++){
          for(int y=max(1,(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getY()-5);y<min((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getY()+5,(int)engine.getTurn().getMap().size()-1);y++){
            Position dest;
            dest.setPos(x,y);
            Move movetest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k], dest);
            // cout<<"Position: x : "<<x<<";y :"<<y<<endl;
            if(movetest.validate(engine.getTurn())){
              engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
              engine.getTurn().getBuffer().pop_back();
              engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().setPos(tempX,tempY);
              if(maxScore<computeScore(movetest)){
                maxScore=computeScore(movetest);
                // cout<<"New MaxScore: "<<maxScore<<endl;
                ptr_command.reset(new Move (movetest));
              }
            }
          }
        }
      }
      cout<<"End Move scoring"<<endl;

    // cout<<"Start Defend scoring"<<endl;
    Defend deftest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]);
    if(deftest.validate(engine.getTurn())){
      engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
      if(maxScore<computeScore(deftest)){
        maxScore=computeScore(deftest);
        // cout<<"New MaxScore: "<<maxScore<<endl;
        ptr_command.reset(new Defend (deftest));
      }
    }
    // cout<<"End Defend scoring"<<endl;

    // cout<<"Start UseObject scoring"<<endl;
    for (int o=0;o<(int)engine.getTurn().getTeams()[teamNumber]->getItems().size();o++){
      for (int c=0;c<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter().size();c++){
        UseObject testUseObject(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[c],o,teamNumber,*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]);
        if(testUseObject.validate(engine.getTurn())){
          engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
          if(maxScore<computeScore(testUseObject)){
            maxScore=computeScore(testUseObject);
            // cout<<"New MaxScore: "<<maxScore<<endl;
            ptr_command.reset(new UseObject(testUseObject));
          }
        }
      }
    }
    // cout<<"End UseObject scoring"<<endl;

    // cout<<"Start UseSkill scoring"<<endl;
    for(int p=0;p<(int)engine.getTurn().getTeams()[1-teamNumber]->getListCharacter().size();p++){
      for(int s=0;s<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getSkillList().size();s++){
        UseSkill testUseSkill(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[1-teamNumber]->getListCharacter()[p],s,0);
        if(testUseSkill.validate(engine.getTurn())){
              engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
              if(maxScore<computeScore(testUseSkill)){
                maxScore=computeScore(testUseSkill);
                // cout<<"New MaxScore: "<<maxScore<<endl;
                ptr_command.reset(new UseSkill(testUseSkill));
              }
        }
      }
    }
    // cout<<"End UseSkill scoring"<<endl;

    if(ptr_command->validate(engine.getTurn())){
      if (ptr_command->commandType==Attackcmd){
        if(showText) cout << "->attack instruction added " << endl;
      }
      else if (ptr_command->commandType==Movecmd){
        if(showText) cout << "->move instruction added " << endl;
      }
      else if (ptr_command->commandType==Defendcmd){
        if(showText) cout << "->defend instruction added " << endl;
      }
      else if (ptr_command->commandType==UseSkillcmd){
        if(showText) cout << "->useskill instruction added " << endl;
      }
      else if (ptr_command->commandType==UseObjectcmd){
        if(showText) cout << "->useobject instruction added " << endl;
      }
      if (not(ptr_command->commandType==Movecmd)){
        hNM=true;
        k++;
      }
      else{
        hNM=false;
      }
      engine.addCommand(move(ptr_command));
    }
    else{
      EndTurn endturntest(teamNumber);
      if(endturntest.validate(engine.getTurn())){
        unique_ptr<Command> ptr_endturntest (new EndTurn (endturntest));
        engine.addCommand(move(ptr_endturntest));
        k=engine.getTurn().getTeams()[teamNumber]->getListCharacter().size();
        if(showText) cout << "->endturn instruction added " << endl;
      }
    }
  }
}
