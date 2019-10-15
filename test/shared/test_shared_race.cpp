#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestRace)
{
  Race race {};
	race.setRace(Monster);
	BOOST_CHECK_EQUAL((race.getRace()),Monster);
}
