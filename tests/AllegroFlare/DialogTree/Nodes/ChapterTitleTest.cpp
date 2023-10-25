
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Nodes/ChapterTitle.hpp>


TEST(AllegroFlare_DialogTree_Nodes_ChapterTitleTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Nodes::ChapterTitle chapter_title;
}


TEST(AllegroFlare_DialogTree_Nodes_ChapterTitleTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Nodes/ChapterTitle",
     AllegroFlare::DialogTree::Nodes::ChapterTitle::TYPE
   );
}


TEST(AllegroFlare_DialogTree_Nodes_ChapterTitleTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Nodes::ChapterTitle chapter_title;
   EXPECT_EQ(AllegroFlare::DialogTree::Nodes::ChapterTitle::TYPE, chapter_title.get_type());
}


