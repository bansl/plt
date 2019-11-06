
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <vector>
using namespace state;


BOOST_AUTO_TEST_CASE(TestItem)
{
  Item testItem("TestHeal",10,0,3) ;
  BOOST_CHECK_EQUAL(testItem.getQuantity(),3);
  testItem.modifyQuantity(2);
  BOOST_CHECK_EQUAL(testItem.getQuantity(),5);
  testItem.setQuantity(3);
  BOOST_CHECK_EQUAL(testItem.getQuantity(),3);
  BOOST_CHECK_EQUAL(testItem.getConsumable().getHealth(),10);
  BOOST_CHECK_EQUAL(testItem.getConsumable().getMana(),0);
  testItem.getConsumable().setConsumable(0,10);
  BOOST_CHECK_EQUAL(testItem.getConsumable().getHealth(),0);
  BOOST_CHECK_EQUAL(testItem.getConsumable().getMana(),10);
  Team testTeam{};
  BOOST_CHECK_EQUAL(testTeam.getItems().size(),0);
  testTeam.addItem(testItem);
  BOOST_CHECK_EQUAL(testTeam.getItems().size(),1);
  BOOST_CHECK_EQUAL(testTeam.getItems()[0]->getConsumable().getHealth(),0);
}
