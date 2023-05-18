
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
    data: { target_node_name: my_dialog_node_567 }
  - text: I have a bad feeling too. We must proceed cautiously.
    type: node
    data:
      speaker: yuki
      pages:
        - Agreed. Trusting our instincts is crucial in these situations.
        - Let's carefully analyze each step and keep an eye out for any hidden dangers.
      options:
        - text: Agreed. Let's gather more information discreetly.
          type: exit_dialog
  - text: I'll keep my eyes open and watch our backs
    type: exit_dialog
)YAML_CONTENT";
};


class AllegroFlare_DialogTree_YAMLLoaderTestWithNestedNodesFixtureData : public ::testing::Test
{
public:
   std::string yaml_as_string = R"YAML_CONTENT(
name: my_node_abc123
speaker: jonas
pages:
  - I've heard rumors about a hidden treasure.
options:
  - text: Tell me more. Where should we start?
    type: node
    data:
      speaker: jonas
      pages:
        - According to the legends, the first clue lies within the ancient temple ruins deep in the forest.
        - We should head there and search for any hidden symbols or markings.
  - text: Rumors can be misleading. Any evidence?
    type: node
    data:
      speaker: jonas
      pages:
        - You're right to be skeptical.
        - I've uncovered an ancient inscription that suggests the treasure's existence.
        - It speaks of a forgotten chamber guarded by puzzles and traps.
        - We must find more clues to confirm its authenticity.
      options:
        - text: Agreed. Let's gather more information discreetly.
          type: go_to_node
          data: { target_node_name: my_dialog_node_567 }
        - text: I'll keep my eyes open and watch our backs
          type: exit_dialog
)YAML_CONTENT";
};


class AllegroFlare_DialogTree_YAMLLoaderTestWithSequenceOfNodesFixtureData : public ::testing::Test
{
public:
   std::string yaml_as_string = R"YAML_CONTENT(
- speaker: yuki
  pages:
    - We must find the ancient artifact before they do.
    - The key lies within the forgotten tomb.
    - Something seems fishy. Stay vigilant.
  options:
    - text: Agreed. Let's gather more information discreetly.
      type: go_to_node
      data: { target_node_name: my_dialog_node_567 }
    - text: I have a bad feeling too. We must proceed cautiously.
      type: node
      data:
        speaker: yuki
        pages:
          - Agreed. Trusting our instincts is crucial in these situations.
          - Let's carefully analyze each step and keep an eye out for any hidden dangers.
        options:
          - text: Agreed. Let's gather more information discreetly.
            type: exit_dialog
    - text: I'll keep my eyes open and watch our backs
      type: exit_dialog
)YAML_CONTENT";
};



TEST_F(AllegroFlare_DialogTree_YAMLLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::YAMLLoader yamlloader;
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTest, load__will_not_blow_up)
{
   std::string yaml_as_string = R"YAML_CONTENT(
- name: start
  speaker: yuki
  pages:
    - We must find the ancient artifact before they do.
  options:
    - text: I'll keep my eyes open and watch our backs
      type: exit_dialog
)YAML_CONTENT";

   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   yaml_loader.load(yaml_as_string);
   // TODO: Free up the node recursively
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithSequenceOfNodesFixtureData, load__will_set_loaded_to_true)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   yaml_loader.load(yaml_as_string);
   EXPECT_EQ(true, yaml_loader.get_loaded());
   //EXPECT_EQ(true, yaml_loader.loaded());
   // TODO: Free up the node recursively
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   load__on_the_root_node__when_the_speaker_is_not_present__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData, parse_and_create_node__will_extract_the_speaker)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   YAML::Node node = YAML::Load(yaml_as_string);
   AllegroFlare::DialogTree::Node *actual_node = yaml_loader.parse_and_create_node(&node).second;
   ASSERT_NE(nullptr, actual_node);
   EXPECT_EQ("yuki", actual_node->get_speaker());
}


//TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   //load__on_the_root_node__when_pages_are_not_present__will_throw_an_error)
//{
   //// TODO
//}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData, parse_and_create_node__will_extract_the_pages)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   YAML::Node node = YAML::Load(yaml_as_string);
   AllegroFlare::DialogTree::Node *actual_node = yaml_loader.parse_and_create_node(&node).second;
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
   parse_and_create_node__will_extract_the_expected_number_of_options)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   YAML::Node node = YAML::Load(yaml_as_string);
   AllegroFlare::DialogTree::Node *actual_node = yaml_loader.parse_and_create_node(&node).second;
   ASSERT_NE(nullptr, actual_node);

   std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> actual_options =
      actual_node->get_options();

   EXPECT_EQ(3, actual_options.size());
   // TODO: Free up the node recursively
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   parse_and_create_node__on_the_root_node__will_extract_options_with_the_expected_content)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   YAML::Node node = YAML::Load(yaml_as_string);
   AllegroFlare::DialogTree::Node *actual_node = yaml_loader.parse_and_create_node(&node).second;
   ASSERT_NE(nullptr, actual_node);
   std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> extracted_options =
      actual_node->get_options();
   ASSERT_EQ(3, extracted_options.size());

   // Option 0
   std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> expected_option_0 = extracted_options[0];
   EXPECT_EQ("Agreed. Let's gather more information discreetly.", expected_option_0.first);
   ASSERT_NE(nullptr, expected_option_0.second);
   EXPECT_EQ(true, expected_option_0.second->is_type(AllegroFlare::DialogTree::NodeOptions::GoToNode::TYPE));
   AllegroFlare::DialogTree::NodeOptions::GoToNode *as_go_to_node_0 = 
      static_cast<AllegroFlare::DialogTree::NodeOptions::GoToNode*>(expected_option_0.second);
   EXPECT_EQ("my_dialog_node_567", as_go_to_node_0->get_target_node_name());

   // Option 1
   std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> expected_option_1 = extracted_options[1];
   EXPECT_EQ("I have a bad feeling too. We must proceed cautiously.", expected_option_1.first);
   ASSERT_NE(nullptr, expected_option_1.second);
   EXPECT_EQ(true, expected_option_1.second->is_type(AllegroFlare::DialogTree::NodeOptions::Node::TYPE));
   AllegroFlare::DialogTree::NodeOptions::Node *as_node_1 =
      static_cast<AllegroFlare::DialogTree::NodeOptions::Node*>(expected_option_1.second);
   // Nested node content in Option 1 (sanity check, more thorough testing in follow-up tests)
      AllegroFlare::DialogTree::Node *actual_nested_node = as_node_1->get_node();
      ASSERT_NE(nullptr, actual_nested_node);
      EXPECT_EQ("yuki", actual_nested_node->get_speaker());

   // Option 2
   std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> expected_option_2 = extracted_options[2];
   EXPECT_EQ("I'll keep my eyes open and watch our backs", expected_option_2.first);
   ASSERT_NE(nullptr, expected_option_2.second);
   EXPECT_EQ(true, expected_option_2.second->is_type(AllegroFlare::DialogTree::NodeOptions::ExitDialog::TYPE));

   // TODO: Free up the node recursively
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithNestedNodesFixtureData,
   parse_and_create_node__will_extract_nested_node_options_with_the_expected_content)
{
   // TODO
}


