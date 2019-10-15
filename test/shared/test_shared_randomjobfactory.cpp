#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;


BOOST_AUTO_TEST_CASE(TestJobFactory)
{
	Character test {};
	Job jobtest {};
	RandomJobFactory rjf {};
	jobtest=rjf.getJob();
	test.job.job=jobtest.job;
	BOOST_CHECK_EQUAL(test.job.job,Pugilist);
}
