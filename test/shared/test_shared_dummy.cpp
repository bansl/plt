
#include <boost/test/unit_test.hpp>

// #include "../../src/shared/state/Exemple.h"
#include "../../src/shared/state/Item.h"
#include "../../src/shared/state/Team.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestCharacter)
{
  Character Charles {  };
  Charles.name="Charles";
  Charles.currentHP=24;
  Charles.currentMP=13;
  Charles.xPosition=0;
  Charles.yPosition=0;
  Charles.idCharacter=69;

  Team player {};
  player.listCharacter.push_back(Charles);

  BOOST_CHECK_EQUAL(player.listCharacter[0].idCharacter,69);
  BOOST_CHECK_EQUAL(player.listCharacter[0].name,"Charles");
}

BOOST_AUTO_TEST_CASE(TestHealItem)
{
  Item exheal {  };
  exheal.name="potion";
  exheal.quantity=2;
  // exheal.healthRestoreAmount=42;

  Team player1 {};
  player1.listItems.push_back(exheal);

  BOOST_CHECK_EQUAL((player1.getItems())[0].quantity,2);
}

 BOOST_AUTO_TEST_CASE(TestExemple)
 {
   {
     Exemple ex {};
     BOOST_CHECK_EQUAL(ex.x, 0);
    ex.setX(21);
     BOOST_CHECK_EQUAL(ex.x, 21);
   }

   {
     Exemple ex {};
     ex.setX(21);
     BOOST_CHECK_LE(ex.x, 32); // Less than equal
     BOOST_CHECK_GT(ex.x, 11); // Greater than equl
   }
 }

/* vim: set sw=2 sts=2 et : */
