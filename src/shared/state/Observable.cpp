#include "state.h"
#include "engine.h"
#include <iostream>

using namespace state;
using namespace std;

void Observable::registerObserver (IObserver* observer){
	observers.push_back(observer);
}

void Observable::notifyObservers ( Turn& turn, sf::RenderWindow& window, state::RenderType rendertype){
	// cout << "notifyObservers" << endl;
	for(auto observer : observers){
		observer->redraw(turn, window, rendertype);
	}
}
