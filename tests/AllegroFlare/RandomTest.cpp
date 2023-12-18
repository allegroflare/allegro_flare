

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/Random.hpp>

#include <algorithm>
#include <iomanip>
#include <AllegroFlare/Testing/CustomComparison.hpp>


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


TEST(AllegroFlare_RandomTest, get_random_sign__returns_the_number_1_randomly_either_positive_or_negative)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);

   int positive_one_count = 0;
   int negative_one_count = 0;
   int num_checks = 1000;
   for (int i=0; i<num_checks; i++)
   {
      int val = number_generator.get_random_sign();
      (val == 1) ? positive_one_count++ : negative_one_count++;
   }

   ASSERT_GE(positive_one_count, num_checks/3); // just a sanity check
   ASSERT_GE(negative_one_count, num_checks/3); // just a sanity check
}


TEST(AllegroFlare_RandomTest, get_random_sign__will_return_repeatable_values_given_the_same_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);

   std::vector<int> randomly_generated_signs;
   for (int i=0; i<9; i++) randomly_generated_signs.push_back(number_generator.get_random_sign());

   std::vector<int> expected_randomly_generated_signs = { -1, 1, -1, 1, -1, 1, 1, 1, 1 };
   EXPECT_EQ(expected_randomly_generated_signs, randomly_generated_signs);
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


TEST(AllegroFlare_RandomTest, get_random_letter__returns_a_random_uppercase_character)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);

   std::string expected_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   std::vector<unsigned char> errors;

   for (int i=0; i<30; i++)
   {
      unsigned char random_letter = number_generator.get_random_letter();

      std::size_t pos = expected_characters.find(random_letter);
      if (pos == std::string::npos) errors.push_back(random_letter);
   }

   EXPECT_THAT(errors, testing::IsEmpty());
}


TEST(AllegroFlare_RandomTest, get_random_letter__with_lowercase_set_to_true__returns_a_random_uppercase_character)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);

   std::string expected_characters = "abcdefghijklmnopqrstuvwxyz";
   std::vector<unsigned char> errors;

   for (int i=0; i<30; i++)
   {
      unsigned char random_letter = number_generator.get_random_letter(true);

      std::size_t pos = expected_characters.find(random_letter);
      if (pos == std::string::npos) errors.push_back(random_letter);
   }

   EXPECT_THAT(errors, testing::IsEmpty());
}


TEST(AllegroFlare_RandomTest, get_random_letter__will_return_repeatable_values_given_the_same_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);

   std::vector<unsigned char> randomly_generated_characters;
   for (int i=0; i<9; i++) randomly_generated_characters.push_back(number_generator.get_random_letter());

   std::vector<unsigned char> expected_randomly_generated_characters = { 'A', 'O', 'J', 'Y', 'X', 'I', 'A', 'D', 'T' };
   EXPECT_EQ(expected_randomly_generated_characters, randomly_generated_characters);
}


TEST(AllegroFlare_RandomTest,
   get_random_letter__with_lowercase_set_to_true__would_return_the_same_alphabetic_character_as_uppercase)
{
   AllegroFlare::Random number_generator;

   number_generator.set_seed(123);
   std::vector<unsigned char> generated_uppercase_characters;
   for (int i=0; i<9; i++) generated_uppercase_characters.push_back(number_generator.get_random_letter());

   number_generator.set_seed(123);
   std::vector<unsigned char> generated_lowercase_characters;
   for (int i=0; i<9; i++) generated_lowercase_characters.push_back(number_generator.get_random_letter(true));

   std::vector<unsigned char> expected_generated_uppercase_characters = { 'A', 'O', 'J', 'Y', 'X', 'I', 'A', 'D', 'T' };
   std::vector<unsigned char> expected_generated_lowercase_characters = { 'a', 'o', 'j', 'y', 'x', 'i', 'a', 'd', 't' };

   EXPECT_EQ(expected_generated_uppercase_characters, generated_uppercase_characters);
   EXPECT_EQ(expected_generated_lowercase_characters, generated_lowercase_characters);
}


TEST(AllegroFlare_RandomTest,
   get_random_letter_or_number__returns_a_random_uppercase_lowercase_or_number_character)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);

   std::string expected_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
   std::vector<unsigned char> errors;

   for (int i=0; i<30; i++)
   {
      unsigned char random_letter_or_number = number_generator.get_random_letter_or_number();

      std::size_t pos = expected_characters.find(random_letter_or_number);
      if (pos == std::string::npos) errors.push_back(random_letter_or_number);
   }

   EXPECT_THAT(errors, testing::IsEmpty());
}


TEST(AllegroFlare_RandomTest, get_random_letter_or_number__returns_repeatable_values_given_the_same_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);

   std::vector<unsigned char> randomly_generated_characters;
   for (int i=0; i<9; i++) randomly_generated_characters.push_back(number_generator.get_random_letter_or_number());

   std::vector<unsigned char> expected_randomly_generated_characters = { 'M', 'f', 'q', '2', 'Q', 'R', 'm', 'Z', 't' };
   EXPECT_EQ(expected_randomly_generated_characters, randomly_generated_characters);
}


TEST(AllegroFlare_RandomTest,
   get_random_string__returns_an_string_of_the_expected_length_containing_random_letters_or_numbers)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);

   std::string expected_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
   std::vector<std::string> errors;

   for (int i=0; i<30; i++)
   {
      int length = number_generator.get_random_int(1, 100);

      std::string random_string = number_generator.get_random_string(length);

      ASSERT_EQ(length, random_string.length());
      std::size_t pos = random_string.find_first_not_of(expected_characters);
      if (pos != std::string::npos)
      {
         std::stringstream error;
         error << "pos " << pos << " in \"" << random_string << "\""; 
         errors.push_back(error.str());
      }
   }

   EXPECT_THAT(errors, testing::IsEmpty());
}


TEST(AllegroFlare_RandomTest, get_random_string__returns_repeatable_values_given_the_same_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);

   std::vector<std::string> randomly_generated_strings;
   for (int i=0; i<4; i++) randomly_generated_strings.push_back(number_generator.get_random_string(10));

   std::vector<std::string> expected_randomly_generated_strings = {
         "oO0SW2wd3J",
         "s0okvpJjk2",
         "OV5WiOgRV7",
         "KY6wcooVfS"
      };
   EXPECT_EQ(expected_randomly_generated_strings, randomly_generated_strings);
}


TEST(AllegroFlare_RandomTest,
   get_random_string__could_potentially_return_inappropriate_content_and_is_not_guaranteed_to_filter_unsafe_language)
{
   AllegroFlare::Random number_generator;

   number_generator.set_seed(3919617);

   std::string expected_unfiltered_profanity = "fuck";
   std::string randomly_generated_string = number_generator.get_random_string(4);
   EXPECT_EQ(expected_unfiltered_profanity, randomly_generated_string);
}


TEST(AllegroFlare_RandomTest, get_random_float__only_returns_floats_within_the_bounds_inclusive)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);
   const float min_random_num = 3.0;
   const float max_random_num = 5.0;

   for (int i=0; i<1000; i++)
   {
      float val = number_generator.get_random_float(min_random_num, max_random_num);

      ASSERT_TRUE(val <= max_random_num);
      ASSERT_TRUE(val >= min_random_num);
   }
}


TEST(AllegroFlare_RandomTest, get_random_element__returns_a_random_element_from_the_vector)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);
   std::vector<int> elements_to_pick_from = { 18, 42, 256, 9, 11 };

   for (int i=0; i<20; i++)
   {
      int random_element = number_generator.get_random_element(elements_to_pick_from);
      EXPECT_THAT(elements_to_pick_from, testing::Contains(random_element));
   }
}


TEST(AllegroFlare_RandomTest, get_random_element__returns_a_repeatable_selection_of_elements_given_a_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);
   std::vector<int> elements_to_pick_from = { 18, 42, 256, 9, 11 };

   std::vector<int> expected_randomly_selected_elements = { 11, 9, 9, 42, 9, 11, 9, 42, 18, 9, 42, 11, 11, 256 };
   std::vector<int> randomly_selected_elements;

   for (int i=0; i<expected_randomly_selected_elements.size(); i++)
   {
      randomly_selected_elements.push_back(number_generator.get_random_element(elements_to_pick_from));
   }

   EXPECT_EQ(expected_randomly_selected_elements, randomly_selected_elements);
}


TEST(AllegroFlare_RandomTest, shuffle_elements__will_randomize_the_order_of_the_elements_in_the_vector)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);
   std::vector<int> elements = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
   std::vector<int> sorted_elements = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

   number_generator.shuffle_elements(elements);

   EXPECT_NE(elements, sorted_elements);
   EXPECT_THAT(elements, testing::WhenSorted(testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11)));
}


TEST(AllegroFlare_RandomTest, shuffle_elements__will_produce_a_reproducable_shuffling_given_the_same_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456+7);
   std::vector<int> elements = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

   std::vector<std::vector<int>> expected_shuffles = {
      { 6, 3, 9, 10, 2, 5, 1, 4, 8, 7 },
      { 5, 9, 6, 4, 2, 10, 1, 8, 3, 7 },
      { 6, 3, 8, 7, 9, 1, 4, 5, 2, 10 },
   };

   for (auto &expected_shuffle : expected_shuffles)
   {
      number_generator.shuffle_elements(elements);
      EXPECT_EQ(expected_shuffle, elements);
   }
}


TEST(AllegroFlare_RandomTest, get_random_int__returns_a_repeatable_sequence_of_random_numbers_given_a_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);
   const int min_random_num = 0;
   const int max_random_num = 10;

   std::vector<int> expected_numbers = { 5, 5, 6, 3, 5 };
   std::vector<int> actual_numbers;

   for (int i=0; i<expected_numbers.size(); i++)
   {
      actual_numbers.push_back(number_generator.get_random_int(min_random_num, max_random_num));
   }

   ASSERT_EQ(expected_numbers, actual_numbers);
}


TEST(AllegroFlare_RandomTest, get_random_float__returns_a_repeatable_sequence_of_random_numbers_given_a_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);
   const float min_random_num = 3.0;
   const float max_random_num = 5.0;

   int num_numbers = 5;
   std::string expected_numbers = "3.510779619216918945312500 "
                                  "3.349828720092773437500000 "
                                  "3.559968233108520507812500 "
                                  "4.295793533325195312500000 "
                                  "3.418380260467529296875000 ";
   std::stringstream actual_numbers;
   actual_numbers << std::fixed << std::setprecision(24);

   for (int i=0; i<num_numbers; i++)
   {
      float value = number_generator.get_random_float(min_random_num, max_random_num);
      actual_numbers << value << " ";
   }
  
   ASSERT_EQ(expected_numbers, actual_numbers.str());
}


TEST(AllegroFlare_RandomTest, get_random_double__returns_a_repeatable_sequence_of_random_numbers_given_a_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);
   const double min_random_num = 3.0;
   const double max_random_num = 5.0;

   int num_numbers = 5;
   std::string expected_numbers = "3.427699877980095344298661075299605727195739746094 "
                                  "4.440386506132871780039295117603614926338195800781 "
                                  "3.121539735729233377981017838465049862861633300781 "
                                  "4.228234231757985739363903121557086706161499023438 "
                                  "4.513077179322269927297384128905832767486572265625 ";
   std::stringstream actual_numbers;
   actual_numbers << std::fixed << std::setprecision(48);

   for (int i=0; i<num_numbers; i++)
   {
      double value = number_generator.get_random_double(min_random_num, max_random_num);
      actual_numbers << value << " ";
   }
  
   ASSERT_EQ(expected_numbers, actual_numbers.str());
}

TEST(AllegroFlare_RandomTest, get_random_bool__returns_a_repeatable_sequence_of_random_booleans_given_a_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);

   std::vector<bool> expected_repeatable_results = { true, false, true, false, true, true, false };
   std::vector<bool> actual_results;
   for (int i=0; i<expected_repeatable_results.size(); i++)
   {
      actual_results.push_back(number_generator.get_random_bool());
   }

   ASSERT_EQ(expected_repeatable_results, actual_results);
}


TEST(AllegroFlare_RandomTest, roll_dice__returns_a_repeatable_sequence_of_random_rolls_given_a_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);

   std::vector<int> expected_repeatable_results = { 4, 9, 7, 12, 3, 8, 2 };
   std::vector<int> actual_results;
   for (int i=0; i<expected_repeatable_results.size(); i++)
   {
      actual_results.push_back(number_generator.roll_dice(6, 2));
   }

   ASSERT_EQ(expected_repeatable_results, actual_results);
}


TEST(AllegroFlare_RandomTest, get_one_in_chance__returns_a_repeatable_sequence_of_random_values_given_a_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);

   std::vector<bool> expected_repeatable_results = { false, false, false, true, false, false, false, true };
   std::vector<bool> actual_results;
   for (int i=0; i<expected_repeatable_results.size(); i++)
   {
      actual_results.push_back(number_generator.get_one_in_chance(3));
   }

   ASSERT_EQ(expected_repeatable_results, actual_results);
}


TEST(AllegroFlare_RandomTest, 
   get_random_color__returns_a_repeatable_sequence_of_random_values_given_a_seed)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123456);

   std::vector<ALLEGRO_COLOR> expected_repeatable_results = {
      AllegroFlare::Color::DeepSkyBlue,
      AllegroFlare::Color::Chartreuse,
      AllegroFlare::Color::Tan,
      AllegroFlare::Color::Salmon,
   };
   std::vector<ALLEGRO_COLOR> actual_results;
   for (int i=0; i<expected_repeatable_results.size(); i++)
   {
      actual_results.push_back(number_generator.get_random_color());
   }

   ASSERT_EQ(expected_repeatable_results, actual_results);
}


TEST(AllegroFlare_RandomTest,
   get_random_color_exhaustive__will_exhaust_the_full_list_of_possible_colors_before_repeating_one_again)
{
   AllegroFlare::Random number_generator = AllegroFlare::Random(123);

   // get a copy of the color palette
   std::vector<ALLEGRO_COLOR> color_palette = number_generator.get_source_color_palette();

   int num_tries = 10;
   while (num_tries > 0)
   {
      // get_random_color from the generator
      ALLEGRO_COLOR random_color = number_generator.get_random_color_exhaustive();

      // find color in our copy of the palette
      std::vector<ALLEGRO_COLOR>::iterator found_color_position =
         std::find(color_palette.begin(), color_palette.end(), random_color);
      
      // assert the color was color found
      ASSERT_NE(color_palette.end(), found_color_position);

      // remove color from our list
      color_palette.erase(found_color_position);

      // if list is empty
      if (color_palette.empty())
      {
         // build a new copy
         color_palette = number_generator.get_source_color_palette();

         // decrement num_tries
         num_tries--;
      }
   }
}


