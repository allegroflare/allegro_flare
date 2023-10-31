
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/ChapterIndex.hpp>


TEST(AllegroFlare_DialogSystem_ChapterIndexTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::ChapterIndex chapter_index;
}


TEST(AllegroFlare_DialogSystem_ChapterIndexTest, chapters__retains_order_when_set)
{
   AllegroFlare::DialogSystem::ChapterIndex chapter_index;
   chapter_index.set_chapters({
      { "Chapter 1: One", nullptr },
      { "Chapter 0: Zero", nullptr },
      { "Chapter 4: Four", nullptr },
   });

   std::vector<std::string> expected_ordered_identifiers = { "Chapter 1: One", "Chapter 0: Zero", "Chapter 4: Four" };
   std::vector<std::string> actual_identifiers = chapter_index.get_chapter_identifiers();

   EXPECT_EQ(expected_ordered_identifiers, actual_identifiers);
}


TEST(AllegroFlare_DialogSystem_ChapterIndexTest, chapters__retains_order_when_items_are_inserted)
{
   AllegroFlare::DialogSystem::ChapterIndex chapter_index;
   chapter_index.set_chapters({
      { "Chapter 1: One", nullptr },
      { "Chapter 0: Zero", nullptr },
      { "Chapter 4: Four", nullptr },
   });

   chapter_index.add_chapter("Zoo", nullptr);
   chapter_index.add_chapter("Advent", nullptr);

   std::vector<std::string> expected_ordered_identifiers = {
      "Chapter 1: One",
      "Chapter 0: Zero",
      "Chapter 4: Four",
      "Zoo",
      "Advent",
   };
   std::vector<std::string> actual_identifiers = chapter_index.get_chapter_identifiers();

   EXPECT_EQ(expected_ordered_identifiers, actual_identifiers);
}


