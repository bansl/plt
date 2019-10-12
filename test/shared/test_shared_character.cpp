#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestCharacter)
{
  Character Gilbert {  };
  Race testRace {};
  testRace.race=Human;
  Job testJob {};
  testJob.job=Pugilist;
  Level testLevel {};
  testLevel.level=1;
  int maxHP=Gilbert.getMaxHP(testRace,testJob,testLevel);

  BOOST_CHECK_EQUAL(maxHP,55);
}
