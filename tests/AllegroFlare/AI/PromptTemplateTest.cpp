
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
   std::string TEMPLATE_CONTENT = "";
   std::vector<std::pair<std::string, std::string>> insertion_variables = {
      { "[[COMPONENT_HEADER_INCLUDE_FILE_PATH]]", "AllegroFlare/ComponentName.hpp" },
      { "[[COMPONENT_TEST_DESCRIPTION_NAME]]", "AllegroFlare_ComponentNameTest" },
      { "[[COMPONENT_CLASS_NAME]]", "AllegroFlare::ComponentName" },
      { "[[COMPONENT_BASENAME_SNAKE_CASE]]", "component_name" },
   };

   AllegroFlare::AI::PromptTemplate templated_file(TEMPLATE_CONTENT, insertion_variables);

   std::string expected_string = "";

   EXPECT_EQ(expected_string, templated_file.generate_content());
}


