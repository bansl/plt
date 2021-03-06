#include "../render.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Graphics/Image.hpp>



using namespace std;
using namespace render;
using namespace state;
bool DrawObject::renderMapBase (std::vector<std::vector<state::Tile>> map, render::TileSet tileset, std::vector<int> mapDims, std::vector<int> tileDims, int margin, int layer, std::vector<int> pos, std::vector<int> posEnd){

        if (!texture.loadFromFile(tileset.getImagePath()[0])){
          std::vector<std::string> imagePath;
          imagePath.push_back("../../../res/maptile2x129.png");
          imagePath.push_back("../../../res/char1.png");
          imagePath.push_back("../../../res/char2.png");
          imagePath.push_back("../../../res/cursor.png");
          imagePath.push_back("../../../res/windowsprite.png");
          imagePath.push_back("../../../res/handpointer.png");

          tileset.setImagePath(imagePath);
          if (!texture.loadFromFile(tileset.getImagePath()[0])){
            return false;
          }
	}
        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(mapDims[0] * mapDims[1] * 4);

        for (int i = pos[0]; i < mapDims[0]; i++){
                for (int j = 0; j < mapDims[1]; j++){
                        if(i==pos[0] && j==0){
                                if(i==0) j=pos[1];
                                else j=pos[1]+1;
                        }
                        if(map[i][j].getHeight()==layer){
                                state::TileType tiletype=map[i][j].getTile();
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
                                sf::Vertex* quad = &vertexarray[(i + j * mapDims[0]) * 4];

                                // vextex pos
                                int xpos,ypos;
                                xpos=(j-i)*(tileDims[0]/2);
                                ypos=(j+i-tileheight)*(tileDims[1]/4);
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
                        if(i==posEnd[0] && j == posEnd[1]){
                                return true;
                        }
                }

        }
        return true;

}

bool DrawObject::renderMapWalls (std::vector<std::vector<state::Tile>> map, render::TileSet tileset, std::vector<int> mapDims, std::vector<int> tileDims, int margin, int layer, std::vector<int> pos, std::vector<int> posEnd){

  if (!texture.loadFromFile(tileset.getImagePath()[0])){
    std::vector<std::string> imagePath;
    imagePath.push_back("../../../res/maptile2x129.png");
    imagePath.push_back("../../../res/char1.png");
    imagePath.push_back("../../../res/char2.png");
    imagePath.push_back("../../../res/cursor.png");
    imagePath.push_back("../../../res/windowsprite.png");
    imagePath.push_back("../../../res/handpointer.png");

    tileset.setImagePath(imagePath);
    if (!texture.loadFromFile(tileset.getImagePath()[0])){
      return false;
    }
   }
        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(2*mapDims[0] * mapDims[1] * 4);
        int l=0, tileheight,xpos,ypos;
        sf::Vertex* quad;
        for (int i = pos[0]; i < mapDims[0]; i++){
            for (int j = 0; j < mapDims[1]; j++){
                if(i==pos[0] && j==0){
                        j=pos[1];
                }
                if(map[i][j].getHeight()>=layer){
                        state::TileType tiletype=map[i][j].getTile();
                        // cout << "check map : " << turn.getMap().size() << endl;
                        int tu,tv;
                        if(tiletype==Dirt){tu=3,tv=0;}
                        else if(tiletype==Grass){tu=0,tv=1;}
                        else if(tiletype==Water){tu=1,tv=0;}
                        else if(tiletype==Sand){tu=2,tv=0;}
                        else if(tiletype==Pound){tu=0,tv=1;}
                        else if(tiletype==Rock){tu=2,tv=1;}

                        if((i==mapDims[0]-1)||(j==mapDims[1]-1)||(map[i][j].getHeight()>map[i][j+1].getHeight())){
                        // if((j==mapDims[1]-1)){
                                tileheight= layer-1;

                                // cursor for current vextex
                                quad = &vertexarray[l * 4];
                                // vextex pos

                                xpos=(j-i)*(tileDims[0]/2);
                                ypos=(j+i-tileheight)*(tileDims[1]/4);
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


                        if((j==mapDims[1]-1)||(i==mapDims[0]-1)||(map[i][j].getHeight()>map[i+1][j].getHeight())){
                        // if((i==mapDims[0]-1)){
                                tileheight= layer-1;

                                quad = &vertexarray[l * 4];

                                // vextex pos
                                xpos=(j-i)*(tileDims[0]/2);
                                ypos=(j+i-tileheight)*(tileDims[1]/4);
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
                if(i==posEnd[0] && j == posEnd[1]){
                        return true;
                }
            }
        }

        return true;

}

bool DrawObject::renderCursor(state::Turn& turn, render::TileSet tileset, std::vector<int> mapDims, std::vector<int> tileDims){
        if (!texture.loadFromFile(tileset.getImagePath()[0])){
          std::vector<std::string> imagePath;
          imagePath.push_back("../../../res/maptile2x129.png");
          imagePath.push_back("../../../res/char1.png");
          imagePath.push_back("../../../res/char2.png");
          imagePath.push_back("../../../res/cursor.png");
          imagePath.push_back("../../../res/windowsprite.png");
          imagePath.push_back("../../../res/handpointer.png");
          tileset.setImagePath(imagePath);
          if (!texture.loadFromFile(tileset.getImagePath()[0])){
            return false;
          }
	}
        vertexarray.setPrimitiveType(sf::Quads);
        vertexarray.resize(4);
        int tempPosX=turn.getCursor()->getPosition().getX();
        int tempPosY=turn.getCursor()->getPosition().getY();
        int temp=0;
        for (int q=0; q<turn.rotation; q++){
          temp=tempPosX;
          tempPosX=turn.getMap().size()-tempPosY-1;
          tempPosY=temp;
        }

        float cursPosX= (float) tempPosX;
        float cursPosY= (float) tempPosY;
        float tileheight= (float) (turn.getMap()[turn.getCursor()->getPosition().getX()][turn.getCursor()->getPosition().getY()].getHeight());
        tileheight +=-1;

        // cursor for current vertex
        sf::Vertex* quad = &vertexarray[0];

        // vextex pos
        int xpos,ypos;
        xpos=(cursPosY-cursPosX)*(tileDims[0]/2);
        ypos=(cursPosY+cursPosX-tileheight)*(tileDims[1]/4);
        quad[0].position = sf::Vector2f(xpos + tileDims[0]/2   , ypos + tileDims[1]/2     );
        quad[1].position = sf::Vector2f(xpos + tileDims[0]     , ypos + 3*(tileDims[1]/4) );
        quad[2].position = sf::Vector2f(xpos + tileDims[0]/2   , ypos + tileDims[1]       );
        quad[3].position = sf::Vector2f(xpos                   , ypos + 3*(tileDims[1]/4) );

        //texture
        quad[0].texCoords = sf::Vector2f(0           , 0           );
        quad[1].texCoords = sf::Vector2f(tileDims[0] , 0           );
        quad[2].texCoords = sf::Vector2f(tileDims[0] , tileDims[1] );
        quad[3].texCoords = sf::Vector2f(0           , tileDims[1] );

        return true;
}

bool DrawObject::renderCharacter(state::Turn& turn, render::TileSet tileset, int mapHeight, int mapWidth, int tileXsize, int tileYsize, int margin, int spriteNb, int charNb, int playerId){

        sf::Image image;
        if (!texture.loadFromFile(tileset.getImagePath()[playerId])){ // Segment of code to avoid error in build test on Jenkins server
          std::vector<std::string> imagePath;
          imagePath.push_back("../../../res/maptile2x129.png");
          imagePath.push_back("../../../res/char1.png");
          imagePath.push_back("../../../res/char2.png");
          imagePath.push_back("../../../res/cursor.png");
          imagePath.push_back("../../../res/windowsprite.png");

          tileset.setImagePath(imagePath);
          if (!texture.loadFromFile(tileset.getImagePath()[playerId])){
            return false;
          }
         }
        image.loadFromFile(tileset.getImagePath()[playerId]);
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
        int facing=turn.getTeams()[playerId]->getListCharacter()[charNb]->getFacing();
        int tempPosX=turn.getTeams()[playerId]->getListCharacter()[charNb]->getPosition().getX();
        int tempPosY=turn.getTeams()[playerId]->getListCharacter()[charNb]->getPosition().getY();
        int temp=0;

        for (int q=0; q<turn.rotation; q++){
          temp=tempPosX;
          tempPosX=turn.getMap().size()-tempPosY-1;
          tempPosY=temp;
          facing=(facing+1)%4;
        }

        float charPosX= (float) tempPosX;
        float charPosY= (float) tempPosY;
        float tileheight= (float) (turn.getMap()[turn.getTeams()[playerId]->getListCharacter()[charNb]->getPosition().getX()][turn.getTeams()[playerId]->getListCharacter()[charNb]->getPosition().getY()].getHeight());
        tileheight +=-1;
        int tv=0; //idle anim
        StatusList status = turn.getTeams()[playerId]->getListCharacter()[charNb]->getStatus();
        if(status==Attacking) tv=3*(facing)+2;//, cout << "status=attacking"<<endl;
        if(status==UsingObj) tv=3*(facing)+0;//, cout << "status=usingObj"<<endl;
        if(status==Moving) tv=3*(facing)+1;//, cout << "status=moving"<<endl;
        else tv=3*(facing)+0;

                                // xpos=(j-i)*(tileDims[0]/2);
                                // ypos=(j+i-tileheight)*(tileDims[1]/4);
        float isoPosX=(charPosY-charPosX+1.f)/2.011;
        float isoPosY=(charPosX+charPosY)*((129.f/155.f)/4.03) - tileheight/6.f +1.f/6.f;
        // cursor for current vertex
        sf::Vertex* quad = &vertexarray[i * 4];
        if(status!=Dead){
                // vextex pos
                quad[0].position = sf::Vector2f(isoPosX * (float)tileXsize - (float)tileXsize/2.f       , isoPosY * (float)tileYsize - (float)tileYsize/2.f);
                quad[1].position = sf::Vector2f((isoPosX + 1) * (float)tileXsize - (float)tileXsize/2.f  , isoPosY * (float)tileYsize - (float)tileYsize/2.f);
                quad[2].position = sf::Vector2f((isoPosX + 1) * (float)tileXsize - (float)tileXsize/2.f  , (isoPosY + 1) * (float)tileYsize - (float)tileYsize/2.f);
                quad[3].position = sf::Vector2f(isoPosX * (float)tileXsize - (float)tileXsize/2.f        , (isoPosY + 1) * (float)tileYsize - (float)tileYsize/2.f);

                // texture
                quad[0].texCoords = sf::Vector2f(spriteNb * tileXsize + spriteNb           , tv * tileYsize + margin);
                quad[1].texCoords = sf::Vector2f((spriteNb + 1) * tileXsize + spriteNb     , tv * tileYsize + margin);
                quad[2].texCoords = sf::Vector2f((spriteNb + 1) * tileXsize + spriteNb      , (tv + 1) * tileYsize + margin);
                quad[3].texCoords = sf::Vector2f(spriteNb * tileXsize  + spriteNb       , (tv + 1) * tileYsize + margin);
        }
        else{
                // vextex pos
                quad[0].position = sf::Vector2f(0, 0);
                quad[1].position = sf::Vector2f(0, 0);
                quad[2].position = sf::Vector2f(0, 0);
                quad[3].position = sf::Vector2f(0, 0);

                // texture
                quad[0].texCoords = sf::Vector2f(0, 0);
                quad[1].texCoords = sf::Vector2f(0, 0);
                quad[2].texCoords = sf::Vector2f(0, 0);
                quad[3].texCoords = sf::Vector2f(0, 0);
        }
        if( (turn.getTeams()[playerId]->getListCharacter()[charNb]->getStatus()==Used) || (turn.getTeams()[playerId]->getListCharacter()[charNb]->getStatus()==Defending) ) shaders=1;
        else shaders=0;
	return true;
}


void DrawObject::changeCharAnimSpriteNb (int spriteNb, int tileXsize, int tileYsize, int margin, state::Turn& turn, int playerId, int charNb){
        int facing=turn.getTeams()[playerId]->getListCharacter()[charNb]->getFacing();
        int tv=0; //idle anim
        for (int q=0; q<turn.rotation; q++){
          facing=(facing+1)%4;
        }
        StatusList status = turn.getTeams()[playerId]->getListCharacter()[charNb]->getStatus();
        if(status!=Dead){
                if(status==Attacking) tv=3*(facing)+2;
                if(status==UsingObj) tv=3*(facing)+0;
                if(status==Moving) tv=3*(facing)+1;
                else tv=3*(facing)+0;
                sf::Vertex* quad = &vertexarray[0];
                quad[0].texCoords = sf::Vector2f(spriteNb * tileXsize + spriteNb           , tv * tileYsize + margin);
                quad[1].texCoords = sf::Vector2f((spriteNb + 1) * tileXsize + spriteNb     , tv * tileYsize + margin);
                quad[2].texCoords = sf::Vector2f((spriteNb + 1) * tileXsize + spriteNb      , (tv + 1) * tileYsize + margin);
                quad[3].texCoords = sf::Vector2f(spriteNb * tileXsize  + spriteNb       , (tv + 1) * tileYsize + margin);
        }
}


// void DrawObject::draw(sf::RenderTarget& target, sf::RenderStates states, sf::Shader& shaders) const  {
void DrawObject::draw(sf::RenderTarget& target, sf::RenderStates states) const  {
        sf::Shader shaderobj;
        if (shaders==1){

                shaderobj.loadFromFile("res/transparency.frag", sf::Shader::Fragment) ;
                shaderobj.setParameter("opacity", 0.6f);
                shaderobj.setParameter("texture", sf::Shader::CurrentTexture) ;
                states.blendMode = sf::BlendAlpha ;
                states.shader = &shaderobj;
        }

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
