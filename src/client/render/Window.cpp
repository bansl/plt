#include "../render.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Graphics/Image.hpp>


using namespace std;
using namespace render;
using namespace state;

bool Window::renderWindow (render::WindowType windowType, render::TileSet tileset, int tileDims, state::Turn& turn){
    if (windowType==infobanner)
    {
        if (!texture.loadFromFile(tileset.getImagePath()[0])){
          std::vector<std::string> imagePath;
          imagePath.push_back("../../../res/maptile2x129.png");
          imagePath.push_back("../../../res/char1.png");
          imagePath.push_back("../../../res/char2.png");
          imagePath.push_back("../../../res/cursor.png");
          imagePath.push_back("../../../res/windowsprite.png");
          tileset.setImagePath(imagePath);
          if (!texture.loadFromFile(tileset.getImagePath()[0])){
            return false;
          }
	    }
        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(8);

        for (size_t i = 0; i < 1; i++)
        {
            sf::Vertex* quad = &vertexarray[4*i];

            // vextex pos
            quad[0].position = sf::Vector2f(0    , 0   );
            quad[1].position = sf::Vector2f(800  , 0   );
            quad[2].position = sf::Vector2f(800  , 22 );
            quad[3].position = sf::Vector2f(0    , 22 );

            //texture
            quad[0].texCoords = sf::Vector2f(0+i*tileDims        , 0           );
            quad[1].texCoords = sf::Vector2f(tileDims+i*tileDims , 0           );
            quad[2].texCoords = sf::Vector2f(tileDims+i*tileDims , tileDims );
            quad[3].texCoords = sf::Vector2f(0+i*tileDims        , tileDims );
        }
        
        sf::Font font;
        font.loadFromFile("res/COURG___.TTF");
        message.setFont(font);
        message.setColor(sf::Color::White);
        message.setStyle(sf::Text::Bold);
        message.setCharacterSize(10);
        message.setString("Tile Type:");
          
        

        return true;
    }
    else if (windowType==actionselect)
    {
        /* code */
    }
    else
    {
        /* code */
    }
    return false;    
}

// bool Window::renderCursor (){

// }
void Window::moveCursorUp (){
    if (selectpos>=0) selectpos--;
}
void Window::moveCursorDown (){
    if (selectpos<4) selectpos--;
}

void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const  {

        states.transform *= getTransform();
        states.texture = &texture;
        target.draw(vertexarray, states);
}