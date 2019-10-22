#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;

BOOST_AUTO_TEST_CASE(TestAdd)
{
  Team testTeam {};
  testTeam.addCharacter();
  BOOST_CHECK_EQUAL(testTeam.getListCharacter().size(),1);
}
