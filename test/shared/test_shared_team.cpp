#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <vector>

using namespace state;

BOOST_AUTO_TEST_CASE(TestTeam)
{
	Team testTeam ;
    BOOST_CHECK_EQUAL(testTeam.getListCharacter().size(),0);
    testTeam.addCharacter();
	BOOST_CHECK_EQUAL(testTeam.getListCharacter().size(),1);
}

