
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/MultipageWithOptionsOptionFlags.hpp>


TEST(AllegroFlare_DialogTree_MultipageWithOptionsOptionFlagsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::MultipageWithOptionsOptionFlags multipage_with_options_option_flags;
}


TEST(AllegroFlare_DialogTree_MultipageWithOptionsOptionFlagsTest, run__returns_the_expected_response)
{
   AllegroFlare::DialogTree::MultipageWithOptionsOptionFlags multipage_with_options_option_flags;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, multipage_with_options_option_flags.run());
}


