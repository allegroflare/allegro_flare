
#include <gtest/gtest.h>

#include <AllegroFlare/AI/PromptTemplateYAMLLoader.hpp>


TEST(AllegroFlare_AI_PromptTemplateYAMLLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AI::PromptTemplateYAMLLoader prompt_template_yamlloader;
}


TEST(AllegroFlare_AI_PromptTemplateYAMLLoaderTest, load_yaml__will_not_blow_up)
{
   std::string template_content = R"CONTENT(
parameters: [ { name: location }, { name: time_of_day } ]
prompt: "A rainbow-coloured butterfly flying across [location] during [time_of_day]"

)CONTENT";

   std::vector<std::pair<std::string, std::string>> template_arguments = {
      { "location", "a field of flowers" },
      { "time_of_day", "sunset" },
   };

   AllegroFlare::AI::PromptTemplateYAMLLoader prompt_template_yaml_loader;
   std::string expected_prompt = "foo";

   EXPECT_EQ(expected_prompt, prompt_template_yaml_loader.load_yaml(template_content, template_arguments));
}


