#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;

BOOST_AUTO_TEST_CASE(TestCharacterFactory)
{
	Character test {};
	CharacterFactory cf {};
	test=cf.getCharacter();
	BOOST_CHECK_EQUAL(test.race.race,Monster);
  BOOST_CHECK_EQUAL(test.job.job,Pugilist);
}
