#include "../render.h"
#include <state.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Graphics/Image.hpp>



using namespace std;
using namespace render;
using namespace state;
bool DrawObject::renderMapBase (state::Turn& turn, render::TileSet tileset, int mapHeight, int mapWidth, int tileXsize, int tileYsize, int margin, int layer, int rotation){
  std::vector<std::vector<state::Tile>> rotateMapVector(turn.getMap());
  if (rotation!=0){
    for (int i=0; i<rotation; i++){
      rotateMapVector=rotateMap(rotateMapVector,rotateMapVector.size());
    }
  }
        if (!texture.loadFromFile(tileset.getImagePath()[0])){
            return false;
	}
        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(mapWidth * mapHeight * 4);

        for (int i = 0; i < mapWidth; i++){
                for (int j = 0; j < mapHeight; j++){
                if(rotateMapVector[i][j].getHeight()==layer){
                state::TileType tiletype=rotateMapVector[i][j].getTile();
                int tileheight=layer-1;
                // cout << "check map : " << turn.getMap().size() << endl;
                int tu,tv;
                if(tiletype==Dirt){tu=3,tv=0;}
                else if(tiletype==Grass){tu=0,tv=1;}
                else if(tiletype==Water){tu=1,tv=0;}
                else if(tiletype==Sand){tu=2,tv=0;}
                else if(tiletype==Pound){tu=3,tv=1;}
                else if(tiletype==Rock){tu=2,tv=1;}

                // cursor for current vextex
                sf::Vertex* quad = &vertexarray[(i + j * mapWidth) * 4];

                // vextex pos
                int xpos,ypos;
                xpos=(j-i+mapWidth-1)*(tileXsize/2);
                ypos=(j+i+4-tileheight)*(tileYsize/4);
                quad[0].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileYsize/2    );
                quad[1].position = sf::Vector2f(xpos + tileXsize     , ypos + 3*(tileYsize/4)     );
                quad[2].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileYsize         );
                quad[3].position = sf::Vector2f(xpos                 , ypos + 3*(tileYsize/4)   );

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

bool DrawObject::renderMapWalls (state::Turn& turn, render::TileSet tileset, int mapHeight, int mapWidth, int tileXsize, int tileYsize, int margin, int layer, int rotation){
  std::vector<std::vector<state::Tile>> rotateMapVector(turn.getMap());
  if (rotation!=0){
    for (int i=0; i<rotation; i++){
      rotateMapVector=rotateMap(rotateMapVector,rotateMapVector.size());
    }
  }
        if (!texture.loadFromFile(tileset.getImagePath()[0])){
            return false;
	}
        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(2*mapWidth * mapHeight * 4);
        int l=0, tileheight,xpos,ypos;
        sf::Vertex* quad;
        for (int i = 0; i < mapWidth; i++){
            for (int j = 0; j < mapHeight; j++){
                if(turn.getMap()[i][j].getHeight()>=layer){
                        state::TileType tiletype=turn.getMap()[i][j].getTile();
                        // cout << "check map : " << turn.getMap().size() << endl;
                        int tu,tv;
                        if(tiletype==Dirt){tu=3,tv=0;}
                        else if(tiletype==Grass){tu=0,tv=1;}
                        else if(tiletype==Water){tu=1,tv=0;}
                        else if(tiletype==Sand){tu=2,tv=0;}
                        else if(tiletype==Pound){tu=0,tv=1;}
                        else if(tiletype==Rock){tu=2,tv=1;}

                        if((i==mapWidth-1)||(j==mapHeight-1)||(turn.getMap()[i][j].getHeight()>turn.getMap()[i][j+1].getHeight())){
                        // if((j==mapHeight-1)){
                                tileheight= layer-1;

                                // cursor for current vextex
                                quad = &vertexarray[l * 4];
                                // vextex pos

                                xpos=(j-i+mapWidth-1)*(tileXsize/2);
                                ypos=(j+i+4-tileheight)*(tileYsize/4);
                                quad[0].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileYsize   );
                                quad[1].position = sf::Vector2f(xpos + tileXsize     , ypos + 3*(tileYsize/4)   );
                                quad[2].position = sf::Vector2f(xpos + tileXsize     , ypos + 3*(tileYsize/4)+tileYsize/2  /2 );
                                quad[3].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileYsize+tileYsize/2 /2 );
                                //texture
                                quad[0].texCoords = sf::Vector2f(tu * tileXsize +tu*margin         , tv * tileYsize +tv*margin);
                                quad[1].texCoords = sf::Vector2f((tu + 1) * tileXsize +tu*margin   , tv * tileYsize +tv*margin);
                                quad[2].texCoords = sf::Vector2f((tu + 1) * tileXsize +tu*margin   , (tv + 1) * tileYsize +tv*margin);
                                quad[3].texCoords = sf::Vector2f(tu * tileXsize +tu*margin         , (tv + 1) * tileYsize +tv*margin);

                                l++;
                        }


                        if((j==mapHeight-1)||(i==mapWidth-1)||(turn.getMap()[i][j].getHeight()>turn.getMap()[i+1][j].getHeight())){
                        // if((i==mapWidth-1)){
                                tileheight= layer-1;

                                quad = &vertexarray[l * 4];

                                // vextex pos
                                xpos=(j-i+mapWidth-1)*(tileXsize/2);
                                ypos=(j+i+4-tileheight)*(tileYsize/4);
                                quad[0].position = sf::Vector2f(xpos                 , ypos + 3*(tileXsize/4)  );
                                quad[1].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileXsize    );
                                quad[2].position = sf::Vector2f(xpos + tileXsize/2   , ypos + tileXsize+tileYsize/2   /2 );
                                quad[3].position = sf::Vector2f(xpos                 , ypos + 3*(tileXsize/4)+tileYsize/2 /2  );

                                //texture
                                quad[0].texCoords = sf::Vector2f(tu * tileXsize +tu*margin         , tv * tileYsize +tv*margin);
                                quad[1].texCoords = sf::Vector2f((tu + 1) * tileXsize +tu*margin   , tv * tileYsize +tv*margin);
                                quad[2].texCoords = sf::Vector2f((tu + 1) * tileXsize +tu*margin   , (tv + 1) * tileYsize +tv*margin);
                                quad[3].texCoords = sf::Vector2f(tu * tileXsize +tu*margin         , (tv + 1) * tileYsize +tv*margin);

                                l++;
                        }

                }
            }
        }

        return true;

}



bool DrawObject::renderCharacter(state::Turn& turn, render::TileSet tileset, int mapHeight, int mapWidth, int tileXsize, int tileYsize, int margin, int spriteNb, int charNb,int rotation){

        sf::Image image;
        image.loadFromFile(tileset.getImagePath()[0]);
        sf::Color color(147, 187, 236);
        image.createMaskFromColor(color);
        sf::Color color2(27, 89, 153);
        image.createMaskFromColor(color2);
        if (!texture.loadFromImage(image)){
                return false;
        }

        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(mapWidth * mapHeight * 4);

        int i=0;



        float charPosX= (float) turn.getTeams()[0]->getListCharacter()[charNb]->getPosition().getX();
        float charPosY= (float) turn.getTeams()[0]->getListCharacter()[charNb]->getPosition().getY();

        // float charPosX= 5;
        // float charPosY= 0;
        float tileheight= (float) (turn.getMap()[(int)charPosX][(int)charPosY].getHeight());
        tileheight +=-1;
        int tv=0; //idle anim
        float isoPosX=((-charPosX+charPosY)*8+mapWidth*8)/16;//mapWidth/2-(charPosY-charPosX/2);
        float isoPosY=((charPosX+charPosY-tileheight)*27+mapWidth*64)/128-2;//1+(charPosY+charPosX)/2;
        // cursor for current vertex
        sf::Vertex* quad = &vertexarray[i * 4];

        // vextex pos
        quad[0].position = sf::Vector2f(isoPosX * tileXsize - tileXsize/2       , isoPosY * tileYsize - tileYsize/2);
        quad[1].position = sf::Vector2f((isoPosX + 1) * tileXsize - tileXsize/2  , isoPosY * tileYsize - tileYsize/2);
        quad[2].position = sf::Vector2f((isoPosX + 1) * tileXsize - tileXsize/2  , (isoPosY + 1) * tileYsize - tileYsize/2);
        quad[3].position = sf::Vector2f(isoPosX * tileXsize - tileXsize/2        , (isoPosY + 1) * tileYsize - tileYsize/2);

        // texture
        quad[0].texCoords = sf::Vector2f(spriteNb * tileXsize + spriteNb           , tv * tileYsize + margin);
        quad[1].texCoords = sf::Vector2f((spriteNb + 1) * tileXsize + spriteNb     , tv * tileYsize + margin);
        quad[2].texCoords = sf::Vector2f((spriteNb + 1) * tileXsize + spriteNb      , (tv + 1) * tileYsize + margin);
        quad[3].texCoords = sf::Vector2f(spriteNb * tileXsize  + spriteNb       , (tv + 1) * tileYsize + margin);
        i++;



		return true;
}





void DrawObject::draw(sf::RenderTarget& target, sf::RenderStates states) const  {

        states.transform *= getTransform();
        states.texture = &texture;
        target.draw(vertexarray, states);

}

std::vector<std::vector<state::Tile>> DrawObject::rotateMap(std::vector<std::vector<state::Tile>> map, int N){
  std::vector<std::vector<state::Tile>> rotateMap;
  for (int x = 0; x < N / 2; x++)
    {   // Consider elements in group of 4 in current square
        for (int y = x; y < N-x-1; y++)
        {   // store current cell in temp variable
            rotateMap[N-1-y][x] = map[x][y];
            // move values from right to top
            rotateMap[x][y] = map[y][N-1-x];
            // move values from bottom to right
            rotateMap[y][N-1-x] = map[N-1-x][N-1-y];
            // move values from left to bottom
            rotateMap[N-1-x][N-1-y] = map[N-1-y][x];
        }
    }
    return rotateMap;
}
