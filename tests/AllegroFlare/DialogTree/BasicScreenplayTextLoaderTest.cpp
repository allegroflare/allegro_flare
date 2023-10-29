
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/BasicScreenplayTextLoader.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>


TEST(AllegroFlare_DialogTree_BasicScreenplayTextLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::BasicScreenplayTextLoader basic_screenplay_text_loader;
}


TEST(AllegroFlare_DialogTree_BasicScreenplayTextLoaderTest, load__will_build_the_expected_node_bank_for_the_script)
{
   std::string script_text = AllegroFlare::php::file_get_contents(
      "/Users/markoates/Repos/allegro_flare/tests/fixtures/dialogs/basic_screenplay_text.screenplay.txt"
   );

   AllegroFlare::DialogTree::BasicScreenplayTextLoader basic_screenplay_text_loader;
   basic_screenplay_text_loader.set_text(script_text);
   basic_screenplay_text_loader.load();

   AllegroFlare::DialogTree::NodeBank node_bank = basic_screenplay_text_loader.get_node_bank();

   ASSERT_EQ(13, node_bank.num_nodes());

   std::map<std::string, AllegroFlare::DialogTree::Nodes::Base*> nodes = node_bank.get_nodes_ref();

   // All nodes (except the last one) are the expected types
   int count_MultipageWithOptions = 0;
   int count_ExitDialog = 0;
   for (auto &node : nodes)
   {
      if (std::get<1>(node)->is_type(AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE))
      {
         count_MultipageWithOptions++;
      }
      else if (std::get<1>(node)->is_type(AllegroFlare::DialogTree::Nodes::ExitDialog::TYPE))
      {
         count_ExitDialog++;
      }
   }
   EXPECT_EQ(12, count_MultipageWithOptions);
   EXPECT_EQ(1, count_ExitDialog);

   // Pluck a few nodes
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions *as = nullptr;

   as = static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(nodes["dialog_node_0"]);
   EXPECT_EQ("DETECTIVE", as->get_speaker());
   ASSERT_EQ(false, as->get_options().empty());
   EXPECT_EQ("next", std::get<0>(as->get_options()[0])); //.first);
   ASSERT_NE(nullptr, std::get<1>(as->get_options()[0])); //.second);
   EXPECT_EQ(
      AllegroFlare::DialogTree::NodeOptions::GoToNode::TYPE,
      std::get<1>(as->get_options()[0])->get_type() //.second->get_type()
   );
   AllegroFlare::DialogTree::NodeOptions::GoToNode* as_option_node =
      static_cast<AllegroFlare::DialogTree::NodeOptions::GoToNode*>(std::get<1>(as->get_options()[0])); //.second);
   EXPECT_EQ(
      "dialog_node_1",
      as_option_node->get_target_node_name()
   );

   as = static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(nodes["dialog_node_2"]);
   EXPECT_EQ("COMMISSIONER", as->get_speaker());
   EXPECT_EQ(
      "Maybe it was an inside job, but how could BANKER have done it? He's always been loyal to this bank!",
      as->get_pages()[0]
   );
}


