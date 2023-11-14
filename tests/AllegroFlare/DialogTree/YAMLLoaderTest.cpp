
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/YAMLLoader.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>


static AllegroFlare::DialogTree::Nodes::MultipageWithOptions *as_multipage(
   AllegroFlare::DialogTree::Nodes::Base* base)
{
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions *result =
      static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(base);
   return result;
}


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
    type: exit_dialog
  - text: I'll keep my eyes open and watch our backs
    type: exit_dialog
)YAML_CONTENT";
};


class AllegroFlare_DialogTree_YAMLLoaderTestWithSequenceOfNodesFixtureData : public ::testing::Test
{
public:
   std::string yaml_as_string = R"YAML_CONTENT(
- name: my_node_345
  type: multipage_with_options
  data:
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
         type: exit_dialog
       - text: I'll keep my eyes open and watch our backs
         type: exit_dialog
- name: my_node_567
  type: multipage_with_options
  data:
     speaker: charlie
     pages:
       - The ancient artifact before they do lies within the forgotten tomb.
     options:
       - text: Let's do it!
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
  type: multipage_with_options
  data:
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


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithSequenceOfNodesFixtureData,
   load__before_load__will_throw_an_error)
{
   // TODO
   // TODO: Free up the node recursively
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithSequenceOfNodesFixtureData,
   load__will_fill_the_node_bank_with_the_expected_content)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   yaml_loader.load(yaml_as_string);
   AllegroFlare::DialogTree::NodeBank node_bank = yaml_loader.get_node_bank();

   // Validate presence of expected nodes
   EXPECT_EQ(2, node_bank.num_nodes());
   EXPECT_EQ(true, node_bank.node_exists_by_name("my_node_345"));
   EXPECT_EQ(true, node_bank.node_exists_by_name("my_node_567"));

   // Sanity check node "my_node_345"
   //AllegroFlare::DialogTree::Nodes::Base* my_node_345 = node_bank.find_node_by_name("my_node_345");
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions* my_node_345 = as_multipage(
      node_bank.find_node_by_name("my_node_345")
   );

   ASSERT_NE(nullptr, my_node_345);
   EXPECT_EQ("yuki", my_node_345->get_speaker());
   EXPECT_EQ(3, my_node_345->get_pages().size());

   // Sanity check node "my_node_567"
   //AllegroFlare::DialogTree::Nodes::Base* my_node_567 = node_bank.find_node_by_name("my_node_567");
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions* my_node_567 = as_multipage(
      node_bank.find_node_by_name("my_node_567")
   );
   ASSERT_NE(nullptr, my_node_567);
   EXPECT_EQ(1, my_node_567->get_pages().size());
   EXPECT_EQ("charlie", my_node_567->get_speaker());
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   load__on_the_root_node__when_the_speaker_is_not_present__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   parse_and_create_MultipageWithOptions_node__will_extract_the_speaker)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   YAML::Node node = YAML::Load(yaml_as_string);
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions *actual_node =
      std::get<1>(yaml_loader.parse_and_create_MultipageWithOptions_node(&node)); //.second;
   ASSERT_NE(nullptr, actual_node);
   EXPECT_EQ("yuki", actual_node->get_speaker());
}


//TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   //load__on_the_root_node__when_pages_are_not_present__will_throw_an_error)
//{
   //// TODO
//}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   parse_and_create_MultipageWithOptions_node__will_extract_the_pages)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   YAML::Node node = YAML::Load(yaml_as_string);
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions *actual_node =
      std::get<1>(yaml_loader.parse_and_create_MultipageWithOptions_node(&node)); //.second;
      //yaml_loader.parse_and_create_MultipageWithOptions_node(&node).second;
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
   parse_and_create_MultiPageWithOptions_node__will_extract_the_expected_number_of_options)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   YAML::Node node = YAML::Load(yaml_as_string);
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions *actual_node =
      std::get<1>(yaml_loader.parse_and_create_MultipageWithOptions_node(&node)); //.second;
      //yaml_loader.parse_and_create_MultipageWithOptions_node(&node).second;
   ASSERT_NE(nullptr, actual_node);

   std::vector<
         std::tuple<std::string, AllegroFlare::DialogTree::NodeOptions::Base*, AllegroFlare::BitFlags<uint32_t>>
      > actual_options =
      actual_node->get_options();

   EXPECT_EQ(3, actual_options.size());
   // TODO: Free up the node recursively
}


TEST_F(AllegroFlare_DialogTree_YAMLLoaderTestWithFixtureData,
   parse_and_create_MultipageWithOptions_node__on_the_root_node__will_extract_options_with_the_expected_content)
{
   AllegroFlare::DialogTree::YAMLLoader yaml_loader;
   YAML::Node node = YAML::Load(yaml_as_string);
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions *actual_node =
      std::get<1>(yaml_loader.parse_and_create_MultipageWithOptions_node(&node)); //.second;
      //as_multipage(yaml_loader.parse_and_create_MultipageWithOptions_node(&node).second);
   ASSERT_NE(nullptr, actual_node);
   std::vector<std::tuple<std::string, AllegroFlare::DialogTree::NodeOptions::Base*, AllegroFlare::BitFlags<uint32_t>>> extracted_options =
      actual_node->get_options();
   ASSERT_EQ(3, extracted_options.size());

   // Option 0
   std::tuple<std::string, AllegroFlare::DialogTree::NodeOptions::Base*, AllegroFlare::BitFlags<uint32_t>> expected_option_0 = extracted_options[0];
   EXPECT_EQ("Agreed. Let's gather more information discreetly.", std::get<0>(expected_option_0));
   ASSERT_NE(nullptr, std::get<1>(expected_option_0)); //.second);
   EXPECT_EQ(true, std::get<1>(expected_option_0)->is_type(AllegroFlare::DialogTree::NodeOptions::GoToNode::TYPE));
   AllegroFlare::DialogTree::NodeOptions::GoToNode *as_go_to_node_0 = 
      static_cast<AllegroFlare::DialogTree::NodeOptions::GoToNode*>(std::get<1>(expected_option_0));
   EXPECT_EQ("my_dialog_node_567", as_go_to_node_0->get_target_node_name());

   // Option 1
   // //TODO: Re-evaluate this test now that NodeOptions::Node is removed
   //std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> expected_option_1 = extracted_options[1];
   //EXPECT_EQ("I have a bad feeling too. We must proceed cautiously.", expected_option_1.first);
   //ASSERT_NE(nullptr, expected_option_1.second);
   //EXPECT_EQ(true, expected_option_1.second->is_type(AllegroFlare::DialogTree::NodeOptions::Node::TYPE));
   //AllegroFlare::DialogTree::NodeOptions::Node *as_node_1 =
      //static_cast<AllegroFlare::DialogTree::NodeOptions::Node*>(expected_option_1.second);
   //// Nested node content in Option 1 (sanity check)
   //// TODO: Consider more thorough testing
      //AllegroFlare::DialogTree::Nodes::Base *actual_nested_node = as_node_1->get_node();
      //ASSERT_NE(nullptr, actual_nested_node);
      //EXPECT_EQ("yuki", actual_nested_node->get_speaker());

   // Option 2
   std::tuple<std::string, AllegroFlare::DialogTree::NodeOptions::Base*, AllegroFlare::BitFlags<uint32_t>> expected_option_2 = extracted_options[2];
   EXPECT_EQ("I'll keep my eyes open and watch our backs", std::get<0>(expected_option_2));
   ASSERT_NE(nullptr, std::get<1>(expected_option_2));
   EXPECT_EQ(true, std::get<1>(expected_option_2)->is_type(AllegroFlare::DialogTree::NodeOptions::ExitDialog::TYPE));

   // TODO: Free up the node recursively
}


