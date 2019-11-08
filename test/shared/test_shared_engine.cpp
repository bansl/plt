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
  testTurn.initMap(10,10,"g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1,g1,g2,g3,g2,g1");
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
  testTurn.getTeams()[0]->getListCharacter()[4]->getPosition().setPos(4,6);
  testTurn.getTeams()[0]->addCharacter();
  testTurn.getTeams()[0]->getListCharacter()[5]->getPosition().setPos(10,10);


  Engine testEngine(testTurn);

  testEngine.getTurn().rotation=(testEngine.getTurn().rotation+1)%4;
  BOOST_CHECK_EQUAL(testEngine.getTurn().rotation,1);
  //testEngine.turnCheckIn();


  TurnDisplay layer(testEngine.getTurn());
  TurnDisplay* ptr_layer=&layer;
  testEngine.getTurn().registerObserver(ptr_layer);
  sf::RenderWindow window;
  layer.initRender(testEngine.getTurn());
  sf::Font font;
  font.loadFromFile("res/COURG___.TTF");
  window.display();

  Defend testDefend(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
  if(testDefend.validate(testEngine.getTurn())){
    std::unique_ptr<Defend> ptr_defend (new Defend(testDefend));
    testEngine.addCommand(move(ptr_defend));
  }
  BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[0]->getStatus(),Defending);


  // Attack testAttack(*testEngine.getTurn().getTeams()[0]->getListCharacter()[1],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],testEngine.getTurn().getCharacterHeight(0,1));
  // if(testAttack.validate(testEngine.getTurn())){
  //   std::unique_ptr<Attack> ptr_attack (new Attack(testAttack));
  //   testEngine.addCommand(move(ptr_attack));
  // }
  // BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[1]->getStatus(),Used);


  // Skill fireStrike {};
  // fireStrike.skillName="fire strike";
  // fireStrike.setEffect(10,0);
  // fireStrike.setMpCost(5);
  // testEngine.getTurn().getTeams()[0]->getListCharacter()[2]->addSkill(fireStrike);
  //
  // std::vector<state::Character> testTargetList;
  // testTargetList.push_back(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
  // std::vector<state::Character> & addrtestTargetList= testTargetList;
  //
  // UseSkill testUseSkill(*testEngine.getTurn().getTeams()[0]->getListCharacter()[2],addrtestTargetList,0);
  // if(testUseSkill.validate(testEngine.getTurn())){
  //   std::unique_ptr<UseSkill> ptr_testUseSkill (new UseSkill(testUseSkill));
  //   testEngine.addCommand(move(ptr_testUseSkill));
  // }
  // BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[2]->getStatus(),Used);


  Item testItem("TestHeal",10,0,3) ;
  testEngine.getTurn().getTeams()[0]->addItem(testItem);
  UseObject testUseItem(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],0,0,*testEngine.getTurn().getTeams()[0]->getListCharacter()[3]);
  if(testUseItem.validate(testEngine.getTurn())){
    std::unique_ptr<UseObject> ptr_testUseItem (new UseObject(testUseItem));
    testEngine.addCommand(move(ptr_testUseItem));
  }
  BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[3]->getStatus(),Used);

  // Attack testAttack2(*testEngine.getTurn().getTeams()[0]->getListCharacter()[5],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],testEngine.getTurn().getCharacterHeight(0,5));
  // if(testAttack2.validate(testEngine.getTurn())){
  //   std::unique_ptr<Attack> ptr_attack2 (new Attack(testAttack2));
  //   testEngine.addCommand(move(ptr_attack2));
  // }
  // BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[5]->getStatus(),Available);

    // Position dest;
    // dest.setPos(2,6);
    // Position & addrDest=dest;
    // Move movetest(*testEngine.getTurn().getTeams()[4]->getListCharacter()[0],addrDest);
    // if(movetest.validate(testEngine.getTurn())){
    //     std::unique_ptr<Move> ptr_movetest (new Move(movetest));
    //     testEngine.addCommand(move(ptr_movetest));
    // }
    // BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[4]->getStatus(),Used);
    if(i!=4){
      Defend testDefend2(*testEngine.getTurn().getTeams()[0]->getListCharacter()[4]);
      if(testDefend2.validate(testEngine.getTurn())){
        std::unique_ptr<Defend> ptr_defend2 (new Defend(testDefend2));
        testEngine.addCommand(move(ptr_defend2));
      }
      BOOST_CHECK_EQUAL(testEngine.getTurn().getTeams()[0]->getListCharacter()[4]->getStatus(),Defending);
    }
    if(i==4){
      testEngine.getTurn().getTeams()[0]->getListCharacter()[4]->setCurrentHP(-100);
    }

    layer.initRender();
    layer.display(window,0);

    EndTurn endturnTest(0);
    if(endturnTest.validate(testEngine.getTurn())){
      std::unique_ptr<EndTurn> ptr_endTestTurn (new EndTurn(endturnTest));
      testEngine.addCommand(move(ptr_endTestTurn));
    }

    // Attack testFailedAttack(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],testEngine.getTurn().getCharacterHeight(0,0));
    // testFailedAttack.validate(testEngine.getTurn());
    Defend testFailedDefend(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
    testFailedDefend.validate(testEngine.getTurn());
    UseObject testFailedUseObject(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],0,1,*testEngine.getTurn().getTeams()[0]->getListCharacter()[0]);
    testFailedUseObject.validate(testEngine.getTurn());
    // UseSkill testFailedUseSkill(*testEngine.getTurn().getTeams()[0]->getListCharacter()[0],addrtestTargetList,1);
    // testFailedUseSkill.validate(testEngine.getTurn());


    testEngine.turnCheckOut();
    BOOST_CHECK(testEngine.isTurnFinished);
    testEngine.getTurn().notifyObservers(testEngine.getTurn(), window);

    testEngine.turnCheckIn();
    window.close();
}
}
