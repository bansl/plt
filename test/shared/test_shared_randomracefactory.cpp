#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestRaceFactory)
{
	Character test {};
	Race racetest {};
	RandomRaceFactory rrf {};
	racetest=rrf.getRace();
	test.race.race=racetest.race;
	BOOST_CHECK_EQUAL(test.race.race,Monster);
}
