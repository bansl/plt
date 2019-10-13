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
  //TODO
}
