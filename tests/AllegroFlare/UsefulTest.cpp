

#include <AllegroFlare/Useful.hpp>


#include <gtest/gtest.h>


TEST(UsefulTest, random_string__only_returns_strings_with_the_expected_characters_and_length)
{
   std::string allowed_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

   std::vector<std::string> errors;

   for (int i=0; i<30; i++)
   {
      int length = AllegroFlare::random_int(1, 100);
      std::string val = AllegroFlare::random_string(length);

      ASSERT_EQ(length, val.length());
      ASSERT_EQ(std::string::npos, val.find_first_not_of(allowed_characters));
   }
}


