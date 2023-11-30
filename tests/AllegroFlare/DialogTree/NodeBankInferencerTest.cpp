
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/NodeBankInferencer.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/DialogTree/BasicScreenplayTextLoader.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>


class AllegroFlare_DialogTree_NodeBankInferencerTest : public ::testing::Test
{
public:
   AllegroFlare::DialogTree::NodeBank build_node_bank()
   {
      AllegroFlare::DeploymentEnvironment deployment_environment("test");
      std::string fixture_path = deployment_environment.get_data_folder_path();
      std::string FIXTURE_FILE = fixture_path + "dialogs/basic_screenplay_text.screenplay.txt";
      std::string script_text = AllegroFlare::php::file_get_contents(FIXTURE_FILE);
      AllegroFlare::DialogTree::BasicScreenplayTextLoader basic_screenplay_text_loader;
      basic_screenplay_text_loader.set_text(script_text);
      basic_screenplay_text_loader.load();
      AllegroFlare::DialogTree::NodeBank node_bank = basic_screenplay_text_loader.get_node_bank();
      //ASSERT_EQ(12, node_bank.num_nodes());
      return node_bank;
   }
};


TEST_F(AllegroFlare_DialogTree_NodeBankInferencerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::NodeBankInferencer node_bank_inferencer;
}


TEST_F(AllegroFlare_DialogTree_NodeBankInferencerTest, run__returns_the_expected_response)
{
   AllegroFlare::DialogTree::NodeBank node_bank = build_node_bank();
   AllegroFlare::DialogTree::NodeBankInferencer node_bank_inferencer(&node_bank);

   std::vector<std::string> expected_speaking_characters = {
      "DETECTIVE",
      "BANKER",
      "COMMISSIONER",
      "ASSISTANT",
   };
   std::vector<std::string> actual_speaking_characters = node_bank_inferencer.obtain_list_of_speaking_characters();

   EXPECT_EQ(expected_speaking_characters, actual_speaking_characters);

}


TEST_F(AllegroFlare_DialogTree_NodeBankInferencerTest,
   character_names_are_present__when_all_the_names_are_present__will_return_true)
{
   AllegroFlare::DialogTree::NodeBank node_bank = build_node_bank();
   AllegroFlare::DialogTree::NodeBankInferencer node_bank_inferencer(&node_bank);

   std::vector<std::string> some_expected_character_names = {
      "COMMISSIONER",
      "BANKER",
   };
   EXPECT_EQ(true, node_bank_inferencer.character_names_are_present(some_expected_character_names));
}


TEST_F(AllegroFlare_DialogTree_NodeBankInferencerTest,
   character_names_are_present__when_some_of_the_names_are_not_present__will_return_false)
{
   AllegroFlare::DialogTree::NodeBank node_bank = build_node_bank();
   AllegroFlare::DialogTree::NodeBankInferencer node_bank_inferencer(&node_bank);

   std::vector<std::string> some_expected_character_names = {
      "COMMISSIONER",
      "MR. MISSING",
      "BANKER",
   };
   EXPECT_EQ(false, node_bank_inferencer.character_names_are_present(some_expected_character_names));
}


TEST_F(AllegroFlare_DialogTree_NodeBankInferencerTest,
   find_missing_character_names__when_some_of_the_names_are_not_present__will_return_names_that_are_not_included)
{
   AllegroFlare::DialogTree::NodeBank node_bank = build_node_bank();
   AllegroFlare::DialogTree::NodeBankInferencer node_bank_inferencer(&node_bank);

   std::vector<std::string> some_expected_character_names = {
      "DETECTIVE",
      "COMMISSIONER",
      "MR. MISSING",
      "BANKER",
      "MRS. NOWHERE",
   };

   std::vector<std::string> expected_missing_character_names = {
      "MR. MISSING",
      "MRS. NOWHERE",
   };
   std::vector<std::string> actual_missing_character_names =
      node_bank_inferencer.find_missing_character_names(some_expected_character_names);

   EXPECT_EQ(expected_missing_character_names, actual_missing_character_names);
}


TEST_F(AllegroFlare_DialogTree_NodeBankInferencerTest,
   find_missing_character_names__when_all_of_the_names_are_present__will_return_an_empty_result)
{
   AllegroFlare::DialogTree::NodeBank node_bank = build_node_bank();
   AllegroFlare::DialogTree::NodeBankInferencer node_bank_inferencer(&node_bank);

   std::vector<std::string> some_expected_character_names = {
      "DETECTIVE",
      "COMMISSIONER",
      "BANKER",
   };
   std::vector<std::string> expected_missing_character_names = {};
   std::vector<std::string> actual_missing_character_names =
      node_bank_inferencer.find_missing_character_names(some_expected_character_names);

   EXPECT_EQ(expected_missing_character_names, actual_missing_character_names);
}


