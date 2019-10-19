#include "../render.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


using namespace std;
using namespace render;
using namespace state;
bool DrawObject::renderMapBase (state::Turn turn, render::TileSet tileset, int mapHeight, int mapWidth, int tileXsize, int tileYsize, int margin){

        if (!texture.loadFromFile(tileset.getImagePath())){
            return false;
	}
        
        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(mapWidth * mapHeight * 4);

        for (int i = 0; i < mapWidth; i++){
            for (int j = 0; j < mapHeight; j++){

                state::TileType tiletype=turn.getMap()[i][j].getTile();
                int tileheight=turn.getMap()[i][j].getHeight();
                tileheight=1; //disable height
                // cout << "check map : " << turn.getMap().size() << endl;
                int tu,tv;
                if(tiletype==Dirt){
                     tu=1;
                     tv=1;
                }
                else if(tiletype==Grass){
                     tu=0;
                     tv=1;
                }
                else if(tiletype==Water){
                     tu=1;
                     tv=2;
                }
                else if(tiletype==Sand){
                     tu=2;
                     tv=1;
                }
                else if(tiletype==Pound){
                     tu=1;
                     tv=0;
                }
                else if(tiletype==Rock){
                     tu=2;
                     tv=2;
                }      
                // cursor for current vextex
                sf::Vertex* quad = &vertexarray[(i + j * mapWidth) * 4];

                // vextex pos
                int xpos,ypos;
                xpos=(j-i+mapWidth-1)*(tileXsize/2);
                ypos=(j+i-1)*(tileYsize/4);
                quad[0].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileYsize/2   -   (tileheight-1)*tileYsize/2        );
                quad[1].position = sf::Vector2f(xpos + tileXsize     , ypos + 3*(tileYsize/4) -   (tileheight-1)*tileYsize/2       );
                quad[2].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileYsize  -   (tileheight-1)*tileYsize/2           );
                quad[3].position = sf::Vector2f(xpos                 , ypos + 3*(tileYsize/4)  -   (tileheight-1)*tileYsize/2      );


                // color
                // quad[0].color = sf::Color::Red;
                // quad[1].color = sf::Color::Green;
                // quad[2].color = sf::Color::Blue;
                // quad[3].color = sf::Color::Yellow;
                
                

                // texture coords
                // int txpos,typos;
                // txpos=(0-0)*(tileXsize/2);
                // typos=(0+0-1)*(tileXsize/4);
                // quad[0].texCoords = sf::Vector2f(txpos +(tu)*margin + tileXsize/2 + tu*tileYsize   , typos + (tv-1)*margin + tileXsize/2 + tv*tileYsize);
                // quad[1].texCoords = sf::Vector2f(txpos +(tu)*margin + tileXsize +   tu*tileYsize   , typos + (tv-1)*margin + 3*(tileXsize/4) + tv*tileYsize);
                // quad[2].texCoords = sf::Vector2f(txpos +(tu)*margin + tileXsize/2 + tu*tileYsize   , typos + (tv-1)*margin + tileXsize + tv*tileYsize);
                // quad[3].texCoords = sf::Vector2f(txpos +(tu)*margin +               tu*tileYsize   , typos + (tv-1)*margin + 3*(tileXsize/4) + tv*tileYsize);

                quad[0].texCoords = sf::Vector2f(tu * tileXsize +tu*margin         , tv * tileYsize +tv*margin);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileXsize +tu*margin   , tv * tileYsize +tv*margin);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileXsize +tu*margin   , (tv + 1) * tileYsize +tv*margin);
                quad[3].texCoords = sf::Vector2f(tu * tileXsize +tu*margin         , (tv + 1) * tileYsize +tv*margin);

           }    
        }
        return true;

}

bool DrawObject::renderMapWalls (state::Turn turn, render::TileSet tileset, int mapHeight, int mapWidth, int tileXsize, int tileYsize, int margin){
        if (!texture.loadFromFile(tileset.getImagePath())){
            return false;
	}
        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(mapWidth * mapHeight * 4);
        

        for (int i = 0; i < mapWidth; i++){
            for (int j = 0; j < mapHeight; j++){
                state::TileType tiletype=turn.getMap()[i][j].getTile();
                        // cout << "check map : " << turn.getMap().size() << endl;
                        int tu,tv;
                        if(tiletype==Dirt){
                                tu=1;
                                tv=1;
                        }
                        else if(tiletype==Grass){
                                tu=0;
                                tv=1;
                        }
                        else if(tiletype==Water){
                                tu=1;
                                tv=2;
                        }
                        else if(tiletype==Sand){
                                tu=2;
                                tv=1;
                        }
                        else if(tiletype==Pound){
                                tu=0;
                                tv=1;
                        }
                        else if(tiletype==Rock){
                                tu=2;
                                tv=2;
                        }      
                // if((j==mapHeight-1)||(turn.getMap()[i][j].getHeight()>turn.getMap()[i][j+1].getHeight())){
                if((j==mapHeight-1)){              
                        int tileheight= turn.getMap()[i][j].getHeight();  
                        tileheight=1; //disable height
                        // cursor for current vextex
                        sf::Vertex* quad = &vertexarray[(i + j * mapWidth) * 4];
                        // vextex pos
                        int xpos,ypos;
                        xpos=(j-i+mapWidth-1)*(tileXsize/2);
                        ypos=(j+i-1)*(tileYsize/4);
                        quad[0].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileYsize    -   (tileheight-1)*tileYsize/2   );
                        quad[1].position = sf::Vector2f(xpos + tileXsize     , ypos + 3*(tileYsize/4)  -   (tileheight-1)*tileYsize/2   );
                        quad[2].position = sf::Vector2f(xpos + tileXsize     , ypos + 3*(tileYsize/4)+tileYsize/2 -   (tileheight-1)*tileYsize/2   );
                        quad[3].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileYsize+tileYsize/2 -   (tileheight-1)*tileYsize/2   );
                        //texture
                        quad[0].texCoords = sf::Vector2f(tu * tileXsize +tu*margin         , tv * tileYsize +tv*margin);
                        quad[1].texCoords = sf::Vector2f((tu + 1) * tileXsize +tu*margin   , tv * tileYsize +tv*margin);
                        quad[2].texCoords = sf::Vector2f((tu + 1) * tileXsize +tu*margin   , (tv + 1) * tileYsize +tv*margin);
                        quad[3].texCoords = sf::Vector2f(tu * tileXsize +tu*margin         , (tv + 1) * tileYsize +tv*margin);
                }
                // if((i==mapWidth-1)||(turn.getMap()[i][j].getHeight()>turn.getMap()[i+1][j].getHeight())){ 
                if((i==mapWidth-1)){
                        int tileheight= turn.getMap()[i][j].getHeight();  
                        tileheight=1; //disable height                    
                        // cursor for current vextex
                        sf::Vertex* quad = &vertexarray[(i + j * mapWidth) * 4];
                        // vextex pos
                        int xpos,ypos;
                        xpos=(j-i+mapWidth-1)*(tileXsize/2);
                        ypos=(j+i-1)*(tileYsize/4);
                        quad[0].position = sf::Vector2f(xpos                 , ypos + 3*(tileXsize/4) -   (tileheight-1)*tileYsize/2   );
                        quad[1].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileXsize -   (tileheight-1)*tileYsize/2   );
                        quad[2].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileXsize+tileYsize/2   -   (tileheight-1)*tileYsize/2   );
                        quad[3].position = sf::Vector2f(xpos                 , ypos + 3*(tileXsize/4)+tileYsize/2  -   (tileheight-1)*tileYsize/2   );

                        //texture
                        quad[0].texCoords = sf::Vector2f(tu * tileXsize +tu*margin         , tv * tileYsize +tv*margin);
                        quad[1].texCoords = sf::Vector2f((tu + 1) * tileXsize +tu*margin   , tv * tileYsize +tv*margin);
                        quad[2].texCoords = sf::Vector2f((tu + 1) * tileXsize +tu*margin   , (tv + 1) * tileYsize +tv*margin);
                        quad[3].texCoords = sf::Vector2f(tu * tileXsize +tu*margin         , (tv + 1) * tileYsize +tv*margin);
                }
           }    
        }
        return true;

}

void DrawObject::draw(sf::RenderTarget& target, sf::RenderStates states) const  {
        
        states.transform *= getTransform();
        states.texture = &texture;
        target.draw(vertexarray, states);
        
}
