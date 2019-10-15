#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestRaceFactory)
{
	Character test {};
	RandomRaceFactory rrf {};
	Race testRace;
	testRace.setRace(rrf.getRandomRace());
	test.setRace(testRace);
	bool value=((test.getRace().getRace()==Monster)||(test.getRace().getRace()==Demon)||(test.getRace().getRace()==Human)||(test.getRace().getRace()==Beastman));
	BOOST_CHECK(value);
}
