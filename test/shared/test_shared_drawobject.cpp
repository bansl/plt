#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/client/render.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Graphics/Image.hpp>

using namespace state;
using namespace render;
using namespace std;

BOOST_AUTO_TEST_CASE(TestDrawObject)
{
DrawObject rmb ;
state::Turn turnDisplay;
turnDisplay.initMap(8,8);
std::vector<std::shared_ptr<render::TileSet>> tilesets;
// TurnDisplay turnDisplay(turn);
TileSet tilesetMap(Maptile);
std::vector<std::string> imagePath;
imagePath.push_back("../../../res/maptile2x129.png");
tilesetMap.setImagePath(imagePath);
std::shared_ptr<TileSet> ptr_tilesetMap (new TileSet(tilesetMap));
tilesets.push_back(ptr_tilesetMap);



TileSet tilesetPersonnages(CharaSpritesheet);
std::vector<std::string> imagePath2;
imagePath2.push_back("../../../res/char1.png");
imagePath2.push_back("../../../res/char2.png");
tilesetPersonnages.setImagePath(imagePath2);
std::shared_ptr<TileSet> ptr_tilesetPersonnages (new TileSet(tilesetPersonnages));
tilesets.push_back(ptr_tilesetPersonnages);

turnDisplay.initTeams();
turnDisplay.getTeams()[0]->addCharacter();

vector<vector<int>> map_segmentation;
for (int i = 0; i < (int) turnDisplay.getTeams().size(); i++){
        for (int k=0; k< (int) turnDisplay.getTeams()[i]->getListCharacter().size(); k++) {
                vector<int> coord;
                coord.push_back(turnDisplay.getTeams()[i]->getListCharacter()[k]->getPosition().getX());
                coord.push_back(turnDisplay.getTeams()[i]->getListCharacter()[k]->getPosition().getY());
                int temp=0;
                for (int q=0; q<turnDisplay.rotation; q++){
                        temp=coord[0];
                        coord[0]=turnDisplay.getMap().size()-coord[1]-1;
                        coord[1]=temp;
                }
                map_segmentation.push_back(coord);
        }
}
vector<int> lastcoord;
lastcoord.push_back(turnDisplay.getMap().size());
lastcoord.push_back(turnDisplay.getMap()[0].size());
map_segmentation.push_back(lastcoord);

sort(map_segmentation.begin(),map_segmentation.end());
vector<int> segStart(2,0),segEnd(2,0);
for (int l=0; l< (int) map_segmentation.size(); l++){
        segStart[0]=segEnd[0],segStart[1]=segEnd[1];
        segEnd[0]=(map_segmentation[l][0]),segEnd[1]=(map_segmentation[l][1]);
      }


BOOST_CHECK(rmb.renderMapBase(turnDisplay.getMap(),*tilesets[0],{(int)turnDisplay.getMap().size(),(int) turnDisplay.getMap()[0].size()},{tilesets[0]->getXsize(), tilesets[0]->getYsize()},tilesets[0]->getMargin(),1,segStart,segEnd));

BOOST_CHECK(rmb.renderMapWalls(turnDisplay.getMap(),*tilesets[0],{(int)turnDisplay.getMap().size(),(int) turnDisplay.getMap()[0].size()},{tilesets[0]->getXsize(), tilesets[0]->getYsize()},tilesets[0]->getMargin(),1,segStart,segEnd));

//BOOST_CHECK(rmb.renderCharacter(turnDisplay,*tilesets[1], (int)turnDisplay.getMap().size(),(int)turnDisplay.getMap()[0].size(),tilesets[1]->getXsize(), tilesets[1]->getYsize(),tilesets[1]->getMargin(),0,1,0));
}
