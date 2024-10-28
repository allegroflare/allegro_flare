
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Nodes/Interparsable.hpp>


TEST(AllegroFlare_DialogTree_Nodes_InterparsableTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Nodes::Interparsable multipage_with_options;
}


TEST(AllegroFlare_DialogTree_Nodes_InterparsableTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Nodes/Interparsable",
     AllegroFlare::DialogTree::Nodes::Interparsable::TYPE
   );
}


TEST(AllegroFlare_DialogTree_Nodes_InterparsableTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Nodes::Interparsable multipage_with_options;
   EXPECT_EQ(AllegroFlare::DialogTree::Nodes::Interparsable::TYPE, multipage_with_options.get_type());
}


TEST(AllegroFlare_DialogTree_Nodes_InterparsableTest, num_options__compares_correctly_against_standard_int)
{
   AllegroFlare::DialogTree::Nodes::Interparsable multipage_with_options;
   int negative_number = -1;
   EXPECT_TRUE(negative_number < multipage_with_options.num_options());
}


TEST(AllegroFlare_DialogTree_Nodes_InterparsableTest,
   infer_cursor_position_on_spawn__will_return_the_position_of_the_option_with_the_flag_set)
{
   AllegroFlare::DialogTree::Nodes::Interparsable multipage_with_options;
   multipage_with_options.set_options({
      { "Choice 1", nullptr, 0 },
      { "Choice 2", nullptr, 0 },
      { "Choice 3", nullptr, AllegroFlare::BitFlags<uint32_t>(
            AllegroFlare::DialogTree::Nodes::Interparsable::OptionFlags::FLAG_CURSOR_HERE_ON_SPAWN
         ) },
      { "Choice 4", nullptr, 0 },
   });

   EXPECT_EQ(2, multipage_with_options.infer_cursor_position_on_spawn());
}


TEST(AllegroFlare_DialogTree_NodesInterparsableTest,
   option_is_selectable__will_return_true_if_an_option_is_not_disabled)
{
   AllegroFlare::DialogTree::Nodes::Interparsable multipage_with_options;
   multipage_with_options.set_options({
      { "Choice 1", nullptr, 0 },
   });

   EXPECT_EQ(true, multipage_with_options.option_is_selectable(0));
}


TEST(AllegroFlare_DialogTree_NodesInterparsableTest,
   option_is_selectable__will_return_false_if_an_option_is_disabled)
{
   AllegroFlare::DialogTree::Nodes::Interparsable multipage_with_options;
   multipage_with_options.set_options({
      { "Choice 1", nullptr, AllegroFlare::BitFlags<uint32_t>(
         AllegroFlare::DialogTree::Nodes::Interparsable::OptionFlags::FLAG_DISABLED
      ) },
   });

   EXPECT_EQ(false, multipage_with_options.option_is_selectable(0));
}


