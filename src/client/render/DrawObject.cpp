#include "../render.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


using namespace std;
using namespace render;
using namespace state;
bool DrawObject::renderMap (state::Turn turn, render::TileSet tileset, int mapHeight, int mapWidth, int tileXsize, int tileYsize){

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
                     tv=1;
                }
                else if(tiletype==Grass){
                     tu=2;
                     tv=2;
                }
                else {
                 tu=3;
                 tv=3;
                }
                // cursor for current vextex
                sf::Vertex* quad = &vertexarray[(i + j * mapWidth) * 4];

                                // vextex pos
                                quad[0].position = sf::Vector2f(i * tileXsize, j * tileYsize);
                                quad[1].position = sf::Vector2f((i+ 1) * tileXsize, j * tileYsize);
                                quad[2].position = sf::Vector2f((i + 1) * tileXsize, (j + 1) * tileYsize);
                                quad[3].position = sf::Vector2f(i * tileXsize, (j + 1) * tileYsize);

                                // color
                                // quad[0].color = sf::Color::Red;
                                // quad[1].color = sf::Color::Green;
                                // quad[2].color = sf::Color::Blue;
                                // quad[3].color = sf::Color::Yellow;

                                // texure coords
                                quad[0].texCoords = sf::Vector2f(tu * tileXsize, tv * tileYsize);
                                quad[1].texCoords = sf::Vector2f((tu + 1) * tileXsize, tv * tileYsize);
                                quad[2].texCoords = sf::Vector2f((tu + 1) * tileXsize, (tv + 1) * tileYsize);
                                quad[3].texCoords = sf::Vector2f(tu * tileXsize, (tv + 1) * tileYsize);

           }
        }
        return true;

}

void DrawObject::draw(sf::RenderTarget& target, sf::RenderStates states) const  {

        target.draw(vertexarray, states);
        states.transform *= getTransform();
        states.texture = &texture;
}
