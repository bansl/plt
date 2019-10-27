#include <engine.h>
#include <render.h>
#include <state.h>

#include <iostream>

using namespace state;
using namespace engine;
using namespace render;
using namespace std;


state::Turn& Engine::getTurn (){
	state::Turn& myturn=turn;
	return myturn;
}
