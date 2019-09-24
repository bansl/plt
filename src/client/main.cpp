#include <iostream>
#include <cstring>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{   
    Exemple exemple;
    exemple.setX(53);
    if( std::strcmp( argv[1], "hello") == 0 ){
        cout << "Bonjour le monde!" << endl;    
    }
    else{
        cout << "Type hello to get welcome message." << endl;
    }
    return 0;
}
