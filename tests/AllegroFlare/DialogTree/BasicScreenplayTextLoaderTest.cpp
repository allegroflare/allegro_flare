
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/BasicScreenplayTextLoader.hpp>
#include <AllegroFlare/UsefulPHP.hpp>


TEST(AllegroFlare_DialogTree_BasicScreenplayTextLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::BasicScreenplayTextLoader basic_screenplay_text_loader;
}


TEST(AllegroFlare_DialogTree_BasicScreenplayTextLoaderTest, load__will_build_the_expected_node_bank_for_the_script)
{
   std::string script_text = AllegroFlare::php::file_get_contents(
      "/Users/markoates/Repos/allegro_flare/tests/fixtures/dialogs/basic_screenplay_text.txt"
   );

   AllegroFlare::DialogTree::BasicScreenplayTextLoader basic_screenplay_text_loader;
   basic_screenplay_text_loader.set_text(script_text);
   basic_screenplay_text_loader.load();

   AllegroFlare::DialogTree::NodeBank node_bank = basic_screenplay_text_loader.get_node_bank();

   ASSERT_EQ(12, node_bank.num_nodes());
}


