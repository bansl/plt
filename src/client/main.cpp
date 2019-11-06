#include <iostream>
#include <cstring>
#include <state.h>
#include "render.h"
#include "../shared/engine.h"

#include <unistd.h>
#include <chrono>

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace std::chrono;

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

int main(int argc,char* argv[])
{
    // Exemple exemple;
    // exemple.setX(53);

    if (argc>1){

        if( std::strcmp( argv[1], "hello") == 0 ){
            cout << "Bonjour le monde!" << endl;
        }


//=====================================================================================================
//
//                                              RENDER TEST
//
//=====================================================================================================

        else if(strcmp(argv[1],"render") == 0){
            int rotation=0;
            cout<<"Turn Display Test"<<endl<<endl;
            cout<<"Controls:"<<endl;
            cout << "-Press Up, Down, Right or Left key to move around the map " << endl;
            cout << "-Press R key to rotate map anti-clockwise " << endl;
            cout << "-Press T key to rotate map clockwise " << endl<< endl;
            // === Init turn ===
            Turn testTurn;
            testTurn.initMap(10,10); //squares only
            testTurn.initTeams();
            testTurn.getTeams()[0]->addCharacter();
            testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(2,5);
            testTurn.getTeams()[0]->addCharacter();
            testTurn.getTeams()[0]->getListCharacter()[1]->getPosition().setPos(2,8);
            // === Display Turn ===
            TurnDisplay layer(testTurn);

            // cout << "check map : " << testTurn.getMap().size() << endl;
            // cout << "check map : " << testTurn.getMap()[0].size() << endl;
            // int screensizeWidth=testTurn.getMap().size()*layer.getTilesets()[0]->getYsize();
            // int screensizeHeight=testTurn.getMap()[0].size()*layer.getTilesets()[0]->getYsize();
            sf::RenderWindow window(sf::VideoMode(  800,
                                                    (600)),
                                                    "Render");
            sf::View view1(sf::Vector2f(350, 300), sf::Vector2f(400, 300));
            sf::View view2(sf::Vector2f(400, 300), sf::Vector2f(800, 600));
            view1.zoom(3.f);
            window.setView(view1);
            cout << "Render begin." << endl;
            layer.initRender(0);
            cout << "Render done." << endl;

            sf::Text message;
            sf::Font font;
            font.loadFromFile("res/COURG___.TTF");
            message.setFont(font);
            message.setColor(sf::Color::White);
            message.setStyle(sf::Text::Bold);
            message.setCharacterSize(25);
            message.setString("PAUSED\n\n Controls: \n -Press Up, Down, Right or Left key \n to move around the map \n -Press R key to rotate map anti-clockwise \n -Press T key to rotate map clockwise");

            int k=0;
            milliseconds last_ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            last_ms+=(milliseconds) 60;
            window.setFramerateLimit(60);
            bool resume=true;
            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                    if (event.type == sf::Event::LostFocus){
                        resume=false;
                        window.setView(view2);
                        window.draw(message);
                        window.display();
                    }
                    if (event.type == sf::Event::GainedFocus){
                        window.setView(view1);
                        resume=true;
                    }
                }
                if((duration_cast< milliseconds >(system_clock::now().time_since_epoch())) >= (last_ms) && resume){
                    window.clear();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                        view1.move(40, 40);
                        window.setView(view1);

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                        view1.move(-40, -40);
                        window.setView(view1);

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                        view1.move(-40, +40);
                        window.setView(view1);

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                        view1.move(+40, -40);
                        window.setView(view1);

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                        // right key is pressed: rotate map
                        rotation=(rotation+1)%4;
                        layer.initRender(rotation);
                        // cout << "check map tile 0,0: " << testTurn.getMap()[0][0].getTile() << endl;
                        // cout << "check map tile 0,1: " << testTurn.getMap()[0][1].getTile() << endl;
                        // cout << "check map tile 1,0: " << testTurn.getMap()[1][0].getTile() << endl;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
                        // left key is pressed: rotate map to other side
                        rotation=(rotation+3)%4;
                        layer.initRender(rotation);
                        // cout << "check map tile 0,0: " << testTurn.getMap()[0][0].getTile() << endl;
                        // cout << "check map tile 0,1: " << testTurn.getMap()[0][1].getTile() << endl;
                        // cout << "check map tile 1,0: " << testTurn.getMap()[1][0].getTile() << endl;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                        Attack testattack(*testTurn.getTeams()[0]->getListCharacter()[0],*testTurn.getTeams()[0]->getListCharacter()[1]);
                        testattack.action(testTurn);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
                        // press `M` to move char 0 to 2,2
                        Position dest;
                        dest.setPos(2,2);
                        Move testmove(*testTurn.getTeams()[0]->getListCharacter()[0],dest);
                        if(testmove.action(testTurn)){
                        testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(2,2);
                        }
                        layer.initRender(rotation);
                    }
                    // Draw map(roofs and walls)
                    size_t j=0;

                    for (size_t i = 0; i < layer.getDrawmaps().size(); i++)
                    {
                        window.draw(*layer.getDrawmaps()[i]);


                        if((i+1)%6==0 && j<layer.getDrawchars().size()){
                            window.draw(*layer.getDrawchars()[j][k]);
                            j++;
                        }

                    }


                        k=(k+1)%6;
                        last_ms=duration_cast< milliseconds >(system_clock::now().time_since_epoch()) + (milliseconds) 60;


                    window.display();
                }
            }
        }

//=====================================================================================================
//
//                                              ENGINE TEST
//
//=====================================================================================================
        else if(strcmp(argv[1],"engine") == 0){
            int rotation=0;
            cout<<"Engine Test"<<endl<<endl;
            cout<<"Controls:"<<endl;
            cout << "-Press E key to launch a turn" << endl;
            cout << "-Press Up, Down, Right or Left key to move around the map " << endl;
            cout << "-Press R key to rotate map anti-clockwise " << endl;
            cout << "-Press T key to rotate map clockwise " << endl<< endl;
            // === Init Turn ===
            Turn testTurn;
            testTurn.initMap(10,10); //squares only
            testTurn.initTeams();
            testTurn.getTeams()[0]->addCharacter();
            testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(2,5);
            testTurn.getTeams()[0]->addCharacter();
            testTurn.getTeams()[0]->getListCharacter()[1]->getPosition().setPos(2,8);
            // === Init Engine ===
            Engine testEngine(testTurn);
            // === Display Turn ===
            TurnDisplay layer(testTurn);

            TurnDisplay* ptr_layer=&layer;
			testEngine.getTurn().registerObserver(ptr_layer);

            sf::RenderWindow window(sf::VideoMode(  800,
                                                    (600)),
                                                    "Engine");
            sf::View view1(sf::Vector2f(350, 300), sf::Vector2f(400, 300));
            sf::View view2(sf::Vector2f(400, 300), sf::Vector2f(800, 600));
            view1.zoom(3.f);
            window.setView(view1);
            cout << "Render begin." << endl;
            layer.initRender(0);
            cout << "Render done." << endl;

            sf::Text message;
            sf::Font font;
            font.loadFromFile("res/COURG___.TTF");
            message.setFont(font);
            message.setColor(sf::Color::White);
            message.setStyle(sf::Text::Bold);
            message.setCharacterSize(25);
            message.setString("PAUSED\n\n Controls: \n -Press Up, Down, Right or Left key \n to move around the map \n -Press R key to rotate map anti-clockwise \n -Press T key to rotate map clockwise");

            int k=0;
            milliseconds last_ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            last_ms+=(milliseconds) 60;
            window.setFramerateLimit(60);
            bool resume=true;
            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                    if ( resume && ((event.type == sf::Event::LostFocus) || (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) ) ){
                        resume=false;
                        window.setView(view2);
                        window.draw(message);
                        window.display();
                        sf::Time t1 = sf::seconds(0.1f);
                        sf::sleep(t1);
                    }
                    if ( !resume && ((event.type == sf::Event::GainedFocus) || (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) ) ){
                        window.clear();
                        window.setView(view1);
                        resume=true;
                        sf::Time t1 = sf::seconds(0.1f);
                        sf::sleep(t1);
                    }
                }
                if((duration_cast< milliseconds >(system_clock::now().time_since_epoch())) >= (last_ms) && resume){
                    
                    window.clear();
                    size_t j=0;

                    for (size_t i = 0; i < layer.getDrawmaps().size(); i++)
                    {
                        window.draw(*layer.getDrawmaps()[i]);


                        if((i+1)%6==0 && j<layer.getDrawchars().size()){
                            window.draw(*layer.getDrawchars()[j][k]);
                            j++;
                        }

                    }
                    k=(k+1)%6;
                    last_ms=duration_cast< milliseconds >(system_clock::now().time_since_epoch()) + (milliseconds) 60;

                    window.display();
                    
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                        view1.move(40, 40), window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                        view1.move(-40, -40), window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                        view1.move(-40, +40), window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                        view1.move(+40, -40),window.setView(view1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                        // right key is pressed: rotate map
                        rotation=(rotation+1)%4;
                        layer.initRender(rotation);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
                        // left key is pressed: rotate map to other side
                        rotation=(rotation+3)%4;
                        layer.initRender(rotation);
                    }
                    //Commands
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                        cout << "initial char pos is: " << testEngine.getTurn().getTeams()[0]->getListCharacter()[0]->getPosition().getX() << "|"<< testEngine.getTurn().getTeams()[0]->getListCharacter()[0]->getPosition().getY() << endl;
                        cout << "begin engine test: " << endl;
                        testEngine.turnCheckIn();
                        cout << "engine turnCheckIn done: " << endl;
                        Position dest;
                        dest.setPos(2,3);
                        Move movetest(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0], dest);
                        if(movetest.validate(testEngine.getTurn())){
                            unique_ptr<Command> ptr_movetest (new Move (movetest));
                            testEngine.addCommand(move(ptr_movetest));
                            cout << "move instruction added: " << endl;
                        }
                        cout << "instructions done: " << endl;
                        testEngine.turnCheckOut(window,rotation);
                        testEngine.getTurn().notifyObservers(testEngine.getTurn(), rotation, window);
                        cout << "engine turnCheckOut done: " << endl;
                        cout << "char pos is: " << testEngine.getTurn().getTeams()[0]->getListCharacter()[0]->getPosition().getX() << "|"<< testEngine.getTurn().getTeams()[0]->getListCharacter()[0]->getPosition().getY() << endl;
                    }
                    
                    k=(k+1)%6;
                    last_ms=duration_cast< milliseconds >(system_clock::now().time_since_epoch()) + (milliseconds) 60;
                    
                }
            }
        }
        else{
            cout << "Type hello to get welcome message." << endl;
        }
    }
    else{
            cout << "Type hello to get welcome message." << endl;
        }
    return 0;
}
