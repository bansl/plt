#include "../server.h"
#include <memory>

using namespace server;
using namespace std;

Game::Game():playerNb(0){   
}
std::vector<std::unique_ptr<Player>>& Game::getPlayersList(){
	std::vector<std::unique_ptr<Player>>& ref=players;
	return ref;
}

const Player* Game::getPlayer (int id) const {
    for (size_t i = 0; i < players.size(); i++)
    {
        if(players[i]->id==id) return players[i].get();
    }    
    return nullptr;
}

int Game::addPlayer (std::unique_ptr<Player> player) {
    int id = playerNb++;
    players.push_back(move(player));
    return id;
}

void Game::setPlayer (int id, std::unique_ptr<Player> player) {
    players[id] = std::move(player);
    if (id > playerNb) {
        playerNb = id;
    }
}

void Game::removePlayer (int id) {
    for (size_t i = 0; i < players.size(); i++)
    {
        if(players[i]->id==id) players.erase(players.begin() + i);
    }   
}