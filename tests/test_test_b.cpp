

// this test taken from
// http://www.alittlemadness.com/2009/03/31/c-unit-testing-with-boosttest/


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include <boost/test/unit_test.hpp>


int add(int i, int j)
{
   return i + j;
}


BOOST_AUTO_TEST_SUITE(Maths)

BOOST_AUTO_TEST_CASE(universeInOrder)
{
   BOOST_CHECK(add(2, 2) == 4);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Physics)

BOOST_AUTO_TEST_CASE(specialTheory)
{
   int e = 32;
   int m = 2;
   int c = 4;

   BOOST_CHECK(e == m * c * c);
}

BOOST_AUTO_TEST_SUITE_END()


