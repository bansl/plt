#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestLevel)
{
  Level testLevel {};
  BOOST_CHECK_EQUAL(testLevel.getLevel(),1);
  testLevel.levelUp(1);
  BOOST_CHECK_EQUAL(testLevel.getLevel(),2);
  testLevel.levelUp(25);
  BOOST_CHECK_EQUAL(testLevel.getLevel(),6);
}
