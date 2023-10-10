
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>


TEST(AllegroFlare_DialogTree_Nodes_WaitTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Nodes::Wait wait;
}


TEST(AllegroFlare_DialogTree_Nodes_WaitTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Nodes/Wait",
     AllegroFlare::DialogTree::Nodes::Wait::TYPE
   );
}


TEST(AllegroFlare_DialogTree_Nodes_WaitTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Nodes::Wait wait;
   EXPECT_EQ(AllegroFlare::DialogTree::Nodes::Wait::TYPE, wait.get_type());
}


