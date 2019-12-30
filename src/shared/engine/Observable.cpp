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
	cout << "notif updating ";
	for(auto observer : observers){
		observer->engineUpdating();
	}
}

void const engine::Observable::notifyUpdated(){
	cout << "notif updated ";
	for(auto observer : observers){
		observer->engineUpdated();
	}
}
