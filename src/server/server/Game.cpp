#include "../server.h"
#include <memory>
#include <cstdlib>
#include "../../shared/state.h"

using namespace server;
using namespace std;

Game::Game():playerNb(0){
	state::Turn testTurn;
	testTurn.initTurn(10,2,3);
	std::string mapSeed=testTurn.seedMap();
	std::string charSeed=testTurn.seedTeams();
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
    player->id=playerNb;
    int id=playerNb;
    players.push_back(move(player));
    playerNb++;
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

std::string Game::getCommands(int turnNumber){
	if(turnNumber<(int)commandsList.size())	return commandsList[turnNumber-1];
	else return "None";
}

void Game::addCommands(std::string commands){
	commandsList.push_back(commands);
}

std::vector<std::string>& Game::getCommandsList(){
	std::vector<std::string>& addrcommandsList=commandsList;
	return addrcommandsList;
}

std::string Game::getMapSeed(){
	return mapSeed;
}

std::string Game::getCharSeed(){
	return mapSeed;
}
