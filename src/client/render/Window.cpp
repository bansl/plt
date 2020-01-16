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
            quad[0].position = sf::Vector2f(0    , 510  );
            quad[1].position = sf::Vector2f(800  , 510  );
            quad[2].position = sf::Vector2f(800  , 600  );
            quad[3].position = sf::Vector2f(0    , 600  );

            //texture
            quad[0].texCoords = sf::Vector2f(0+i*tileDims        , 0           );
            quad[1].texCoords = sf::Vector2f(tileDims+i*tileDims , 0           );
            quad[2].texCoords = sf::Vector2f(tileDims+i*tileDims , tileDims );
            quad[3].texCoords = sf::Vector2f(0+i*tileDims        , tileDims );
        }
        std::vector<string> booldisp = {"No","Yes"};
        Cursor cursor(*turn.getCursor());
        message.tiletype="Tile Type:";
        std::vector<string> tiles = {"","Dirt","Grass","Water","Sand","Pound","Rock"};
        message.tiletype.append(tiles[turn.getMap()[cursor.getPosition().getX()][cursor.getPosition().getY()].getTile()]);
        Entity tilecheck{};
        message.isfree="Free: ";
        message.isfree.append(booldisp[tilecheck.isFree(turn,cursor.getPosition())]);
        message.iscrossable="Crossable: ";
        message.iscrossable.append(booldisp[tilecheck.isCrossable(turn.getMap()[cursor.getPosition().getX()][cursor.getPosition().getY()])]);

        message.team="Team: ";
        message.characterjob="Job: ";
        message.characterrace="Race: ";
        message.hp="HP: ";
        message.mp="MP: ";
        for (size_t team = 0; team < turn.getTeams().size(); team++)
        {
            for (size_t character = 0; character < turn.getTeams()[team]->getListCharacter().size(); character++)
            {
                if (cursor.getPosition().distanceBetween(cursor.getPosition(),turn.getTeams()[team]->getListCharacter()[character]->getPosition())==0){
                    Character selectedChar(*turn.getTeams()[team]->getListCharacter()[character]);
                    std::vector<string> jobs = {"Pugilist", "Swordman", "Archer", "Magician"};
                    message.characterjob.append(jobs[selectedChar.getJob().getJob()-1]);
                    std::vector<string> races = {"Monster", "Beastman", "Demon", "Human"};
                    message.characterrace.append(races[selectedChar.getRace().getRace()-1]);
                    vector<string> teamlabel= {"Blue","Red"};
                    message.team.append(teamlabel[team]);
                    message.hp.append(to_string(selectedChar.getCurrentHP())),message.hp.append("/"),message.hp.append(to_string(selectedChar.getMaxHP()));
                    message.mp.append(to_string(selectedChar.getCurrentMP())),message.mp.append("/"),message.mp.append(to_string(selectedChar.getMaxMP()));
                    break;
                }
            }

        }


        return true;
    }
    else if (windowType==actionselect)
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

        for (size_t i = 0; i < 2; i++){
            sf::Vertex* quad = &vertexarray[4*i];

            // vextex pos
            quad[0].position = sf::Vector2f(200  , 300  );
            quad[1].position = sf::Vector2f(400  , 300  );
            quad[2].position = sf::Vector2f(400  , 500  );
            quad[3].position = sf::Vector2f(200  , 500  );

            //texture
            quad[0].texCoords = sf::Vector2f(0+i*tileDims        , 0           );
            quad[1].texCoords = sf::Vector2f(tileDims+i*tileDims , 0           );
            quad[2].texCoords = sf::Vector2f(tileDims+i*tileDims , tileDims );
            quad[3].texCoords = sf::Vector2f(0+i*tileDims        , tileDims );
        }
        return true;
    }
    else
    {
        /* code */
    }
    return false;
}

bool Window::renderActionCursor(int selectpos,render::TileSet tileset){


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
  sf::Vertex* quad = &vertexarray[0];

  int xpos=225;
  // cout << "wd"<<endl;

  quad[0].position = sf::Vector2f(xpos          , (selectpos-1)*30  +320    );
  quad[1].position = sf::Vector2f(xpos + 25     , (selectpos-1)*30  +320    );
  quad[2].position = sf::Vector2f(xpos + 25     , (selectpos-1)*30  +340    );
  quad[3].position = sf::Vector2f(xpos          , (selectpos-1)*30  +340    );

  //texture
  quad[0].texCoords = sf::Vector2f(0           , 0           );
  quad[1].texCoords = sf::Vector2f(128         , 0           );
  quad[2].texCoords = sf::Vector2f(128         , 128         );
  quad[3].texCoords = sf::Vector2f(0           , 128         );

  return true;
}

void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const  {

        states.transform *= getTransform();
        states.texture = &texture;
        target.draw(vertexarray, states);
}

render::Message& Window::getMessage (){
	Message & addrMessage = message;
	return addrMessage ;
}
