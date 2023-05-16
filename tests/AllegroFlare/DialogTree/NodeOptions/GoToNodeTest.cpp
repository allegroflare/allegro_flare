
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>


TEST(AllegroFlare_DialogTree_NodeOptions_GoToNodeTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::NodeOptions::GoToNode go_to_node;
}


TEST(AllegroFlare_DialogTree_NodeOptions_GoToNodeTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/NodeOptions/GoToNode",
     AllegroFlare::DialogTree::NodeOptions::GoToNode::TYPE
   );
}


TEST(AllegroFlare_DialogTree_NodeOptions_GoToNodeTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::NodeOptions::GoToNode go_to_node;
   EXPECT_EQ(AllegroFlare::DialogTree::NodeOptions::GoToNode::TYPE, go_to_node.get_type());
}


