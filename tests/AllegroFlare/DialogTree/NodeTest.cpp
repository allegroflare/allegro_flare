
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Node.hpp>


TEST(AllegroFlare_DialogTree_NodeTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Node node;
}


TEST(AllegroFlare_DialogTree_NodeTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Node",
     AllegroFlare::DialogTree::Node::TYPE
   );
}


TEST(AllegroFlare_DialogTree_NodeTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Node node;
   EXPECT_EQ(AllegroFlare::DialogTree::Node::TYPE, node.get_type());
}


TEST(AllegroFlare_DialogTree_NodeTest, num_options__compares_correctly_against_standard_int)
{
   AllegroFlare::DialogTree::Node node;
   int negative_number = -1;
   EXPECT_TRUE(negative_number < node.num_options());
}


TEST(AllegroFlare_DialogTree_NodeTest, num_pages__compares_correctly_against_standard_int)
{
   AllegroFlare::DialogTree::Node node;
   int negative_number = -1;
   EXPECT_TRUE(negative_number < node.num_pages());
}


