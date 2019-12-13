#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/client/render.h"
#include "../../src/shared/ai.h"

using namespace state;
using namespace engine;
using namespace render;
using namespace ai;

BOOST_AUTO_TEST_CASE(testDeepAI)
{
  for(int i=0;i<10;i++){
  Turn testTurn;
  testTurn.initMap(8,8); //squares only
  testTurn.initTeams();
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(3,2);
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[1]->getPosition().setPos(3,3);
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[2]->getPosition().setPos(3,4);
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[3]->getPosition().setPos(5,5);

  testTurn.initTeams();
  testTurn.getTeams()[1]->addCharacter();
  testTurn.getTeams()[1]->getListCharacter()[0]->getPosition().setPos(3,1);
  // === Init Engine ===
  Engine testEngine(testTurn);

  Item testItem("TestHeal",10,0,3) ;
  testEngine.getTurn().getTeams()[0]->addItem(testItem);
  testEngine.getTurn().getTeams()[1]->addItem(testItem);
  // === Init AI ===
  DeepAI testAI(testEngine);

  bool checktestAI=false;
    if(testEngine.turnCheckIn()){
        testAI.runAI();
        checktestAI=true;
      }

      BOOST_CHECK(checktestAI);
    }

  }
