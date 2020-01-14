#include "../server.h"
#include <memory>
#include <iostream>

using namespace server;
using namespace std;

InitializeService::InitializeService (Game& game) : Service("/initialize"), game(game) {

}

HttpStatus InitializeService::get (Json::Value& out, int id) const {
    std::string mapseed = game.getMapSeed();
    std::string charseed = game.getCharSeed();
    cout << "Seed map Gen"<< mapseed;
    cout << "Seed char Gen"<< charseed;
    out["mapseed"] = mapseed;
    out["charseed"]= charseed;
    return HttpStatus::OK;
}


Game& InitializeService::getGame(){
	Game& ref=game;
	return ref;
}
