#include "../server.h"
#include <memory>
#include <iostream>

using namespace server;
using namespace std;

CommandService::CommandService (Game& game) : Service("/command"), game(game) {

}

HttpStatus CommandService::get (Json::Value& out, int id) const {
    std::string turnCommands = game.getCommands(id);
    out["turn"] = turnCommands;
    return HttpStatus::OK;
}

HttpStatus CommandService::getall (Json::Value& out) const {
    for (int i = 0; i < (int) game.getCommandsList().size(); i++)
    {
        std::string turnCommands = game.getCommands(i);
        out["turn"+to_string(i)] = turnCommands;
    }


    return HttpStatus::OK;
}


HttpStatus CommandService::put (Json::Value& out, const Json::Value& in) {
    //int turnNumber=(int)game.getCommandsList().size();
    if (in.isMember("turn")) {
        game.addCommands(in["turn"].asString());
        const std::string yes="Yes";
        out["Done"]=yes;
    }
    else{
      const std::string no="No";
      out["Done"]=no;
    }
    return HttpStatus::OK;
}


bool CommandService::isVersion(){
	return false;
}

Game& CommandService::getGame(){
	Game& ref=game;
	return ref;
}
