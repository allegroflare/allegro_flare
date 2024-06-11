
#include <gtest/gtest.h>

#include <AllegroFlare/StringTransformer.hpp>


TEST(AllegroFlare_StringTransformerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::StringTransformer string_transformer;
}


TEST(AllegroFlare_StringTransformerTest, upcase__will_convert_the_string_to_upcase)
{
   std::string text_to_upcase = "hello world!";
   AllegroFlare::StringTransformer string_transformer(text_to_upcase);

   std::string expected_upcased_string = "HELLO WORLD!";
   std::string actual_upcased_string = string_transformer.upcase().get_text();

   EXPECT_EQ(expected_upcased_string, actual_upcased_string);
}


TEST(AllegroFlare_StringTransformerTest, expand__will_inject_spaces_between_each_character)
{
   std::string text_to_upcase = "hello world!";
   AllegroFlare::StringTransformer string_transformer(text_to_upcase);

   std::string expected_expanded_string = "h   e   l   l   o       w   o   r   l   d   !";
   std::string actual_expanded_string = string_transformer.expand().get_text();

   EXPECT_EQ(expected_expanded_string, actual_expanded_string);
}


TEST(AllegroFlare_StringTransformerTest, join_with_commas__will_join_the_string_with_commas)
{
   std::set<std::string> elements = { "foo", "bar", "baz" };
   std::string expected_joined_string = "bar, baz, foo"; // NOTE: The result is sorted because the container is a set
   std::string actual_joined_string = AllegroFlare::StringTransformer::join_with_commas(&elements);

   EXPECT_EQ(expected_joined_string, actual_joined_string);
}


TEST(AllegroFlare_StringTransformerTest, join__will_join_the_string_with_the_interpolation_string)
{
   std::vector<std::string> elements = { "foo", "bar", "baz" };
   std::string expected_joined_string = "foo_+_bar_+_baz"; // NOTE: The result is sorted because the container is a set
   std::string actual_joined_string = AllegroFlare::StringTransformer::join(&elements, "_+_");

   EXPECT_EQ(expected_joined_string, actual_joined_string);
}


TEST(AllegroFlare_StringTransformerTest, remove_non_alphanumeric__will_remove_any_unwanted_characters)
{
   std::vector<std::pair<std::string, std::string>> test_data = {
      { "hello world", "helloworld" },
      { "+54 and me", "54andme" },
   };

   std::string subject, expected;
   for (auto &test_datum : test_data)
   {
      std::tie(subject, expected) = test_datum;
      std::string actual = AllegroFlare::StringTransformer::remove_non_alphanumeric(subject);
      EXPECT_EQ(expected, actual);
   }
}


