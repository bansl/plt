#include <iostream>
#include <cstring>
#include <state.h>
#include "render.h"

using namespace std;
using namespace state;
using namespace render;

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

        else if( std::strcmp( argv[1], "sftest") == 0 ){
            sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

              // Load a sprite to display
            sf::Texture texture;
            if (!texture.loadFromFile("../res/maptiles.png"))
                return EXIT_FAILURE;
            sf::Sprite sprite(texture);
            // run the program as long as the window is open
            while (window.isOpen())
            {
                // check all the window's events that were triggered since the last iteration of the loop
                sf::Event event;
                while (window.pollEvent(event))
                {
                    // "close requested" event: we close the window
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                window.clear();
                window.draw(sprite);
                window.display();
            }

            return 0;

        }

        else if(strcmp(argv[1],"render") == 0){

            cout<<"Affichage d'un Etat"<<endl;

            // === Init turn ===
            Turn testTurn;
            testTurn.initMap();

            // === Display Turn ===
            TurnDisplay layer(testTurn);
            cout << "check map : " << testTurn.getMap().size() << endl;
            cout << "check map : " << testTurn.getMap()[0].size() << endl;
            sf::RenderWindow window(sf::VideoMode(  testTurn.getMap().size()*layer.getTilesets()[0]->getXsize(),
                                                    testTurn.getMap()[0].size()*layer.getTilesets()[0]->getYsize()),
                                                    "Map");
            layer.initRender();

            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                }
                cout << "check drawobjs : " << layer.getDrawobjects().size()<< endl;
                window.clear();
                window.draw(*layer.getDrawobjects()[0]);
            
                window.display();
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