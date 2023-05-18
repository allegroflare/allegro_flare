
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/YAMLLoader.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>


class AllegroFlare_DialogTree_YAMLLoaderTest : public ::testing::Test {};
class AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData : public ::testing::Test
{
public:
   std::string yaml_as_string = R"YAML_CONTENT(
speaker: yuki
pages:
  - We must find the ancient artifact before they do.
  - The key lies within the forgotten tomb.
  - Something seems fishy. Stay vigilant.
options:
  - text: Agreed. Let's gather more information discreetly.
    type: go_to_node
    data:
      - speaker: yuki
        pages:
          - Absolutely. I'll start digging deeper undercover.
  - text: I have a bad feeling too. We must proceed cautiously.
    type: go_to_node
    data:
      - speaker: yuki
        pages:
          - Trust your instincts. I'll watch our every step.
  - text: I'll keep my eyes open and watch our backs
    type: exit_dialog
)YAML_CONTENT";
};



TEST_F(AllegroFlare_DialogTree_YAMLLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::YAMLLoader yamlloader;
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData, load__will_not_blow_up)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   EXPECT_NE(nullptr, yaml_loader.load(yaml_as_string));
   // TODO: Free up the node recursively
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   load__on_the_root_node__when_the_speaker_is_not_present__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData, load__on_the_root_node__will_extract_the_speaker)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   AllegroFlare::DialogTree::Node *actual_node = yaml_loader.load(yaml_as_string);
   ASSERT_NE(nullptr, actual_node);
   EXPECT_EQ("yuki", actual_node->get_speaker());
}


//TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   //load__on_the_root_node__when_pages_are_not_present__will_throw_an_error)
//{
   //// TODO
//}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData, load__on_the_root_node__will_extract_the_pages)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   AllegroFlare::DialogTree::Node *actual_node = yaml_loader.load(yaml_as_string);
   ASSERT_NE(nullptr, actual_node);

   std::vector<std::string> expected_pages = {
      "We must find the ancient artifact before they do.",
      "The key lies within the forgotten tomb.",
      "Something seems fishy. Stay vigilant.",
   };
   std::vector<std::string> actual_pages = actual_node->get_pages();

   EXPECT_EQ(expected_pages, actual_pages);
   // TODO: Free up the node recursively
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   load__on_the_root_node__will_extract_the_expected_number_of_options)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   AllegroFlare::DialogTree::Node *actual_node = yaml_loader.load(yaml_as_string);
   ASSERT_NE(nullptr, actual_node);

   std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> actual_options =
      actual_node->get_options();

   EXPECT_EQ(3, actual_options.size());
   // TODO: Free up the node recursively
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   load__on_the_root_node__will_extract_options_with_the_expected_content)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   AllegroFlare::DialogTree::Node *actual_node = yaml_loader.load(yaml_as_string);
   ASSERT_NE(nullptr, actual_node);
   std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> extracted_options =
      actual_node->get_options();
   ASSERT_EQ(3, extracted_options.size());

   // Option 0
   std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> expected_option_0 = extracted_options[0];
   EXPECT_EQ("Agreed. Let's gather more information discreetly.", expected_option_0.first);
   EXPECT_NE(nullptr, expected_option_0.second);
   EXPECT_EQ(true, expected_option_0.second->is_type(AllegroFlare::DialogTree::NodeOptions::GoToNode::TYPE));

   // Option 2
   std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> expected_option_2 = extracted_options[2];
   EXPECT_EQ("I'll keep my eyes open and watch our backs", expected_option_2.first);
   EXPECT_NE(nullptr, expected_option_2.second);
   EXPECT_EQ(true, expected_option_2.second->is_type(AllegroFlare::DialogTree::NodeOptions::ExitDialog::TYPE));


   // TODO: Free up the node recursively
}


