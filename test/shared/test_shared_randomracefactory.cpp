#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestRaceFactory)
{
	for(int i=0;i<10;i++){
		Character test {};
		RandomRaceFactory rrf {};
		// Race testRace;
		// testRace.setRace(rrf.getRandomRace());
		test.getRace().setRace(rrf.getRandomRace());
		bool value=((test.getRace().getRace()==Monster)||(test.getRace().getRace()==Demon)||(test.getRace().getRace()==Human)||(test.getRace().getRace()==Beastman));
		BOOST_CHECK(value);
	}
}
