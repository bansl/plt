#include "../ai.h"
#include "../engine.h"
#include <iostream>
using namespace std;
using namespace ai;
using namespace engine;
using namespace state;


void DeepAI::runAI(){
	deepCommandList(engine,engine.getCurrentPlayerID());
}

DeepAI::DeepAI(engine::Engine& engine):engine(engine){

}

int DeepAI::minMax(engine::Engine& engine,int teamNumber,int numberNextCharacter, bool hasNotMoved){
	HeuristicAI haitest(engine);
  sf::RenderWindow wt;
	sf::RenderWindow& windowtest=wt;
	haitest.runAI(numberNextCharacter,hasNotMoved);
	engine.updateDisplay(wt);
  haitest.runAI();
	engine.updateDisplay(wt);
	haitest.runAI();
	engine.updateDisplay(wt);
	haitest.runAI();
	engine.updateDisplay(wt);
	int score=0;
  for(int i=0;i<(int)engine.getTurn().getTeams().size();i++){
    for(int j=0;j<(int)engine.getTurn().getTeams()[i]->getListCharacter().size();j++){
      if(i==teamNumber){
        score+=-(engine.getTurn().getTeams()[i]->getListCharacter()[j]->getMaxHP()-engine.getTurn().getTeams()[i]->getListCharacter()[j]->getCurrentHP());
      }
      else{
        score+=(engine.getTurn().getTeams()[i]->getListCharacter()[j]->getMaxHP()-engine.getTurn().getTeams()[i]->getListCharacter()[j]->getCurrentHP());
      }
    }
  }
  engine.revertTurn(windowtest);
  engine.revertTurn(windowtest);
  engine.revertTurn(windowtest);
	engine.revertTurn(windowtest);
  return score;
}

void DeepAI::deepCommandList(Engine& engine,int teamNumber){
  cout<<"Team Number "<<teamNumber<<" is playing"<<endl;
  int k=0;
  bool hasNotMoved=true;
	std::vector<std::unique_ptr<Command>> commandsTemp;
  while(k<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter().size()){
    if(hasNotMoved){
      cout<<"Character Number "<<k<<" is playing"<<endl;
    }
    int maxScore=-500;
    UseSkill commandnull(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],500,0);
    unique_ptr<Command> ptr_command (new UseSkill(commandnull));

    // cout<<"Start Attack scoring"<<endl;
    for(int t=0;t<(int)engine.getTurn().getTeams().size();t++){
      if(t!=teamNumber){
        for(int i=0;i<(int)engine.getTurn().getTeams()[t]->getListCharacter().size();i++){
          Attack attacktest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[t]->getListCharacter()[i]);
          if(attacktest.validate(engine.getTurn())){
            engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
            unique_ptr<Command> ptr_testcommand (new Attack(attacktest));
            engine.addCommand(move(ptr_testcommand));
            int minMaxScore=minMax(engine,teamNumber,k+1,true);
            if(maxScore<minMaxScore){
              maxScore=minMaxScore;
              // cout<<"New MaxScore: "<<maxScore<<endl;
              ptr_command.reset(new Attack(attacktest));
            }

          }
        }
      }
    }
    // cout<<"End Attack scoring"<<endl;

    if(hasNotMoved){
      int tempX=engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getX();
      int tempY=engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getY();
        for(int x=max((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getX()-5,0);x<min((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getX()+5,(int)engine.getTurn().getMap().size());x++){
          for(int y=max(0,(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getY()-5);y<min((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getY()+5,(int)engine.getTurn().getMap().size());y++){
            Position dest;
            dest.setPos(x,y);
            Move movetest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k], dest);
            // cout<<"Position: x : "<<x<<";y :"<<y<<endl;
            if(movetest.validate(engine.getTurn())){
              engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
              engine.getTurn().getBuffer().pop_back();
              engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().setPos(tempX,tempY);
              unique_ptr<Command> ptr_testcommand (new Move(movetest));
              engine.addCommand(move(ptr_testcommand));
              int minMaxScore=minMax(engine,teamNumber,k,false);
              if(maxScore<minMaxScore){
                maxScore=minMaxScore;
                // cout<<"New MaxScore: "<<maxScore<<endl;
                ptr_command.reset(new Move (movetest));
              }

            }
          }
        }
      }

    // cout<<"Start Defend scoring"<<endl;
    Defend deftest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]);
    if(deftest.validate(engine.getTurn())){
      engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
      unique_ptr<Command> ptr_testcommand (new Defend(deftest));
      engine.addCommand(move(ptr_testcommand));
      int minMaxScore=minMax(engine,teamNumber,k+1,true);
      if(maxScore<minMaxScore){
        maxScore=minMaxScore;
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
          unique_ptr<Command> ptr_testcommand (new UseObject(testUseObject));
          engine.addCommand(move(ptr_testcommand));
          int minMaxScore=minMax(engine,teamNumber,k+1,true);
          if(maxScore<minMaxScore){
            maxScore=minMaxScore;
            // cout<<"New MaxScore: "<<maxScore<<endl;
  				  ptr_command.reset(new UseObject(testUseObject));
          }

        }
      }
    }
    // cout<<"End UseObject scoring"<<endl;

    // cout<<"Start UseSkill scoring"<<endl;
    for(int t=0;t<(int)engine.getTurn().getTeams().size();t++){
      if(t!=teamNumber){
        for(int p=0;p<(int)engine.getTurn().getTeams()[t]->getListCharacter().size();p++){
          for(int s=0;s<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getSkillList().size();s++){
            UseSkill testUseSkill(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[t]->getListCharacter()[p],s,0);
    			  if(testUseSkill.validate(engine.getTurn())){
    				      engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
                  unique_ptr<Command> ptr_testcommand (new UseSkill(testUseSkill));
                  engine.addCommand(move(ptr_testcommand));
                  int minMaxScore=minMax(engine,teamNumber,k+1,true);
                  if(maxScore<minMaxScore){
                    maxScore=minMaxScore;
                    // cout<<"New MaxScore: "<<maxScore<<endl;
                    ptr_command.reset(new UseSkill(testUseSkill));
                  }

	            }
	          }
	        }
	      }
	    }
    // cout<<"End UseSkill scoring"<<endl;

    if(ptr_command->validate(engine.getTurn())){
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
      if (not(ptr_command->commandType==Movecmd)){
        hasNotMoved=true;
        k++;
      }
      else{
        hasNotMoved=false;
      }
			commandsTemp.push_back(move(ptr_command));
			for (int i=0;i<(int)commandsTemp.size();i++){
	      engine.addCommand(move(commandsTemp[i]));
			}
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
