
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestCharacter)
{
  Character Gilbert {  };
  Race testRace {};
  testRace.setRace(Human);
  Job testJob {};
  testJob.setJob(Pugilist);
  state::Level testLevel {};
  testLevel.level=2;
  Gilbert.setRace(testRace);
  Gilbert.setJob(testJob);
  Gilbert.level=testLevel;

  BOOST_CHECK_EQUAL(Gilbert.getMaxHP(testRace,testJob,testLevel),60);

  BOOST_CHECK_EQUAL(Gilbert.getMaxMP(testRace,testJob,testLevel),10);

  BOOST_CHECK_EQUAL(Gilbert.getEvade(testRace,testJob,testLevel),30);

  BOOST_CHECK_EQUAL(Gilbert.getAttackPower(testRace,testJob,testLevel),30);

  BOOST_CHECK_EQUAL(Gilbert.getMagicPower(testRace,testJob,testLevel),20);

  BOOST_CHECK_EQUAL(Gilbert.getDefense(testRace,testJob,testLevel),20);

  Gilbert.initHPMP(testRace,testJob,testLevel);
  BOOST_CHECK_EQUAL(Gilbert.getCurrentHP(),60);
  BOOST_CHECK_EQUAL(Gilbert.getCurrentMP(),10);

//   BOOST_CHECK_EQUAL( (int) Gilbert.getSkillList(testJob,testLevel).size()==0,1);

}
