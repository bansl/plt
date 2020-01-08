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

void const engine::Observable::notifyObserver (engine::Engine& engine, sf::Window& window, state::RenderType rendertype, std::vector<sf::View> view){
	// cout << "notifyObservers" << endl;
	for(auto observer : observers){
		observer->redraw(engine, window, rendertype, view);
	}
}
