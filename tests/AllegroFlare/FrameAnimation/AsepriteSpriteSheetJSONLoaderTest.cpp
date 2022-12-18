
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/FrameAnimation/AsepriteSpriteSheetJSONLoader.hpp>


TEST(AllegroFlare_FrameAnimation_AsepriteSpriteSheetJSONLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader aseprite_sprite_sheet_jsonloader;
}


TEST(AllegroFlare_FrameAnimation_AsepriteSpriteSheetJSONLoaderTest,
   load__will_not_blow_up)
{
   AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader asesprite_sheet_jsondata_loader;
   asesprite_sheet_jsondata_loader.load();
}


TEST(AllegroFlare_FrameAnimation_AsepriteSpriteSheetJSONLoaderTest,
   load__on_a_filename_that_does_not_exist__throws_an_error)
{
   AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader loader("./foo/bar/file_that_does_not_exist.json");
   EXPECT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error,
      "[AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader::load]: error: "
      "The expected json file does not exist. Looking in \"./foo/bar/file_that_does_not_exist.json\""
   )
}


TEST(AllegroFlare_FrameAnimation_AsepriteSpriteSheetJSONLoaderTest,
   load__fills_the_animation_book_with_the_expected_values)
{
   AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader asesprite_sheet_jsondata_loader;
   std::map<std::string, AllegroFlare::FrameAnimation::Animation> actual = asesprite_sheet_jsondata_loader.load();

   EXPECT_EQ(1, actual.count("blob"));
   EXPECT_EQ(3, actual["blob"].get_num_frames());

   std::vector<AllegroFlare::FrameAnimation::Frame> blob_frames = actual["blob"].get_frames();
   EXPECT_EQ(1,   blob_frames[0].get_index());
   EXPECT_FLOAT_EQ(0.2, blob_frames[0].get_duration());
   EXPECT_EQ(2,   blob_frames[1].get_index());
   EXPECT_FLOAT_EQ(0.1, blob_frames[1].get_duration());
   EXPECT_EQ(3,   blob_frames[2].get_index());
   EXPECT_FLOAT_EQ(0.2, blob_frames[2].get_duration());

   EXPECT_EQ(AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_PING_PONG, actual["blob"].get_playmode());


   std::vector<AllegroFlare::FrameAnimation::Frame> die_frames = actual["die"].get_frames();
   EXPECT_EQ(9,   die_frames[0].get_index());
   EXPECT_FLOAT_EQ(0.2, die_frames[0].get_duration());
   EXPECT_EQ(10,   die_frames[1].get_index());
   EXPECT_FLOAT_EQ(0.2, die_frames[1].get_duration());
   EXPECT_EQ(11,   die_frames[2].get_index());
   EXPECT_FLOAT_EQ(0.2, die_frames[2].get_duration());

   EXPECT_EQ(AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_LOOP, actual["die"].get_playmode());
}


