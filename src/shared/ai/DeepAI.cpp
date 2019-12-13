#include "../ai.h"
#include "../engine.h"
#include <iostream>
#include <queue>
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
	engine.showStatus=false;
	HeuristicAI haitest(engine);
  sf::RenderWindow wt;
	sf::RenderWindow& windowtest=wt;
	haitest.showText=false;
	int tempTurnNumber=engine.getTurn().getTurn();
	engine.updateDisplay(wt);
	haitest.runAI(numberNextCharacter,hasNotMoved);
	engine.updateDisplay(wt);
	engine.updateDisplay(wt);
  haitest.runAI();
	engine.updateDisplay(wt);
	engine.updateDisplay(wt);
	haitest.runAI();
	engine.updateDisplay(wt);
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
	int tempEndTurn=engine.getTurn().getTurn();
	for(int i=tempTurnNumber;i<tempEndTurn;i++){
		engine.revertTurn(windowtest);
	}
	engine.showStatus=true;
	return score;
}

void DeepAI::deepCommandList(Engine& engine,int teamNumber){
  cout<<"DeepAi: Team Number "<<teamNumber<<" is playing"<<endl;
  int k=0;
  bool hasNotMoved=true;

  std::vector<CommandList> CommandtypeTemp;
  while(k<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter().size()){
    for (size_t k = 0; k < 5; k++) InstructionAdded[k]=false;
    if(hasNotMoved){
      cout<<"Character Number "<<k<<" is playing"<<endl;
    }
    int maxScore=-500;
    UseSkill commandnull(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],500,0);
    unique_ptr<Command> ptr_command (new UseSkill(commandnull));
    CommandtypeTemp.push_back({});
    

    cout<<"Start Attack scoring"<<endl;
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
              Attackqueue.push(attacktest);
              InstructionAdded[0]=true;
              CommandtypeTemp.back()=Attackcmd;

            }
						restoreCommandList();
          }
        }
      }
    }
    cout<<"End Attack scoring"<<endl;

		cout<<"Start Move scoring"<<endl;
    if(hasNotMoved){
			HeuristicAI hai(engine);
      int tempX=engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getX();
      int tempY=engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getY();
        for(int x=max((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getX()-5,0);x<min((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getX()+5,(int)engine.getTurn().getMap().size());x+=2){
          for(int y=max(0,(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getY()-5);y<min((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getY()+5,(int)engine.getTurn().getMap().size());y+=2){
            // cout<< "x: " << x << ", y: " << y << endl;
            Position dest;
            dest.setPos(x,y);
            Move movetest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k], dest);
            // cout<<"Position: x : "<<x<<";y :"<<y<<endl;
            if(movetest.validate(engine.getTurn())){
							int minMaxScore=hai.computeScore(movetest);
              engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
              engine.getTurn().getBuffer().pop_back();
              engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().setPos(tempX,tempY);
              unique_ptr<Command> ptr_testcommand (new Move(movetest));
              engine.addCommand(move(ptr_testcommand));
							//int minMaxScore=minMax(engine,teamNumber,k,false);
              if(maxScore<minMaxScore){
                maxScore=minMaxScore;
                // cout<<"New MaxScore: "<<maxScore<<endl;
                ptr_command.reset(new Move (movetest));
                updateQueue();
                Movequeue.push(movetest);
                InstructionAdded[1]=true;
                CommandtypeTemp.back()=Movecmd;
              }
							restoreCommandList();

            }
          }
        }
      }
			cout<<"End Move scoring"<<endl;

    cout<<"Start Defend scoring"<<endl;
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
        updateQueue();
        Defendqueue.push(deftest);
        InstructionAdded[2]=true;
        CommandtypeTemp.back()=Defendcmd;
      }
			restoreCommandList();

    }
    cout<<"End Defend scoring"<<endl;

    cout<<"Start UseObject scoring"<<endl;
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
            updateQueue();
            UseObjectqueue.push(testUseObject);
            InstructionAdded[3]=true;
            CommandtypeTemp.back()=UseObjectcmd;
          }
					restoreCommandList();

        }
      }
    }
    cout<<"End UseObject scoring"<<endl;

    cout<<"Start UseSkill scoring"<<endl;
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
                    updateQueue();
                    UseSkillqueue.push(testUseSkill);
                    InstructionAdded[4]=true;
                    CommandtypeTemp.back()=UseSkillcmd;
                  }
									restoreCommandList();

	            }
	          }
	        }
	      }
	    }
			cout<<"End UseSkill scoring"<<endl;

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
	    engine.addCommand(move(ptr_command));
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


void DeepAI::restoreCommandList(){
for (int i=0;i<(int)CommandtypeList.size();i++){
    unique_ptr<Command> ptr_commandtemp;
    if (CommandtypeList[i]==Attackcmd){
      ptr_commandtemp.reset(new Attack(Attackqueue.front()));
      Attackqueue.push(Attackqueue.front());
      Attackqueue.pop();
    }
    else if (CommandtypeList[i]==Movecmd){
      ptr_commandtemp.reset(new Move(Movequeue.front()));
      Movequeue.push(Movequeue.front());
      Movequeue.pop();
    }
    else if (CommandtypeList[i]==Defendcmd){
      ptr_commandtemp.reset(new Defend(Defendqueue.front()));
      Defendqueue.push(Defendqueue.front());
      Defendqueue.pop();
    }
    else if (CommandtypeList[i]==UseObjectcmd){
      ptr_commandtemp.reset(new UseObject(UseObjectqueue.front()));
      UseObjectqueue.push(UseObjectqueue.front());
      UseObjectqueue.pop();
    }
    else if (CommandtypeList[i]==UseSkillcmd){
      ptr_commandtemp.reset(new UseSkill(UseSkillqueue.front()));
      UseSkillqueue.push(UseSkillqueue.front());
      UseSkillqueue.pop();
    }
    ptr_commandtemp->validate(engine.getTurn());
    engine.addCommand(move(ptr_commandtemp));
  }
}

void DeepAI::updateQueue(){
  if (InstructionAdded[0]) {
    Attackqueue.pop();
    InstructionAdded[0]=false;
  }
  if (InstructionAdded[1]) {
    Movequeue.pop();
    InstructionAdded[1]=false;
  }
  if (InstructionAdded[2]) {
    Defendqueue.pop();
    InstructionAdded[2]=false;
  }
  if (InstructionAdded[3]) {
    UseObjectqueue.pop();
    InstructionAdded[3]=false;
  }
  if (InstructionAdded[4]) {
    UseSkillqueue.pop();
    InstructionAdded[4]=false;
  }
}