#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/client/render.h"

using namespace state;
using namespace engine;
using namespace render;

BOOST_AUTO_TEST_CASE(TestEngine)
{
  for(int i=0;i<5;i++){
  Turn testTurn{};
  testTurn.initMap(6,6,"g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g3");
  testTurn.initTeams();
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(2,5);
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[1]->getPosition().setPos(3,5);
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[2]->getPosition().setPos(4,5);
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[3]->getPosition().setPos(5,5);
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[4]->getPosition().setPos(4,3);
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[5]->getPosition().setPos(2,4);
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[6]->getPosition().setPos(1,4);

  Engine testEngine(testTurn);
  testEngine.getTurn().rotation=(testEngine.getTurn().rotation+1)%4;
  BOOST_CHECK_EQUAL(testEngine.getTurn().rotation,1);
  testEngine.turnCheckIn();
  sf::RenderWindow window;
  window.display();

  Defend testDefend(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
  if(testDefend.validate(testEngine.getTurn())){
    std::unique_ptr<Defend> ptr_defend (new Defend(testDefend));
    testEngine.addCommand(move(ptr_defend));
  }
  BOOST_CHECK(testEngine.getTurn().getTeams()[0]->getListCharacter()[0]->getStatus()==Defending);


  //Attack testAttack(*testEngine.getTurn().getTeams()[0]->getListCharacter()[1],*testTurn.getTeams()[0]->getListCharacter()[0],testTurn.getCharacterHeight(0,1));
  // if(testAttack.validate(testEngine.getTurn())){
  //   std::unique_ptr<Attack> ptr_attack (new Attack(testAttack));
  //   testEngine.addCommand(move(ptr_attack));
  // }
  // BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[1]->getStatus(),Attacking);


  Skill fireStrike {};
  fireStrike.skillName="fire strike";
  fireStrike.setEffect(10,0);
  fireStrike.setMpCost(5);
  fireStrike.setRange(10);
  testEngine.getTurn().getTeams()[0]->getListCharacter()[2]->addSkill(fireStrike);
  testEngine.getTurn().getTeams()[0]->getListCharacter()[2]->getSkillList()[0]->setRange(10);

  UseSkill testUseSkill(*testEngine.getTurn().getTeams()[0]->getListCharacter()[2],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],0,0);
 if(testUseSkill.validate(testEngine.getTurn())){
   std::unique_ptr<UseSkill> ptr_testUseSkill (new UseSkill(testUseSkill));
   testEngine.addCommand(move(ptr_testUseSkill));
 }
 BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[2]->getStatus(),Attacking);


  Item testItem("TestHeal",10,0,3) ;
  testEngine.getTurn().getTeams()[0]->addItem(testItem);
  UseObject testUseItem(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],0,0,*testEngine.getTurn().getTeams()[0]->getListCharacter()[3]);
  if(testUseItem.validate(testEngine.getTurn())){
    std::unique_ptr<UseObject> ptr_testUseItem (new UseObject(testUseItem));
    testEngine.addCommand(move(ptr_testUseItem));
  }
 BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[3]->getStatus(),UsingObj);

  Attack testAttack2(*testEngine.getTurn().getTeams()[0]->getListCharacter()[5],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
  if(testAttack2.validate(testEngine.getTurn())){
    std::unique_ptr<Attack> ptr_attack2 (new Attack(testAttack2));
    testEngine.addCommand(move(ptr_attack2));
  }
  BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[5]->getStatus(),Attacking);

    Position dest;
    dest.setPos(3,2);
    Move movetest(*testEngine.getTurn().getTeams()[0]->getListCharacter()[4],dest);
    if(movetest.validate(testEngine.getTurn())){
      BOOST_CHECK_GT(movetest.getPathToDest().size(),0);
      BOOST_CHECK_EQUAL(movetest.getCharacter().getAttackPower(),testEngine.getTurn().getTeams()[0]->getListCharacter()[4]->getAttackPower());
        std::unique_ptr<Move> ptr_movetest (new Move(movetest));
        testEngine.addCommand(move(ptr_movetest));
    }
    BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[4]->getStatus(),Moving);

    if(i!=4){
      Defend testDefend2(*testEngine.getTurn().getTeams()[0]->getListCharacter()[6]);
      if(testDefend2.validate(testEngine.getTurn())){
        std::unique_ptr<Defend> ptr_defend2 (new Defend(testDefend2));
        testEngine.addCommand(move(ptr_defend2));
      }
      BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[6]->getStatus(),Defending);
    }
    if(i==4){
      testEngine.getTurn().getTeams()[0]->getListCharacter()[4]->setCurrentHP(-100);
    }
    //
    // layer.initRender();
    // layer.display(window,0);

    EndTurn endturnTest(0);
    if(endturnTest.validate(testEngine.getTurn())){
      std::unique_ptr<EndTurn> ptr_endTestTurn (new EndTurn(endturnTest));
      testEngine.addCommand(move(ptr_endTestTurn));
    }

    Attack testFailedAttack(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
    testFailedAttack.validate(testEngine.getTurn());
    Defend testFailedDefend(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
    testFailedDefend.validate(testEngine.getTurn());
    UseObject testFailedUseObject(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],0,1,*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
    testFailedUseObject.validate(testEngine.getTurn());
    UseSkill testFailedUseSkill(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],2,0);
    testFailedUseSkill.validate(testEngine.getTurn());


    testEngine.turnCheckOut();
    BOOST_CHECK(!testEngine.isTurnFinished);
    testEngine.getTurn().notifyObservers(testEngine.getTurn(), window,fullRender);
    testEngine.updateDisplay(window);
    testEngine.turnCheckIn();
    testEngine.updateDisplay(window);
    window.close();
}

Turn testTurn{};
testTurn.initMap(6,6,"g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g3");
testTurn.initTeams();
testTurn.getTeams()[0]->addCharacter();
testTurn.getTeams()[0]->getListCharacter()[0]->getPosition().setPos(2,5);

Engine testEngine(testTurn);
testEngine.getTurn().rotation=(testEngine.getTurn().rotation+1)%4;
BOOST_CHECK_EQUAL(testEngine.getTurn().rotation,1);
testEngine.turnCheckIn();
sf::RenderWindow window;


  TurnDisplay layer(testEngine.getTurn());
  TurnDisplay* ptr_layer=&layer;
  testEngine.getTurn().registerObserver(ptr_layer);
  layer.initRender(testEngine.getTurn(),fullRender);
  layer.initRender();
  layer.getTilesets();
  layer.getDrawmaps();
  layer.getDrawchars();

window.display();

Defend testDefend(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
if(testDefend.validate(testEngine.getTurn())){
  std::unique_ptr<Defend> ptr_defend (new Defend(testDefend));
  testEngine.addCommand(move(ptr_defend));
}
BOOST_CHECK(testEngine.getTurn().getTeams()[0]->getListCharacter()[0]->getStatus()==Defending);

  testEngine.turnCheckOut();
  BOOST_CHECK(!testEngine.isTurnFinished);
  testEngine.getTurn().notifyObservers(testEngine.getTurn(), window,fullRender);
  testEngine.updateDisplay(window);
  testEngine.turnCheckIn();
  testEngine.updateDisplay(window);
  layer.display(window,0);
  window.close();
}
