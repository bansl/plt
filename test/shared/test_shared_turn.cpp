#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <sstream>
#include <iostream>
#include <cstring>

using namespace state;


BOOST_AUTO_TEST_CASE(TestTurn)
{
  Turn testTurn {};
  testTurn.nextTurn();
  BOOST_CHECK_EQUAL(testTurn.getTurn(),2);

  BOOST_CHECK_EQUAL( (int) testTurn.initCursor(),1);
  Cursor* ptrCursor=testTurn.getCursor();
  Position CursorPos = ptrCursor->getPosition();
  CursorPos.setPos(7,4);
  BOOST_CHECK_EQUAL( CursorPos.getX(),7);
  BOOST_CHECK_EQUAL( CursorPos.getY(),4);

  testTurn.initTeams();
  testTurn.getTeams()[0]->addCharacter();
  BOOST_CHECK_GT(testTurn.getTeams()[0]->getListCharacter()[0]->getMaxHP(),0);

  testTurn.initMap(49,49);
  BOOST_CHECK_EQUAL(testTurn.getMap().size(),49);
  BOOST_CHECK_GT(testTurn.getMap()[0][0].getTile(),0);
  BOOST_CHECK_EQUAL(testTurn.getCharacterHeight(0,0),testTurn.getMap()[testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().getX()][testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().getY()].getHeight());

  Turn testTurn2 {};
  std::string testSeed="d1d1d1d1";
  testTurn2.initMap(2,2,testSeed);
  BOOST_CHECK_EQUAL(testTurn2.getMap().size(),2);
  BOOST_CHECK_EQUAL(testTurn2.getMap()[0].size(),2);
  BOOST_CHECK_EQUAL(testTurn2.getMap()[0][0].getHeight(),1);
  BOOST_CHECK_EQUAL(testTurn2.getMap()[1][1].getTile(),Dirt);
}
