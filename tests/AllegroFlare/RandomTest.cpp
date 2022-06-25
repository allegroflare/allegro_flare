

#include <gtest/gtest.h>

#include <AllegroFlare/Random.hpp>


TEST(AllegroFlare_RandomTest, gets_the_current_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);

   ASSERT_EQ(123, number_generator.get_seed());
}


TEST(AllegroFlare_RandomTest, sets_the_current_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);
   number_generator.set_seed(456);

   ASSERT_EQ(456, number_generator.get_seed());
}


TEST(AllegroFlare_RandomTest, get_random_bool__returns_random_booleans)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);
   
   int true_count = 0;
   int false_count = 0;
   int num_checks = 1000;
   for (int i=0; i<num_checks; i++)
   {
      bool val = number_generator.get_random_bool();
      val ? true_count++ : false_count++;
   }

   ASSERT_GE(true_count, num_checks/3); // just a sanity check
   ASSERT_GE(false_count, num_checks/3); // just a sanity check
}


TEST(AllegroFlare_RandomTest, get_random_int__only_returns_integers_within_the_bounds_inclusive)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);
   const int min_random_num = 1;
   const int max_random_num = 3;

   bool hit_1 = false;
   bool hit_2 = false;
   bool hit_3 = false;

   for (int i=0; i<1000; i++)
   {
      int val = number_generator.get_random_int(min_random_num, max_random_num);
      //std::cout << val << std::endl;

      ASSERT_TRUE(val <= max_random_num);
      ASSERT_TRUE(val >= min_random_num);

      if (val == 1) hit_1 = true;
      if (val == 2) hit_2 = true;
      if (val == 3) hit_3 = true;
   }

   ASSERT_EQ(true, hit_1);
   ASSERT_EQ(true, hit_2);
   ASSERT_EQ(true, hit_3);
}


TEST(AllegroFlare_RandomTest, get_random_double__only_returns_doubles_within_the_bounds_inclusive)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);
   const double min_random_num = 1.0;
   const double max_random_num = 3.0;

   for (int i=0; i<1000; i++)
   {
      double val = number_generator.get_random_double(min_random_num, max_random_num);

      ASSERT_TRUE(val <= max_random_num);
      ASSERT_TRUE(val >= min_random_num);
   }
}


TEST(AllegroFlare_RandomTest, get_random_float__only_returns_floats_within_the_bounds_inclusive)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);
   const float min_random_num = 1.0;
   const float max_random_num = 3.0;

   for (int i=0; i<1000; i++)
   {
      float val = number_generator.get_random_float(min_random_num, max_random_num);

      ASSERT_TRUE(val <= max_random_num);
      ASSERT_TRUE(val >= min_random_num);
   }
}


TEST(RandomTest, get_random_int__returns_a_repeatable_sequence_of_random_numbers_given_a_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);
   const int min_random_num = 0;
   const int max_random_num = 10;

   std::vector<int> expected_numbers = {6, 4, 1, 0, 2};
   std::vector<int> actual_numbers;

   for (int i=0; i<expected_numbers.size(); i++)
   {
      actual_numbers.push_back(number_generator.get_random_int(min_random_num, max_random_num));
   }

   ASSERT_EQ(expected_numbers, actual_numbers);
}


TEST(RandomTest, get_random_bool__returns_a_repeatable_sequence_of_random_booleans_given_a_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);

   std::vector<bool> expected_repeatable_results = { true, false, false, true, false, true, true };
   std::vector<bool> actual_results;
   for (int i=0; i<expected_repeatable_results.size(); i++)
   {
      actual_results.push_back(number_generator.get_random_bool());
   }

   ASSERT_EQ(expected_repeatable_results, actual_results);
}


TEST(RandomTest, roll_dice__returns_a_repeatable_sequence_of_random_rolls_given_a_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);

   std::vector<int> expected_repeatable_results = { 7, 11, 5, 12, 7, 11, 10 };
   std::vector<int> actual_results;
   for (int i=0; i<expected_repeatable_results.size(); i++)
   {
      actual_results.push_back(number_generator.roll_dice(2, 6));
   }

   ASSERT_EQ(expected_repeatable_results, actual_results);
}


