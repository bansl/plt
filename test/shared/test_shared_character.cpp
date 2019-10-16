
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <vector>
using namespace state;


BOOST_AUTO_TEST_CASE(TestCharacter)
{
  Character Gilbert {  };
  Race testRace {};
  testRace.setRace(Human);
  Job testJob {};
  testJob.setJob(Pugilist);
  state::Level testLevel {};
  testLevel.levelUp(2);
  testLevel.levelUp(2);
  Gilbert.setRace(testRace);
  Gilbert.setJob(testJob);

  BOOST_CHECK_EQUAL(Gilbert.getMaxHP(Gilbert.getRace(),Gilbert.getJob(),testLevel),60);

  BOOST_CHECK_EQUAL(Gilbert.getMaxMP(Gilbert.getRace(),Gilbert.getJob(),testLevel),10);

  BOOST_CHECK_EQUAL(Gilbert.getEvade(Gilbert.getRace(),Gilbert.getJob(),testLevel),30);

  BOOST_CHECK_EQUAL(Gilbert.getAttackPower(Gilbert.getRace(),Gilbert.getJob(),testLevel),30);

  BOOST_CHECK_EQUAL(Gilbert.getMagicPower(Gilbert.getRace(),Gilbert.getJob(),testLevel),20);

  BOOST_CHECK_EQUAL(Gilbert.getDefense(Gilbert.getRace(),Gilbert.getJob(),testLevel),20);

  Gilbert.initHPMP(Gilbert.getRace(),Gilbert.getJob(),testLevel);
  BOOST_CHECK_EQUAL(Gilbert.getCurrentHP(),60);
  BOOST_CHECK_EQUAL(Gilbert.getCurrentMP(),10);
  Gilbert.setCurrentHP(-10);
  Gilbert.setCurrentMP(-5);
  BOOST_CHECK_EQUAL(Gilbert.getCurrentHP(),50);
  BOOST_CHECK_EQUAL(Gilbert.getCurrentMP(),5);

  BOOST_CHECK_EQUAL(Gilbert.getSkillList(Gilbert.getJob(),testLevel).size(),0);

  Character Mage {};
  Job testJob2 {};
  testJob2.setJob(Magician);
  Mage.setJob(testJob2);
    BOOST_CHECK_EQUAL(Mage.getSkillList(Mage.getJob(),Mage.getLevel()).size(),1);
//   BOOST_CHECK_EQUAL( (int) Gilbert.getSkillList(testJob,testLevel).size()==0,1);

}
