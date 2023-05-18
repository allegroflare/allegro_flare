
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/YAMLLoader.hpp>


TEST(AllegroFlare_DialogTree_YAMLLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::YAMLLoader yamlloader;
}


TEST(AllegroFlare_DialogTree_YAMLLoaderTest, load__will_not_blow_up)
{
   std::string yaml_string_content = "";
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   EXPECT_NE(nullptr, yaml_loader.load());
   // TODO: Free up the node recursively
}


TEST(AllegroFlare_DialogTree_YAMLLoaderTest, load__on_the_root_node__will_extract_the_speaker)
{
   std::string yaml_string_content = R"YAML_CONTENT(
- speaker: yuki
  pages:
    - We must find the ancient artifact before they do.
    - The key lies within the forgotten tomb.
    - Something seems fishy. Stay vigilant.
  options:
    - text: Agreed. Let's gather more information discreetly.
      type: node
      data:
        - speaker: yuki
          pages:
            - Absolutely. I'll start digging deeper undercover.
    - text: I have a bad feeling too. We must proceed cautiously.
      type: node
      data:
        - speaker: yuki
          pages:
            - Trust your instincts. I'll watch our every step.
    - text: I'll keep my eyes open and watch our backs
      type: node
      data:
        - speaker: yuki
          pages:
            - That's reassuring, main_character. I'll do the same, we're in this together.
)YAML_CONTENT";

   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   EXPECT_NE(nullptr, yaml_loader.load(yaml_string_content));
   // TODO: Free up the node recursively
}


