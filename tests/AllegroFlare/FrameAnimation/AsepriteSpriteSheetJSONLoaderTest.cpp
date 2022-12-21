
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/FrameAnimation/AsepriteSpriteSheetJSONLoader.hpp>


TEST(AllegroFlare_FrameAnimation_AsepriteSpriteSheetJSONLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader loader;
}


TEST(AllegroFlare_FrameAnimation_AsepriteSpriteSheetJSONLoaderTest,
   load__will_not_blow_up)
{
   AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader loader;
   loader.load();
}


TEST(AllegroFlare_FrameAnimation_AsepriteSpriteSheetJSONLoaderTest,
   load__on_a_filename_that_does_not_exist__throws_an_error)
{
   AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader loader("./foo/bar/file_that_does_not_exist.json");
   EXPECT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error,
      "[AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader::load]: error: "
      "The expected json file does not exist. Looking for \"./foo/bar/file_that_does_not_exist.json\" "
      "from the current path \"/Users/markoates/Repos/allegro_flare\"."
   )
}


TEST(AllegroFlare_FrameAnimation_AsepriteSpriteSheetJSONLoaderTest,
   load__fills_the_animation_book_with_the_expected_values)
{
   std::string TEST_FIXTURE_JSON_FILE = "./tests/fixtures/sprites_grid-x.json";

   AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader loader(TEST_FIXTURE_JSON_FILE);
   std::map<std::string, AllegroFlare::FrameAnimation::Animation> actual = loader.load();


   ASSERT_EQ(1, actual.count("blob"));
   ASSERT_EQ(3, actual["blob"].get_num_frames());

   std::vector<AllegroFlare::FrameAnimation::Frame> blob_frames = actual["blob"].get_frames();
   EXPECT_EQ(1,   blob_frames[0].get_index());
   EXPECT_FLOAT_EQ(0.2, blob_frames[0].get_duration());
   EXPECT_EQ(2,   blob_frames[1].get_index());
   EXPECT_FLOAT_EQ(0.1, blob_frames[1].get_duration());
   EXPECT_EQ(3,   blob_frames[2].get_index());
   EXPECT_FLOAT_EQ(0.2, blob_frames[2].get_duration());

   EXPECT_EQ(AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_PING_PONG, actual["blob"].get_playmode());


   ASSERT_EQ(1, actual.count("die"));
   ASSERT_EQ(3, actual["die"].get_num_frames());

   std::vector<AllegroFlare::FrameAnimation::Frame> die_frames = actual["die"].get_frames();
   EXPECT_EQ(9,   die_frames[0].get_index());
   EXPECT_FLOAT_EQ(0.2, die_frames[0].get_duration());
   EXPECT_EQ(10,   die_frames[1].get_index());
   EXPECT_FLOAT_EQ(0.2, die_frames[1].get_duration());
   EXPECT_EQ(11,   die_frames[2].get_index());
   EXPECT_FLOAT_EQ(0.2, die_frames[2].get_duration());

   EXPECT_EQ(AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_ONCE, actual["die"].get_playmode());


   ASSERT_EQ(1, actual.count("fly"));
   ASSERT_EQ(2, actual["fly"].get_num_frames());

   std::vector<AllegroFlare::FrameAnimation::Frame> fly_frames = actual["fly"].get_frames();
   EXPECT_EQ(7,   fly_frames[0].get_index());
   EXPECT_FLOAT_EQ(0.16, fly_frames[0].get_duration());
   EXPECT_EQ(8,   fly_frames[1].get_index());
   EXPECT_FLOAT_EQ(0.08, fly_frames[1].get_duration());

   EXPECT_EQ(AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_LOOP, actual["fly"].get_playmode());
}


