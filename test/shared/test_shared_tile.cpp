#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestTile)
{
  	for(int i=0;i<50;i++){
      TileFactory testTF {};
      BOOST_CHECK_EQUAL(testTF.getRandomTile().getHeight(),1);
    }
}
