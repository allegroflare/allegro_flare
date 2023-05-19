
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Node.hpp>


TEST(AllegroFlare_DialogTree_NodeTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Node node;
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


