#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestTile)
{
  	for(int i=0;i<50;i++){
      TileFactory testTF {};
      int height=testTF.getRandomTile().getHeight();
      bool test= ((height==1) || (height==2) || (height==3));
      BOOST_CHECK( test );
    }
}
