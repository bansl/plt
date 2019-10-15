#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <vector>

using namespace state;

BOOST_AUTO_TEST_CASE(TestTeam)
{
	Team testTeam {};
	testTeam.characterNumber=0;
	testTeam.listCharacter={};
	BOOST_CHECK_EQUAL(testTeam.characterNumber,testTeam.listCharacter.size());
}
