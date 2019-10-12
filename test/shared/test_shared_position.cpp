#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestPosition)
{
  Entity testEntity {};
  Position testEntityPos= testEntity.getPosition();
  testEntityPos.setX(5);
  BOOST_CHECK_EQUAL(testEntityPos.getX(),5);
  testEntityPos.setY(51);
  BOOST_CHECK_EQUAL(testEntityPos.getY(),51);
  testEntityPos.setPos(23,21);
  BOOST_CHECK_EQUAL(testEntityPos.getX(),23);
  BOOST_CHECK_EQUAL(testEntityPos.getY(),21);
  Position anotherPos= {};
  anotherPos.setPos(24,25);
  int dist=testEntityPos.distanceBetween(testEntityPos,anotherPos);
  BOOST_CHECK_EQUAL(dist,5);
  
}
