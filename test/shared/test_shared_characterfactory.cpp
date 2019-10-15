#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;

BOOST_AUTO_TEST_CASE(TestCharacterFactory)
{
	Character test {};
	CharacterFactory cf {};
	test=cf.createCharacter();
	JobType jobget;
	jobget=test.getJob().getJob();
	BOOST_CHECK((jobget==Pugilist)||(jobget==Magician)||(jobget==Archer)||(jobget==Swordman));
	RaceType raceget;
	raceget=test.getRace().getRace();
	BOOST_CHECK((raceget==Monster)||(raceget==Demon)||(raceget==Human)||(raceget==Beastman));
}
