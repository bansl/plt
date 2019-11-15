#include "../ai.h"
#include "../engine.h"
#include <random>
#include <iostream>
using namespace std;
using namespace ai;

void RandomAI::randomCommandList(engine::Engine& engine, int teamNumber){
	for(int k=0;k<engine.getTurn().getTeams()[teamNumber]->getListCharacter().size();k++){  
		std::random_device dev;
  		std::mt19937 rng(dev());
  		std::uniform_int_distribution<std::mt19937::result_type> distribution(1,4);
  		// int i=distribution(rng);
	}
	
}

void RandomAI::runAI(){
	randomCommandList(engine,idAI);
}
