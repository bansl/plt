#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestJobFactory)
{
	Character test {};
	RandomJobFactory rjf {};
	Job testJob;
	testJob.setJob(rjf.getRandomJob());
	test.setJob(testJob);
	bool value=((test.getJob().getJob()==Archer)||(test.getJob().getJob()==Pugilist)||(test.getJob().getJob()==Swordman)||(test.getJob().getJob()==Magician));
	BOOST_CHECK(value);
}
