#include <iostream>
#include <cstring>
#include <state.h>
#include "render.h"
#include <unistd.h>
#include <chrono>

using namespace std;
using namespace state;
using namespace render;
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
            int rotation=0;
            cout<<"Affichage d'un Etat"<<endl<<endl;

            // === Init turn ===
            Turn testTurn;
            testTurn.initMap(6,6);
            testTurn.initTeams();
            testTurn.getTeams()[0]->addCharacter();
            testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(1,4);
            testTurn.getTeams()[0]->addCharacter();
            testTurn.getTeams()[0]->getListCharacter()[1]->getPosition().setPos(1,3);
            // === Display Turn ===
            TurnDisplay layer(testTurn);
            cout << "left click to rotate map anti-clockwise " << endl;
            cout << "right click to rotate map clockwise " << endl<< endl;
            // cout << "check map : " << testTurn.getMap().size() << endl;
            // cout << "check map : " << testTurn.getMap()[0].size() << endl;
            int screensizeWidth=testTurn.getMap().size()*layer.getTilesets()[0]->getYsize();
            int screensizeHeight=testTurn.getMap()[0].size()*layer.getTilesets()[0]->getYsize();
            sf::RenderWindow window(sf::VideoMode(  screensizeWidth,
                                                    (screensizeHeight)),
                                                    "Render");
            layer.initRender(0);
            // cout << "check chara: " << testTurn.getTeams()[0]->getListCharacter().size() << endl;
            // cout << "check map tile 0,0: " << testTurn.getMap()[0][0].getTile() << endl;
            // cout << "check map tile 0,1: " << testTurn.getMap()[0][1].getTile() << endl;
            // cout << "check map tile 1,0: " << testTurn.getMap()[1][0].getTile() << endl;

            int k=0,characterheight;
            milliseconds last_ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            last_ms+=(milliseconds) 60;
            window.setFramerateLimit(60);
            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                }
                window.clear();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    // left mouse button is pressed: rotate map
                    rotation=(rotation+1)%4;
                    layer.initRender(rotation);
                    // cout << "check map tile 0,0: " << testTurn.getMap()[0][0].getTile() << endl;
                    // cout << "check map tile 0,1: " << testTurn.getMap()[0][1].getTile() << endl;
                    // cout << "check map tile 1,0: " << testTurn.getMap()[1][0].getTile() << endl;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                    // right mouse button is pressed: rotate map to other side
                    rotation=(rotation+3)%4;
                    layer.initRender(rotation);
                    // cout << "check map tile 0,0: " << testTurn.getMap()[0][0].getTile() << endl;
                    // cout << "check map tile 0,1: " << testTurn.getMap()[0][1].getTile() << endl;
                    // cout << "check map tile 1,0: " << testTurn.getMap()[1][0].getTile() << endl;
                }
                // Draw map(roofs and walls)
                int temp;
                for (size_t i = 0; i < layer.getDrawmaps().size(); i++)
                {
                    window.draw(*layer.getDrawmaps()[i]);
                        int characterposX=testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().getX();
                        int characterposY=testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().getY();
                        for (int q=0; q<rotation; q++){
                            temp=characterposX;
                            characterposX=testTurn.getMap().size()-characterposY-1;
                            characterposY=temp;
                        }
                        characterheight=testTurn.getMap()[testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().getX()][testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().getY()].getHeight();
                        if((characterposX*testTurn.getMap().size()+characterposY)*6+2*(characterheight+1)== i){ window.draw(*layer.getDrawchars()[0][k]);}
                    
                }

cout << "check drawmaps: " << layer.getDrawmaps().size() << endl;

                if((duration_cast< milliseconds >(system_clock::now().time_since_epoch())) >= (last_ms)){
                    k=(k+1)%6;
                    last_ms=duration_cast< milliseconds >(system_clock::now().time_since_epoch()) + (milliseconds) 60;

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
