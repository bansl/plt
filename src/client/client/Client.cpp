#include "engine.h"
#include "render.h"
#include "state.h"
#include "client.h"
#include "ai.h"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include<pthread.h>
#include <json/json.h>
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

void Client::run (bool human){
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
	usleep(100);
    engine.registerObserver(ptr_layer);

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
							else {
								if (!human)	bots->runAI();
								else
								{
									while(window.isOpen()){
										if(engine.getTurn().getIsSkipped()) break;
										if((duration_cast<milliseconds>(system_clock::now().time_since_epoch()))>=(last_ms)&&resume){
											layer.display(window,k, views);
											k=(k+1)%4;
											last_ms=duration_cast< milliseconds >(system_clock::now().time_since_epoch()) + (milliseconds) 60;
										}

										while (window.pollEvent(event)){
											if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
												engine.getTurn().rotation=(engine.getTurn().rotation+1)%4;
												layer.initRender(engine.getTurn(),fullRender);
											}
											if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
												engine.getTurn().rotation=(engine.getTurn().rotation+3)%4;
												layer.initRender(engine.getTurn(),fullRender);
											}
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
								}

							}
							engine.notifyUpdating();
							while (updating){};
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
			k=(k+1)%4;
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

void Client::run (int playerID){

	sf::Event event;
	TurnDisplay layer(engine.getTurn());
	cout << "Render begin." << endl;
	layer.initRender(engine.getTurn(), fullRender);

	TurnDisplay* ptr_layer=&layer;
	engine.getTurn().registerObserver(ptr_layer);
	// Engine* ptr_engine=&engine;
	usleep(100);
    engine.registerObserver(ptr_layer);

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
	bool sendupdate=true;
	sf::Http http("http://192.168.56.103/", 8080); //192.168.56.103

	while(window.isOpen()){
		 layer.display(window,1, views);
		 if(!updating){
			cout << "finished updating"<< endl;
			if(engine.turnCheckIn() ){
							engine.notifyUpdating();
							while (updating);
							if(engine.getTurn().getTurn()%2==playerID%2){
								bots->runAI();
								sendupdate=false;
							}
							//else bots->runAI();
							if((engine.getTurn().getTurn()%2!=playerID%2) && (sendupdate==false)){
								cout<<"Starting posting last turn commands"<<endl;
								sf::Http::Request requestcmd;
								requestcmd.setMethod(sf::Http::Request::Post);
								requestcmd.setUri("/command");
								cout<<"body begin"<<endl;
								string dataTurn=engine.seedCommandsPlayer(engine.getTurn().getTurn()-1);
								cout<<"data Turn"<<endl;
								requestcmd.setBody("{\"req\" : \"POST\", \"turn\": \""+dataTurn+"\"}");
								// cout<<"{\"req\" : \"POST\", \"turn\": \""+dataTurn+"\"}"<<endl;
								Json::Reader jsonReader;
								Json::Value rep;
								sf::Http::Response response = http.sendRequest(requestcmd);
								cout<<"Last turn commands posted"<<endl;
								if (jsonReader.parse(response.getBody(), rep)){
									if(rep["Done"].asString()=="Yes"){
										sendupdate=true;
									}
								}
							}
							if(engine.getCurrentPlayerID()!=playerID%2){
								while(window.isOpen()){
									sf::Http::Request request;
									request.setMethod(sf::Http::Request::Get);
									request.setUri("/command/"+ to_string(engine.getTurn().getTurn()));
									http.sendRequest(request);
									Json::Reader jsonReader;
									Json::Value rep;
									sf::Http::Response response = http.sendRequest(request);
									if (jsonReader.parse(response.getBody(), rep)){
										cout<< "status : "<<response.getStatus()<<endl;
										cout<<"HTTP version : "<<response.getMajorHttpVersion()<< "."
										                         <<response.getMinorHttpVersion()<<endl;
										cout<<"Content-type header :"<<response.getField("Content-Type")<<endl;
										cout<<"body :"<<response.getBody()<<endl;
										if(rep["turn"].asString()!="None"){
											engine.loadCommands(rep["turn"].asString(),engine.getTurn().getTurn(),window,views);
										}
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
									if((duration_cast<milliseconds>(system_clock::now().time_since_epoch()))>=(last_ms)&&resume){
										layer.display(window,k, views);
										k=(k+1)%4;
										last_ms=duration_cast< milliseconds >(system_clock::now().time_since_epoch()) + (milliseconds) 60;
									}
									usleep(1000000);
								}
							}
							engine.notifyUpdating();
							while (updating);

			}
		}
		if((duration_cast<milliseconds>(system_clock::now().time_since_epoch()))>=(last_ms)&&resume){
            layer.display(window,k, views);
			k=(k+1)%4;
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
