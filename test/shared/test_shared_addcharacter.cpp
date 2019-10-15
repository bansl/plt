#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;

BOOST_AUTO_TEST_CASE(TestAdd)
{
  Team testTeam {};
	testTeam.characterNumber=0;
	testTeam.listCharacter={};
  testTeam.addCharacter();
  BOOST_CHECK_EQUAL(testTeam.characterNumber,1);
}
