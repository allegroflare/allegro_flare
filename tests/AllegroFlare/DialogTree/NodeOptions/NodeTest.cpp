
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/NodeOptions/Node.hpp>


TEST(AllegroFlare_DialogTree_NodeOptions_NodeTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::NodeOptions::Node node;
}


TEST(AllegroFlare_DialogTree_NodeOptions_NodeTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/NodeOptions/Node",
     AllegroFlare::DialogTree::NodeOptions::Node::TYPE
   );
}


TEST(AllegroFlare_DialogTree_NodeOptions_NodeTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::NodeOptions::Node node;
   EXPECT_EQ(AllegroFlare::DialogTree::NodeOptions::Node::TYPE, node.get_type());
}


