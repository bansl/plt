#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;

BOOST_AUTO_TEST_CASE(TestCharacterFactory)
{
	for(int i=0;i<20;i++){
		Character test {};
		CharacterFactory cf {};
		test=cf.createCharacter();
		JobType jobget;
		jobget=test.getJob().getJob();
		BOOST_CHECK((jobget==Pugilist)||(jobget==Magician)||(jobget==Archer)||(jobget==Swordman));
		RaceType raceget;
		raceget=test.getRace().getRace();
		BOOST_CHECK((raceget==Monster)||(raceget==Demon)||(raceget==Human)||(raceget==Beastman));
		//tests for characters fonctions with random character
		BOOST_CHECK_GT(test.getMaxHP(),0);
	  BOOST_CHECK_GT(test.getMaxMP(),0);
	  BOOST_CHECK_GT(test.getEvade(),0);
	  BOOST_CHECK_GT(test.getAttackPower(),0);
	  BOOST_CHECK_GT(test.getMagicPower(),0);
	  BOOST_CHECK_GT(test.getDefense(),0);
	}
}
