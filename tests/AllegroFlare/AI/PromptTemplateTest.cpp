
#include <gtest/gtest.h>

#include <AllegroFlare/AI/PromptTemplate.hpp>


TEST(AllegroFlare_AI_PromptTemplateTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AI::PromptTemplate templated_file;
}


TEST(AllegroFlare_AI_PromptTemplateTest,
   generate_content__when_object_is_created_with_default_arguments__returns_the_expected_filled_content)
{
   AllegroFlare::AI::PromptTemplate templated_file;
   std::string expected_string = "Hello, World!";
   EXPECT_EQ(expected_string, templated_file.generate_content());
}


TEST(AllegroFlare_AI_PromptTemplateTest,
   generate_content__returns_the_expected_filled_content)
{
   std::string template_content = "A rainbow-coloured butterfly flying across [location] during [time_of_day]";
   std::vector<std::pair<std::string, std::string>> insertion_variables = {
      { "[location]", "a field of flowers" },
      { "[time_of_day]", "sunset" },
   };

   AllegroFlare::AI::PromptTemplate templated_file(template_content, insertion_variables);
   std::string expected_string = "A rainbow-coloured butterfly flying across a field of flowers during sunset";
   EXPECT_EQ(expected_string, templated_file.generate_content());
}


