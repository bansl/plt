#include "../ai.h"
#include "../engine.h"
#include <iostream>
#include <queue>
using namespace std;
using namespace ai;
using namespace engine;
using namespace state;


void DeepAI::runAI(){
	deepCommandList(engine.getCurrentPlayerID());
  if(engine.threaded==true) engine.notifyUpdating();
}

DeepAI::DeepAI(engine::Engine& engine):engine(engine){

}

int DeepAI::minMax(int teamNumber,int numberNextCharacter, bool hasNotMoved){
	engine.showStatus=false;
	HeuristicAI haitest(engine);
  sf::RenderWindow wt;
	sf::RenderWindow& windowtest=wt;
  std::vector<sf::View> views;
  sf::View view1(sf::Vector2f(0, 300), sf::Vector2f(800, 560));
  view1.zoom(1.4f);
  sf::View view2(sf::Vector2f(400, 300), sf::Vector2f(800, 600));
  view1.setViewport(sf::FloatRect(0, 0, 1, 0.8f));
  sf::View viewInfobanner (sf::Vector2f(-800, -800), sf::Vector2f(800, 140));
  viewInfobanner.setViewport(sf::FloatRect(0, 0.8f, 1, 1));
  views.push_back(view1);
  views.push_back(view2);
  views.push_back(viewInfobanner);
	haitest.showText=false;
	int tempTurnNumber=engine.getTurn().getTurn();
	engine.updateDisplay(wt,views);
	haitest.runAI(numberNextCharacter,hasNotMoved);
	engine.updateDisplay(wt,views);
	engine.updateDisplay(wt,views);
  haitest.runAI();
	engine.updateDisplay(wt,views);
	engine.updateDisplay(wt,views);
	haitest.runAI();
	engine.updateDisplay(wt,views);
	engine.updateDisplay(wt,views);
	haitest.runAI();
	engine.updateDisplay(wt,views);
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
		engine.revertTurn(windowtest,views);
	}
	engine.showStatus=true;
	restoreCommandList();
	return score;
}

void DeepAI::deepCommandList(int teamNumber){
  cout<<"Deep AI: Team Number "<<teamNumber<<" is playing"<<endl;
  int k=0;
  bool hasNotMoved=true;

  while(k<(int)engine.getTurn().getTeams()[teamNumber]->getListCharacter().size()){
    for (size_t k = 0; k < 5; k++) InstructionAdded[k]=false;
    if(hasNotMoved){
      cout<<"Character Number "<<k<<" is playing"<<endl;
    }
    int maxScore=-500;
    UseSkill commandnull(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],500,0);
    unique_ptr<Command> ptr_command (new UseSkill(commandnull));

    cout<<"Start Attack scoring"<<endl;
    for(int t=0;t<(int)engine.getTurn().getTeams().size();t++){
      if(t!=teamNumber){
        for(int i=0;i<(int)engine.getTurn().getTeams()[t]->getListCharacter().size();i++){
          Attack attacktest(*engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k],*engine.getTurn().getTeams()[t]->getListCharacter()[i]);
          if(attacktest.validate(engine.getTurn())){
            engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->setStatus(Available);
            unique_ptr<Command> ptr_testcommand (new Attack(attacktest));
            engine.addCommand(move(ptr_testcommand));
            int minMaxScore=minMax(teamNumber,k+1,true);
            if(maxScore<minMaxScore){
              maxScore=minMaxScore;
              cout<<"New MaxScore: "<<maxScore<<endl;
              ptr_command.reset(new Attack(attacktest));
							updateQueue();
              Attackqueue.push(attacktest);
              InstructionAdded[0]=true;
            }
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
			int xmin=max((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getX()-5,0);
			int xmax=min((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getX()+5,(int)engine.getTurn().getMap().size());
			int ymin=max((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getY()-5,0);
			int ymax=min((int)engine.getTurn().getTeams()[teamNumber]->getListCharacter()[k]->getPosition().getY()+5,(int)engine.getTurn().getMap().size());
        for(int x=xmin;x<xmax;x++){
          for(int y=ymin;y<ymax;y++){
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
							//int minMaxScore=minMax(teamNumber,k,false);
              if(maxScore<minMaxScore){
                maxScore=minMaxScore;
                cout<<"New MaxScore: "<<maxScore<<endl;
                ptr_command.reset(new Move (movetest));
                updateQueue();
                Movequeue.push(movetest);
                InstructionAdded[1]=true;
              }
							// cout<<"Move in the buffer "<<engine.getTurn().getBuffer().size()<<endl;
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
      int minMaxScore=minMax(teamNumber,k+1,true);
      if(maxScore<minMaxScore){
        maxScore=minMaxScore;
        cout<<"New MaxScore: "<<maxScore<<endl;
        ptr_command.reset(new Defend (deftest));
        updateQueue();
        Defendqueue.push(deftest);
        InstructionAdded[2]=true;
      }
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
          int minMaxScore=minMax(teamNumber,k+1,true);
          if(maxScore<minMaxScore){
            maxScore=minMaxScore;
            cout<<"New MaxScore: "<<maxScore<<endl;
  				  ptr_command.reset(new UseObject(testUseObject));
            updateQueue();
            UseObjectqueue.push(testUseObject);
            InstructionAdded[3]=true;
          }
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
                  int minMaxScore=minMax(teamNumber,k+1,true);
                  if(maxScore<minMaxScore){
                    maxScore=minMaxScore;
                    cout<<"New MaxScore: "<<maxScore<<endl;
                    ptr_command.reset(new UseSkill(testUseSkill));
                    updateQueue();
                    UseSkillqueue.push(testUseSkill);
                    InstructionAdded[4]=true;
                  }
	            }
	          }
	        }
	      }
	    }
			cout<<"End UseSkill scoring"<<endl;

    if(ptr_command->validate(engine.getTurn())){
      if (ptr_command->commandType==Attackcmd){
				cout << "->attack instruction added " << endl;
				CommandtypeList.push_back(Attackcmd);
      }
      else if (ptr_command->commandType==Movecmd){
        cout << "->move instruction added " << endl;
				CommandtypeList.push_back(Movecmd);
      }
      else if (ptr_command->commandType==Defendcmd){
        cout << "->defend instruction added " << endl;
				CommandtypeList.push_back(Defendcmd);
      }
      else if (ptr_command->commandType==UseSkillcmd){
        cout << "->useskill instruction added " << endl;
				CommandtypeList.push_back(UseSkillcmd);
      }
      else if (ptr_command->commandType==UseObjectcmd){
        cout << "->useobject instruction added " << endl;
				CommandtypeList.push_back(UseObjectcmd);
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
