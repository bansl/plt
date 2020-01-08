#include "engine.h"
#include "render.h"
#include "state.h"
#include "client.h"
#include "ai.h"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <thread>
#include<pthread.h>
using namespace state;
using namespace engine;
using namespace render;
using namespace std;
using namespace client;
using namespace ai;
using namespace std::chrono;

bool v1=false;
bool v2=true;
bool updating=false;
void thread_engine(void* ptr,void* ptrwind, void* ptrviews){
	Engine* ptr_engine=(Engine*)ptr;
	sf::RenderWindow* ptrwindow=(sf::RenderWindow*)ptrwind;
	std::vector<sf::View>* ptr_views=(std::vector<sf::View>*)ptrviews;
	while(v2){
		usleep(1000);
		if(v1){
			ptr_engine->updateDisplay(*ptrwindow,*ptr_views);
			v1=false;
		}
	}

}

Client::Client (sf::RenderWindow& window, std::vector<sf::View> views, state::Turn& turn, bool isloading):views(views), engine(turn), window(window){
	engine.threaded = true;
	loading=isloading;
	if(!loading) engine.getTurn().initTurn(10,2,2);
	bots=new HeuristicAI(engine);
	engine.registerObserver(this);

}

void Client::engineUpdated (){
	updating=false;

}

void Client::engineUpdating (){
	updating=true;
	v1=true;
	usleep(150000);
}
void Client::moveCursorDown(){}

void Client::moveCursorUp(){}

void Client::run (){
	if(loading){
		engine.loadGame(window,views);
		loading=false;
	}
	sf::Event event;
	TurnDisplay layer(engine.getTurn());
	cout << "Render begin." << endl;
	layer.initRender(engine.getTurn(), fullRender);

	TurnDisplay* ptr_layer=&layer;
	engine.getTurn().registerObserver(ptr_layer);
	// Engine* ptr_engine=&engine;

	layer.initWindowRender(infobanner);
	cout << "Render done." << endl;

	sf::Text message;
	sf::Font font;
	font.loadFromFile("res/COURG___.TTF");
	message.setFont(font);
	message.setColor(sf::Color::White);
	message.setStyle(sf::Text::Bold);
	message.setCharacterSize(25);
	message.setString("PAUSED\n\n Controls: \n -Press P key to Pause \n -Press Up, Down, Right or Left key \n   to move around the map \n -Press R key to rotate map anti-clockwise \n -Press T key to rotate map clockwise");

	int k=0;
	milliseconds last_ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	milliseconds last_time_ai_run = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	last_ms+=(milliseconds) 60;
	bool resume=true;
	std::thread th(thread_engine, &engine, &window, &views);

	while(window.isOpen()){
		 layer.display(window,1, views);
		 if(!updating){
			cout << "finished updating"<< endl;
			if(engine.turnCheckIn() ){
							engine.notifyUpdating();
							while (updating);
							if(engine.getTurn().getTurn()%2==0) bots->runAI();
							else bots->runAI();
							engine.notifyUpdating();
							while (updating);
							if(test_register && (engine.getTurn().getTurn()==3)) {
								cout << "Register start." << endl;
								engine.registerGame();
								cout << "Register done." << endl;
								test_register=false;
							}
							
			}
		}
		if((duration_cast<milliseconds>(system_clock::now().time_since_epoch()))>=(last_ms)&&resume){
            layer.display(window,k, views);
			k=(k+1)%6;
			last_ms=duration_cast< milliseconds >(system_clock::now().time_since_epoch()) + (milliseconds) 60;
		}

		while (window.pollEvent(event)){
			if (event.type==sf::Event::KeyPressed){
							engine.userInteraction(event, window, views);
			}
			if (event.type == sf::Event::Closed){
				window.close();
				cout << "====WINDOW EXITED====" << endl;
				break;
			}
		}
	}
	v2=false;
	th.join();
}
