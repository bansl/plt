
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <vector>
#include <iostream>
using namespace state;


BOOST_AUTO_TEST_CASE(TestCharacter)
{
  Character Gilbert {  };
  // Race testRace {};
  // testRace.setRace(Human);
  // Job testJob {};
  // testJob.setJob(Pugilist);
  state::Level testLevel {};
  testLevel.levelUp(2);
  testLevel.levelUp(2);
  Gilbert.getRace().setRace(Human);
  Gilbert.getJob().setJob(Pugilist);
  Gilbert.getLevel().levelUp(2);
  Gilbert.getLevel().levelUp(2);

  BOOST_CHECK_EQUAL(Gilbert.getMaxHP(),60);

  BOOST_CHECK_EQUAL(Gilbert.getMaxMP(),10);

  BOOST_CHECK_EQUAL(Gilbert.getEvade(),30);

  BOOST_CHECK_EQUAL(Gilbert.getAttackPower(),30);

  BOOST_CHECK_EQUAL(Gilbert.getMagicPower(),20);

  BOOST_CHECK_EQUAL(Gilbert.getDefense(),20);

  Gilbert.initHPMP();
  BOOST_CHECK_EQUAL(Gilbert.getCurrentHP(),60);
  BOOST_CHECK_EQUAL(Gilbert.getCurrentMP(),10);
  Gilbert.setCurrentHP(-10);
  Gilbert.setCurrentMP(-5);
  BOOST_CHECK_EQUAL(Gilbert.getCurrentHP(),50);
  BOOST_CHECK_EQUAL(Gilbert.getCurrentMP(),5);

  BOOST_CHECK_EQUAL(Gilbert.getSkillList().size(),0);

  Character Mage {};
  // Job testJob2 {};
  // testJob2.setJob(Magician);
  Mage.getJob().setJob(Magician);
    BOOST_CHECK_EQUAL(Mage.getSkillList().size(),1);
    // BOOST_CHECK_EQUAL(Mage.getSkillList()[0]->getDamage(),10);
    // Mage.getSkillList()[0]->setMpCost(10);
    // Mage.getSkillList()[0]->setEffect(0,5);
    // BOOST_CHECK_EQUAL(Mage.getSkillList()[0]->getDamage(),0);
    // BOOST_CHECK_EQUAL(Mage.getSkillList()[0]->getMpCost(),10);
    // BOOST_CHECK_EQUAL(Mage.getSkillList()[0]->getHeal(),5);

}
