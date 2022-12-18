
#include <gtest/gtest.h>

#include <AllegroFlare/FrameAnimation/Book.hpp>


TEST(AllegroFlare_FrameAnimation_BookTest, can_be_created_without_blowing_up)
{
   AllegroFlare::FrameAnimation::Book book;
}


TEST(AllegroFlare_FrameAnimation_BookTest, run__returns_the_expected_response)
{
   AllegroFlare::FrameAnimation::Book book;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, book.run());
}


