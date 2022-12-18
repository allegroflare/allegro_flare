
#include <gtest/gtest.h>

#include <AllegroFlare/FrameAnimation/AsepriteSpriteSheetJSONLoader.hpp>


TEST(AllegroFlare_FrameAnimation_AsepriteSpriteSheetJSONLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader aseprite_sprite_sheet_jsonloader;
}


TEST(AllegroFlare_FrameAnimation_AsepriteSpriteSheetJSONLoaderTest, run__returns_the_expected_response)
{
   AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader aseprite_sprite_sheet_jsonloader;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, aseprite_sprite_sheet_jsonloader.run());
}


