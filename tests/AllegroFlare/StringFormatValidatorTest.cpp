
#include <gtest/gtest.h>

#include <AllegroFlare/StringFormatValidator.hpp>


TEST(AllegroFlare_StringFormatValidatorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::StringFormatValidator string_format_validator;
}


TEST(AllegroFlare_Network2_URLTokenizerTest,
   fits_max_length__will_return_true_if_the_length_is_less_than_or_equal_to_the_number)
{
   std::vector<std::pair<std::string, std::size_t>> test_datas = {
      { "foobar", 7    },
      { "foobar", 100  },
      { "foobar", 9999 },
   };

   for (auto &test_data : test_datas)
   {
      std::string string = test_data.first;
      std::size_t length = test_data.second;

      AllegroFlare::StringFormatValidator string_format_validator(string);
      EXPECT_EQ(true, string_format_validator.fits_max_length(length));
   }
}


TEST(AllegroFlare_Network2_URLTokenizerTest,
   fits_max_length__will_return_false_if_the_length_is_greater_than_the_number)
{
   std::vector<std::pair<std::string, std::size_t>> test_datas = {
      { "foobar", 0 },
      { "foobar", 1 },
      { "foobar", 5 },
   };

   for (auto &test_data : test_datas)
   {
      std::string string = test_data.first;
      std::size_t length = test_data.second;

      AllegroFlare::StringFormatValidator string_format_validator(string);
      EXPECT_EQ(false, string_format_validator.fits_max_length(length));
   }
}


TEST(AllegroFlare_Network2_URLTokenizerTest,
   fits_min_length__will_return_true_if_the_length_is_less_than_or_equal_to_the_number)
{
   std::vector<std::pair<std::string, std::size_t>> test_datas = {
      { "foobar", 0 },
      { "foobar", 1 },
      { "foobar", 5 },
   };

   for (auto &test_data : test_datas)
   {
      std::string string = test_data.first;
      std::size_t length = test_data.second;

      AllegroFlare::StringFormatValidator string_format_validator(string);
      EXPECT_EQ(true, string_format_validator.fits_min_length(length));
   }
}


TEST(AllegroFlare_Network2_URLTokenizerTest,
   fits_min_length__will_return_false_if_the_length_is_greater_than_the_number)
{
   std::vector<std::pair<std::string, std::size_t>> test_datas = {
      { "foobar", 7    },
      { "foobar", 100  },
      { "foobar", 9999 },
   };

   for (auto &test_data : test_datas)
   {
      std::string string = test_data.first;
      std::size_t length = test_data.second;

      AllegroFlare::StringFormatValidator string_format_validator(string);
      EXPECT_EQ(false, string_format_validator.fits_min_length(length));
   }
}


TEST(AllegroFlare_Network2_URLTokenizerTest,
   has_only_numerical_characters__will_return_true_if_the_string_contains_only_numerical_characters)
{
   std::vector<std::string> test_strings = {
      "",
      "0",
      "123",
      "54321",
      "0123456789",
      "4845314804864861561534048643054789465132222311567774887975642313",
   };

   for (auto &test_string : test_strings)
   {
      AllegroFlare::StringFormatValidator string_format_validator(test_string);
      EXPECT_EQ(true, string_format_validator.has_only_numerical_characters());
   }
}


TEST(AllegroFlare_Network2_URLTokenizerTest,
   has_only_numerical_characters__will_return_false_if_any_characters_in_the_string_are_not_numbers)
{
   std::vector<std::string> test_strings = {
      "0.0",
      " 123",
      "123 ",
      "12_543_2345",
      "12,543.00",
      "$5",
   };

   for (auto &test_string : test_strings)
   {
      AllegroFlare::StringFormatValidator string_format_validator(test_string);
      EXPECT_EQ(false, string_format_validator.has_only_numerical_characters());
   }
}


