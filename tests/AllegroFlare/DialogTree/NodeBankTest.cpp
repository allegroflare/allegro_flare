
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(AllegroFlare_DialogTree_NodeBankTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::NodeBank node_bank;
}


TEST(AllegroFlare_DialogTree_NodeBankTest, find_node_by_name__when_a_node_does_not_exist__returns_a_nullptr)
{
   AllegroFlare::DialogTree::NodeBank node_bank;
   EXPECT_EQ(nullptr, node_bank.find_node_by_name("a-node-name-that-does-not-exist"));
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


TEST(AllegroFlare_DialogTree_NodeBankTest,
   merge__if_the_other_node_bank_contains_node_names_that_already_exist__will_throw_an_error)
{
   AllegroFlare::DialogTree::NodeBank node_bank;
   node_bank.add_node("my_node_with_non_unique_name", new AllegroFlare::DialogTree::Nodes::Base());
   AllegroFlare::DialogTree::NodeBank other_node_bank;
   other_node_bank.add_node("my_node_with_non_unique_name", new AllegroFlare::DialogTree::Nodes::Base());

   EXPECT_THROW_WITH_MESSAGE(
      node_bank.merge(&other_node_bank),
      std::runtime_error,
      "[AllegroFlare::DialogTree::NodeBank::merge]: error: Cannot merge two node_bank objects that do not have "
         "node names that are the same"
   );
}


TEST(AllegroFlare_DialogTree_NodeBankTest, merge__will_add_the_nodes_from_another_node_bank)
{
   AllegroFlare::DialogTree::NodeBank node_bank;
   node_bank.add_node("my_node_1", new AllegroFlare::DialogTree::Nodes::Base());
   node_bank.add_node("my_node_2", new AllegroFlare::DialogTree::Nodes::Base());
   node_bank.add_node("my_node_3", new AllegroFlare::DialogTree::Nodes::Base());
   node_bank.add_node("my_node_4", new AllegroFlare::DialogTree::Nodes::Base());

   AllegroFlare::DialogTree::NodeBank other_node_bank;
   other_node_bank.add_node("my_node_5", new AllegroFlare::DialogTree::Nodes::Base());
   other_node_bank.add_node("my_node_6", new AllegroFlare::DialogTree::Nodes::Base());

   std::set<std::string> expected_final_node_names = {
      "my_node_1",
      "my_node_2",
      "my_node_3",
      "my_node_4",
      "my_node_5",
      "my_node_6",
   };

   node_bank.merge(&other_node_bank);

   EXPECT_EQ(expected_final_node_names.size(), node_bank.num_nodes());

   for (auto &expected_final_node_name : expected_final_node_names)
   {
      EXPECT_EQ(true, node_bank.node_exists_by_name(expected_final_node_name));
   }
}


