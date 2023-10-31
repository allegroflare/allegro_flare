
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>


TEST(AllegroFlare_DialogTree_Nodes_MultipageWithOptionsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions multipage_with_options;
}


TEST(AllegroFlare_DialogTree_Nodes_MultipageWithOptionsTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Nodes/MultipageWithOptions",
     AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE
   );
}


TEST(AllegroFlare_DialogTree_Nodes_MultipageWithOptionsTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions multipage_with_options;
   EXPECT_EQ(AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE, multipage_with_options.get_type());
}


TEST(AllegroFlare_DialogTree_NodeTest, num_options__compares_correctly_against_standard_int)
{
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions multipage_with_options;
   int negative_number = -1;
   EXPECT_TRUE(negative_number < multipage_with_options.num_options());
}


TEST(AllegroFlare_DialogTree_NodeTest,
   infer_cursor_position_on_spawn__will_return_the_position_of_the_option_with_the_flag_set)
{
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions multipage_with_options;
   multipage_with_options.set_options({
      { "Choice 1", nullptr, 0 },
      { "Choice 2", nullptr, 0 },
      { "Choice 3", nullptr, AllegroFlare::BitFlags<uint32_t>(
            AllegroFlare::DialogTree::Nodes::MultipageWithOptions::OptionFlags::FLAG_CURSOR_HERE_ON_SPAWN
         ) },
      { "Choice 4", nullptr, 0 },
   });

   EXPECT_EQ(2, multipage_with_options.infer_cursor_position_on_spawn());
}


