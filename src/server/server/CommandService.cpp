#include "../server.h"
#include <memory>
#include <iostream>

using namespace server;
using namespace std;

CommandService::CommandService (Game& game) : Service("/command"), game(game) {

}

HttpStatus CommandService::get (Json::Value& out, int id) const {
    std::string turnCommands = game.getCommands(id);
    if (turnCommands!="None")
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid commands for turn");
    out["turn"+to_string(id)] = turnCommands;
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


HttpStatus CommandService::post (const Json::Value& in, int id) {
    //int turnNumber=(int)game.getCommandsList().size();
    if (in.isMember("turn"+to_string(id))) {
        game.addCommands(in["turn"+to_string(id)].asString());
    }
    return HttpStatus::NO_CONTENT;
}


bool CommandService::isVersion(){
	return false;
}

Game& CommandService::getGame(){
	Game& ref=game;
	return ref;
}
