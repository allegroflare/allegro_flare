
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


TEST(AllegroFlare_DialogTree_NodeTest, num_pages__compares_correctly_against_standard_int)
{
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions multipage_with_options;
   int negative_number = -1;
   EXPECT_TRUE(negative_number < multipage_with_options.num_pages());
}


