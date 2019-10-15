#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestJob)
{
  Job job {};
	job.setJob(Archer);
	BOOST_CHECK_EQUAL((job.getJob()),Archer);
}
