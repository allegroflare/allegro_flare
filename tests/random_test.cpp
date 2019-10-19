

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Random
#include <boost/test/unit_test.hpp>


#include <allegro_flare/random.h>




using namespace allegro_flare;




BOOST_AUTO_TEST_CASE(gets_the_current_seed)
{
   Random number_generator = Random(123);

   BOOST_CHECK_EQUAL(123, number_generator.get_seed());
}




BOOST_AUTO_TEST_CASE(sets_the_current_seed)
{
   Random number_generator = Random(123);
   number_generator.set_seed(456);

   BOOST_CHECK_EQUAL(456, number_generator.get_seed());
}




BOOST_AUTO_TEST_CASE(only_returns_integers_within_the_bounds_inclusive)
{
   Random number_generator = Random(123);
   const int min_random_num = 1;
   const int max_random_num = 3;

   for (int i=0; i<1000; i++)
   {
      int val = number_generator.get_random_int(min_random_num, max_random_num);

      BOOST_CHECK(val <= max_random_num);
      BOOST_CHECK(val >= min_random_num);
   }
}




BOOST_AUTO_TEST_CASE(only_returns_doubles_within_the_bounds_inclusive)
{
   Random number_generator = Random(123);
   const double min_random_num = 1.0;
   const double max_random_num = 3.0;

   for (int i=0; i<1000; i++)
   {
      double val = number_generator.get_random_double(min_random_num, max_random_num);

      BOOST_CHECK(val <= max_random_num);
      BOOST_CHECK(val >= min_random_num);
   }
}




BOOST_AUTO_TEST_CASE(only_returns_floats_within_the_bounds_inclusive)
{
   Random number_generator = Random(123);
   const float min_random_num = 1.0;
   const float max_random_num = 3.0;

   for (int i=0; i<1000; i++)
   {
      float val = number_generator.get_random_float(min_random_num, max_random_num);

      BOOST_CHECK(val <= max_random_num);
      BOOST_CHECK(val >= min_random_num);
   }
}




BOOST_AUTO_TEST_CASE(returns_an_expected_sequence_of_random_numbers_given_a_seed)
{
   Random number_generator = Random(123456);
   const int min_random_num = 0;
   const int max_random_num = 10;
   std::vector<int> expected_numbers = {1, 10, 2, 1, 8};

   for (int i=0; i<expected_numbers.size(); i++)
   {
      int val = number_generator.get_random_int(min_random_num, max_random_num);

      BOOST_CHECK_EQUAL(expected_numbers[i], val);
   }
}




