#include "../server.h"
#include <memory>

using namespace server;
using namespace std;

PlayerService::PlayerService (Game& game) : Service(), game(game) {
    
}

HttpStatus PlayerService::get (Json::Value& out, int id) const {
    const Player* player = game.getPlayer(id);
    if (!player)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid player id");
    out["name"] = player->name;
    out["inlobby"] = player->inlobby;
    return HttpStatus::OK;
}

HttpStatus PlayerService::post (const Json::Value& in, int id) {
    const Player* player = game.getPlayer(id);
    if (!player)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid player id");
    unique_ptr<Player> playermod (new Player(*player));
    if (in.isMember("name")) {
        playermod->name = in["name"].asString();
    }
    if (in.isMember("inlobby")) {
        playermod->inlobby = in["inlobby"].asBool();
    }
    game.setPlayer(id, std::move(playermod));
    return HttpStatus::NO_CONTENT;
}

HttpStatus PlayerService::put (Json::Value& out,const Json::Value& in) {
	if(game.getPlayersList().size()>=2){
		throw ServiceException(HttpStatus::OUT_OF_RESOURCES,"Error Full");
	}
    string name = in["name"].asString();
    bool inlobby = in["inlobby"].asBool();
	Player new_player(name, free);
	std::unique_ptr<Player> ptr_player (new Player(new_player));
	out["id"] = game.addPlayer(move(ptr_player));
    return HttpStatus::CREATED;
}

HttpStatus PlayerService::remove (int id) {
    const Player* player = game.getPlayer(id);
    if (!player)
        throw ServiceException(HttpStatus::NOT_FOUND,"Invalid player id");
    game.removePlayer(id);
    return HttpStatus::NO_CONTENT;
}

bool PlayerService::isVersion(){
	return false;
}

Game& PlayerService::getGame(){
	Game& ref=game;
	return ref;
}

