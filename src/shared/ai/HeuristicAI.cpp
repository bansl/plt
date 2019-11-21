#include "../ai.h"
#include "../engine.h"
#include <random>
#include <iostream>
using namespace std;
using namespace ai;
using namespace engine;
using namespace state;

void HeuristicAI::heuristicCommandList(engine::Engine& engine, int teamNumber){

}

int HeuristicAI::computeScore(engine::Command& command){
    if (command.commandType==Attackcmd)
    {
        // command.
    }
    
    return 0;
}

void HeuristicAI::runAI(){
	heuristicCommandList(engine,engine.getCurrentPlayerID());
}

HeuristicAI::HeuristicAI(engine::Engine& engine):engine(engine){

}
