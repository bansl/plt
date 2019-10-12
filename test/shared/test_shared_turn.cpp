#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

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
  // TODO
}
