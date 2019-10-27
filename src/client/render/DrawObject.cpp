#include "../render.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Graphics/Image.hpp>



using namespace std;
using namespace render;
using namespace state;
bool DrawObject::renderMapBase (std::vector<std::vector<state::Tile>> map, render::TileSet tileset, std::vector<int> mapDims, std::vector<int> tileDims, int margin, int layer, int rotation, std::vector<int> pos){
        
        if (!texture.loadFromFile(tileset.getImagePath()[0])){
            return false;
	}
        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(4);

        
        if(map[pos[0]][pos[1]].getHeight()==layer){
                state::TileType tiletype=map[pos[0]][pos[1]].getTile();
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
                sf::Vertex* quad = &vertexarray[0];

                // vextex pos
                int xpos,ypos;
                xpos=(pos[1]-pos[0]+mapDims[0]-1)*(tileDims[0]/2);
                ypos=(pos[1]+pos[0]+4-tileheight)*(tileDims[1]/4);
                quad[0].position = sf::Vector2f(xpos + tileDims[0]/2   , ypos + tileDims[1]/2    );
                quad[1].position = sf::Vector2f(xpos + tileDims[0]     , ypos + 3*(tileDims[1]/4)     );
                quad[2].position = sf::Vector2f(xpos + tileDims[0]/2   , ypos + tileDims[1]       );
                quad[3].position = sf::Vector2f(xpos                 , ypos + 3*(tileDims[1]/4)  );

                //texture
                quad[0].texCoords = sf::Vector2f(tu * tileDims[0] +tu*margin         , tv * tileDims[1] +tv*margin);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileDims[0] +tu*margin   , tv * tileDims[1] +tv*margin);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileDims[0] +tu*margin   , (tv + 1) * tileDims[1] +tv*margin);
                quad[3].texCoords = sf::Vector2f(tu * tileDims[0] +tu*margin         , (tv + 1) * tileDims[1] +tv*margin);
               
        }

        return true;

}

bool DrawObject::renderMapWalls (std::vector<std::vector<state::Tile>> map, render::TileSet tileset, std::vector<int> mapDims, std::vector<int> tileDims, int margin, int layer, int rotation, std::vector<int> pos){

        if (!texture.loadFromFile(tileset.getImagePath()[0])){
            return false;
	}
        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(2* 4);
        int l=0, tileheight,xpos,ypos;
        sf::Vertex* quad;
        
        if(map[pos[0]][pos[1]].getHeight()>=layer){
                state::TileType tiletype=map[pos[0]][pos[1]].getTile();
                // cout << "check map : " << turn.getMap().size() << endl;
                int tu,tv;
                if(tiletype==Dirt){tu=3,tv=0;}
                else if(tiletype==Grass){tu=0,tv=1;}
                else if(tiletype==Water){tu=1,tv=0;}
                else if(tiletype==Sand){tu=2,tv=0;}
                else if(tiletype==Pound){tu=0,tv=1;}
                else if(tiletype==Rock){tu=2,tv=1;}

                if((pos[0]==mapDims[0]-1)||(pos[1]==mapDims[1]-1)||(map[pos[0]][pos[1]].getHeight()>map[pos[0]][pos[1]+1].getHeight())){
                // if((j==mapDims[1]-1)){
                        tileheight= layer-1;

                        // cursor for current vextex
                        quad = &vertexarray[l * 4];
                        // vextex pos

                        xpos=(pos[1]-pos[0]+mapDims[0]-1)*(tileDims[0]/2);
                        ypos=(pos[1]+pos[0]+4-tileheight)*(tileDims[1]/4);
                        quad[0].position = sf::Vector2f(xpos + tileDims[0]/2   , ypos + tileDims[1]   );
                        quad[1].position = sf::Vector2f(xpos + tileDims[0]     , ypos + 3*(tileDims[1]/4)   );
                        quad[2].position = sf::Vector2f(xpos + tileDims[0]     , ypos + 3*(tileDims[1]/4)+tileDims[1]/2  /2 );
                        quad[3].position = sf::Vector2f(xpos + tileDims[0]/2   , ypos + tileDims[1]+tileDims[1]/2 /2 );
                        //texture
                        quad[0].texCoords = sf::Vector2f(tu * tileDims[0] +tu*margin         , tv * tileDims[1] +tv*margin);
                        quad[1].texCoords = sf::Vector2f((tu + 1) * tileDims[0] +tu*margin   , tv * tileDims[1] +tv*margin);
                        quad[2].texCoords = sf::Vector2f((tu + 1) * tileDims[0] +tu*margin   , (tv + 1) * tileDims[1] +tv*margin);
                        quad[3].texCoords = sf::Vector2f(tu * tileDims[0] +tu*margin         , (tv + 1) * tileDims[1] +tv*margin);

                        l++;
                }


                if((pos[1]==mapDims[1]-1)||(pos[0]==mapDims[0]-1)||(map[pos[0]][pos[1]].getHeight()>map[pos[0]+1][pos[1]].getHeight())){
                // if((i==mapDims[0]-1)){
                        tileheight= layer-1;

                        quad = &vertexarray[l * 4];

                        // vextex pos
                        xpos=(pos[1]-pos[0]+mapDims[0]-1)*(tileDims[0]/2);
                        ypos=(pos[1]+pos[0]+4-tileheight)*(tileDims[1]/4);
                        quad[0].position = sf::Vector2f(xpos                 , ypos + 3*(tileDims[0]/4)  );
                        quad[1].position = sf::Vector2f(xpos + tileDims[0]/2   , ypos + tileDims[0]    );
                        quad[2].position = sf::Vector2f(xpos + tileDims[0]/2   , ypos + tileDims[0]+tileDims[1]/2   /2 );
                        quad[3].position = sf::Vector2f(xpos                 , ypos + 3*(tileDims[0]/4)+tileDims[1]/2 /2  );

                        //texture
                        quad[0].texCoords = sf::Vector2f(tu * tileDims[0] +tu*margin         , tv * tileDims[1] +tv*margin);
                        quad[1].texCoords = sf::Vector2f((tu + 1) * tileDims[0] +tu*margin   , tv * tileDims[1] +tv*margin);
                        quad[2].texCoords = sf::Vector2f((tu + 1) * tileDims[0] +tu*margin   , (tv + 1) * tileDims[1] +tv*margin);
                        quad[3].texCoords = sf::Vector2f(tu * tileDims[0] +tu*margin         , (tv + 1) * tileDims[1] +tv*margin);

                        l++;
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
        vertexarray.resize(4);

        int i=0;
        int tempPosX=turn.getTeams()[0]->getListCharacter()[charNb]->getPosition().getX();
        int tempPosY=turn.getTeams()[0]->getListCharacter()[charNb]->getPosition().getY();
        int temp=0;
        for (int q=0; q<rotation; q++){
          temp=tempPosX;
          tempPosX=turn.getMap().size()-tempPosY-1;
          tempPosY=temp;
        }

        //float charPosX= (float) turn.getTeams()[0]->getListCharacter()[charNb]->getPosition().getX();
        //float charPosY= (float) turn.getTeams()[0]->getListCharacter()[charNb]->getPosition().getY();
        float charPosX= (float) tempPosX;
        float charPosY= (float) tempPosY;
        // float charPosX= 5;
        // float charPosY= 0;
        float tileheight= (float) (turn.getMap()[turn.getTeams()[0]->getListCharacter()[charNb]->getPosition().getX()][turn.getTeams()[0]->getListCharacter()[charNb]->getPosition().getY()].getHeight());
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



		return true;
}





void DrawObject::draw(sf::RenderTarget& target, sf::RenderStates states) const  {

        states.transform *= getTransform();
        states.texture = &texture;
        target.draw(vertexarray, states);

}

std::vector<std::vector<state::Tile>> DrawObject::rotateMap(std::vector<std::vector<state::Tile>> map, int N){
  std::vector<std::vector<state::Tile>> rotateMapVector(map);
  for (int x = 0; x < N / 2; x++)
    {   // Consider elements in group of 4 in current square
        for (int y = x; y < N-x-1; y++)
        {   // store current cell in temp variable
            rotateMapVector[N-1-y][x] = map[x][y];
            // move values from right to top
            rotateMapVector[x][y] = map[y][N-1-x];
            // move values from bottom to right
            rotateMapVector[y][N-1-x] = map[N-1-x][N-1-y];
            // move values from left to bottom
            rotateMapVector[N-1-x][N-1-y] = map[N-1-y][x];
        }
    }
    return rotateMapVector;
}
