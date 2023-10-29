
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/NodeBank.hpp>


TEST(AllegroFlare_DialogTree_NodeBankTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::NodeBank node_bank;
}


TEST(AllegroFlare_DialogTree_NodeBankTest, find_shared_node_names__will_return_node_names_that_are_shared)
{
   AllegroFlare::DialogTree::NodeBank node_bank;
   node_bank.add_node("my_node_1", new AllegroFlare::DialogTree::Nodes::Base());
   node_bank.add_node("my_node_2", new AllegroFlare::DialogTree::Nodes::Base());
   node_bank.add_node("my_node_3", new AllegroFlare::DialogTree::Nodes::Base());

   AllegroFlare::DialogTree::NodeBank other_node_bank;
   other_node_bank.add_node("my_node_2", new AllegroFlare::DialogTree::Nodes::Base());
   other_node_bank.add_node("my_node_3", new AllegroFlare::DialogTree::Nodes::Base());
   other_node_bank.add_node("my_node_4", new AllegroFlare::DialogTree::Nodes::Base());
   other_node_bank.add_node("my_node_5", new AllegroFlare::DialogTree::Nodes::Base());

   std::set<std::string> expected_shared_node_names = { "my_node_2", "my_node_3" };
   std::set<std::string> actual_shared_node_names = node_bank.find_shared_node_names(&other_node_bank);

   EXPECT_EQ(expected_shared_node_names, actual_shared_node_names);

   node_bank.delete_all_nodes_and_clear();
   other_node_bank.delete_all_nodes_and_clear();
}


