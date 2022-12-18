
#include <gtest/gtest.h>

#include <AllegroFlare/FrameAnimation/SpriteSheet.hpp>


TEST(AllegroFlare_FrameAnimation_SpriteSheetTest, can_be_created_without_blowing_up)
{
   AllegroFlare::FrameAnimation::SpriteSheet sprite_sheet;
}


TEST(AllegroFlare_FrameAnimation_SpriteSheetTest, run__returns_the_expected_response)
{
   AllegroFlare::FrameAnimation::SpriteSheet sprite_sheet;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, sprite_sheet.run());
}


