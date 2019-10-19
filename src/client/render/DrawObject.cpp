#include "../render.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


using namespace std;
using namespace render;
using namespace state;
bool DrawObject::renderMap (state::Turn turn, render::TileSet tileset, int mapHeight, int mapWidth, int tileXsize, int tileYsize, int margin){

        if (!texture.loadFromFile(tileset.getImagePath())){
            return false;
	}
        
        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(mapWidth * mapHeight * 4);

        for (size_t i = 0; i < mapWidth; i++){
            for (size_t j = 0; j < mapHeight; j++){

                state::TileType tiletype=turn.getMap()[i][j].getTile();
                // cout << "check map : " << turn.getMap().size() << endl;
                int tu,tv;
                if(tiletype==Dirt){
                     tu=1;
                     tv=2;
                }
                else if(tiletype==Grass){
                     tu=0;
                     tv=0;
                }
                else if(tiletype==Water){
                     tu=0;
                     tv=1;
                }
                else if(tiletype==Sand){
                     tu=2;
                     tv=1;
                }
                else if(tiletype==Pound){
                     tu=1;
                     tv=3;
                }
                else if(tiletype==Rock){
                     tu=2;
                     tv=0;
                }         
                // cursor for current vextex
                sf::Vertex* quad = &vertexarray[(i + j * mapWidth) * 4];

                                // vextex pos
                                int xpos,ypos;
                                xpos=(j-i+mapWidth-1)*(tileXsize/2);
                                ypos=(j+i-2)*(tileXsize/4);
                                quad[0].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileXsize/2);
                                quad[1].position = sf::Vector2f(xpos + tileXsize     , ypos + 3*(tileXsize/4));
                                quad[2].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileXsize);
                                quad[3].position = sf::Vector2f(xpos                 , ypos + 3*(tileXsize/4));

                                // color
                                quad[0].color = sf::Color::Red;
                                quad[1].color = sf::Color::Green;
                                quad[2].color = sf::Color::Blue;
                                quad[3].color = sf::Color::Yellow;

                                // texture coords
                                // quad[0].texCoords = sf::Vector2f(tu * tileXsize +(tu-1)*margin, tv * tileYsize + (tv-1)*margin);
                                // quad[1].texCoords = sf::Vector2f((tu + 1) * tileXsize +(tu-1)*margin, tv * tileYsize + (tv-1)*margin);
                                // quad[2].texCoords = sf::Vector2f((tu + 1) * tileXsize +(tu-1)*margin, (tv + 1) * tileYsize + (tv-1)*margin);
                                // quad[3].texCoords = sf::Vector2f(tu * tileXsize +(tu-1)*margin, (tv + 1) * tileYsize + (tv-1)*margin);

           }
        }
        return true;

}

void DrawObject::draw(sf::RenderTarget& target, sf::RenderStates states) const  {
        target.draw(vertexarray, states);
        states.transform *= getTransform();
        states.texture = &texture;
        
}
