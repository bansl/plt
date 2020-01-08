#include "engine.h"
#include "render.h"
#include "state.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace render;
using namespace std;

void const engine::Observable::registerObserver(Observer* o){
	observers.push_back(o);
}

void const engine::Observable::notifyUpdating(){
	for(auto observer : observers){
		observer->engineUpdating();
	}
}

void const engine::Observable::notifyUpdated(){
	for(auto observer : observers){
		observer->engineUpdated();
	}
}

void const engine::Observable::notifySelectCursorMove (engine::Direction direction){
	if (direction==UP){
		for(auto observer : observers){
			observer->moveCursorUp();
		}
	}
	if (direction==DOWN){
		for(auto observer : observers){
			observer->moveCursorDown();
		}
	}
}