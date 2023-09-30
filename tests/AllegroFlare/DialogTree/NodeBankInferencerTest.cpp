
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/NodeBankInferencer.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/DialogTree/BasicScreenplayTextLoader.hpp>


TEST(AllegroFlare_DialogTree_NodeBankInferencerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::NodeBankInferencer node_bank_inferencer;
}


TEST(AllegroFlare_DialogTree_NodeBankInferencerTest, run__returns_the_expected_response)
{
   std::string script_text = AllegroFlare::php::file_get_contents(
      "/Users/markoates/Repos/allegro_flare/tests/fixtures/dialogs/basic_screenplay_text.txt"
   );
   AllegroFlare::DialogTree::BasicScreenplayTextLoader basic_screenplay_text_loader;
   basic_screenplay_text_loader.set_text(script_text);
   basic_screenplay_text_loader.load();
   AllegroFlare::DialogTree::NodeBank node_bank = basic_screenplay_text_loader.get_node_bank();
   ASSERT_EQ(12, node_bank.num_nodes());

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


