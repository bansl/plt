#include <iostream>
#include <cstring>
#include <state.h>
#include "render.h"
#include <unistd.h>
#include <ctime>

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
            if (!texture.loadFromFile("res/maptile2x129.png"))
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
            testTurn.initMap(6,6);
            testTurn.initTeams();
            testTurn.getTeams()[0].addCharacter();
            // === Display Turn ===
            TurnDisplay layer(testTurn);
            cout << "check map : " << testTurn.getMap().size() << endl;
            cout << "check map : " << testTurn.getMap()[0].size() << endl;
            int screensizeWidth=testTurn.getMap().size()*layer.getTilesets()[0]->getYsize();
            int screensizeHeight=testTurn.getMap()[0].size()*layer.getTilesets()[0]->getYsize();
            sf::RenderWindow window(sf::VideoMode(  screensizeWidth,
                                                    (screensizeHeight)),
                                                    "Render");
            window.setFramerateLimit(30);
            layer.initRender();
            cout << "check map tile 0,0: " << testTurn.getMap()[0][0].getTile() << endl;
            cout << "check map tile 0,1: " << testTurn.getMap()[0][1].getTile() << endl;
            cout << "check map tile 1,0: " << testTurn.getMap()[1][0].getTile() << endl;
            time_t t_now = time(0);
            tm* now = localtime(&t_now);
            int k=0, last;
            last=now->tm_sec;
            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                }
                window.clear();
                //Draw map(roofs and walls)
                for (size_t i = 0; i < layer.getDrawmaps().size(); i++)
                {
                    window.draw(*layer.getDrawmaps()[i]);
                }
                cout << "check time last: " << last << endl;
                cout << "check time now: " << now->tm_sec << endl;
                t_now = time(0);
                now = localtime(&t_now);
                for (size_t i = 0; i < layer.getDrawchars().size(); i++)
                {
                    window.draw(*layer.getDrawchars()[i][k]);
                    
                }
                
                if((now->tm_sec)>=(1+last)){    
                    k=(k+1)%3;
                    last=now->tm_sec;
                }    
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