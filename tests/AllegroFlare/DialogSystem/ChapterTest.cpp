
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/Chapter.hpp>


TEST(AllegroFlare_DialogSystem_ChapterTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::Chapter chapter;
}


TEST(AllegroFlare_DialogSystem_ChapterTest, run__returns_the_expected_response)
{
   AllegroFlare::DialogSystem::Chapter chapter;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, chapter.run());
}


