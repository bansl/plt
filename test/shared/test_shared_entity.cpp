#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestEntity)
{
  Entity testEntity {};
  testEntity.initEntity();
  bool test = testEntity.getName()=="";
  BOOST_CHECK_EQUAL( (int) test,1);
  BOOST_CHECK_EQUAL( testEntity.getPosition().getX(),0);
  BOOST_CHECK_EQUAL( testEntity.getPosition().getY(),0);
  Tile waterTile;
  waterTile.tile=Water;
  testEntity.tile=waterTile;
  CharacterFactory cf {};
  testEntity.character=cf.createCharacter();
  BOOST_CHECK_EQUAL(testEntity.getTile().getTile(),Water);
  BOOST_CHECK_GT(testEntity.getCharacter().getMaxHP(),0);
  Entity tilecheck{};
  Turn turn;
  turn.initMap(2,2,"w1w1w1w1");
  turn.initTeams();
  turn.getTeams()[0]->addCharacter();
  turn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(1,0);
  Position newPosition;
  newPosition.setPos(0,0);
  BOOST_CHECK(tilecheck.isFree(turn,newPosition));
  BOOST_CHECK(tilecheck.isCrossable(turn.getMap()[0][0])==false);
}
