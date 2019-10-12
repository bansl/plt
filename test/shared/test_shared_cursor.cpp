
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestCursor)
{
  Cursor testCursor {};
  Position dest {};
  dest.setPos(5,3);
  testCursor.cursorMove(dest);
  BOOST_CHECK_EQUAL(testCursor.getPosition().getX(),5);
  BOOST_CHECK_EQUAL(testCursor.getPosition().getY(),3);
}
