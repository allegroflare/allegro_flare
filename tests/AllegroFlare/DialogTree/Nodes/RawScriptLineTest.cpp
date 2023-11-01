
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Nodes/RawScriptLine.hpp>


TEST(AllegroFlare_DialogTree_Nodes_RawScriptLineTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Nodes::RawScriptLine raw_script_line;
}


TEST(AllegroFlare_DialogTree_Nodes_RawScriptLineTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Nodes/RawScriptLine",
     AllegroFlare::DialogTree::Nodes::RawScriptLine::TYPE
   );
}


TEST(AllegroFlare_DialogTree_Nodes_RawScriptLineTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Nodes::RawScriptLine raw_script_line;
   EXPECT_EQ(AllegroFlare::DialogTree::Nodes::RawScriptLine::TYPE, raw_script_line.get_type());
}


