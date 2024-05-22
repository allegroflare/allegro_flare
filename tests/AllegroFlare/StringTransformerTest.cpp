
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


