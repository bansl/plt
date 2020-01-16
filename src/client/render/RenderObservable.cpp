#include "engine.h"
#include "render.h"
#include "state.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace render;
using namespace std;

void const render::RenderObservable::registerObserver(RenderObserver* o){
	observers.push_back(o);
}

void const render::RenderObservable::notifyNextAction(){
	for(auto observer : observers){
		observer->nextAction();
	}
}