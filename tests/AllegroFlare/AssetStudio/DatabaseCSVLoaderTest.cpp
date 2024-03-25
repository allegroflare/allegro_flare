
#include <gtest/gtest.h>

#include <AllegroFlare/AssetStudio/DatabaseCSVLoader.hpp>
#include <AllegroFlare/BitmapBin.hpp>


// TODO: Consider loading some test data csv, and then separately from that the production data set
//#define ASSETS_FULL_PATH "/Users/markoates/Assets/"
//#define ASSETS_FULL_PATH "/Volumes/markoates/Assets/"
#define ASSETS_FULL_PATH "/Users/markoates/Assets/"
#define ASSETS_DB_CSV_FILENAME ASSETS_FULL_PATH "assets_db.csv"


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
}


// TODO: Add test on assets_bitmap_bin guard


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest, load__will_not_blow_up)
{
   al_init();
   al_init_image_addon();

   AllegroFlare::BitmapBin assets_bitmap_bin;
   assets_bitmap_bin.set_full_path(ASSETS_FULL_PATH);
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_assets_bitmap_bin(&assets_bitmap_bin);
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load();
   SUCCEED();

   assets_bitmap_bin.clear();
   al_uninstall_system();
}


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest,
   // TODO: Re-enable this test
   DISABLED__load__when_loading_from_the_source_data__will_create_the_expected_records)
{
   al_init();
   al_init_image_addon();

   AllegroFlare::BitmapBin assets_bitmap_bin;
   assets_bitmap_bin.set_full_path(ASSETS_FULL_PATH);
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_assets_bitmap_bin(&assets_bitmap_bin);
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load();

   EXPECT_EQ(true, loader.level_exists("grotto_walk"));

   assets_bitmap_bin.clear();
   al_uninstall_system();
}


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest,
   // TODO: Re-enable this test
   DISABLED__load__when_loading_from_the_source_data__will_load_records_with_the_expected_data)
{
   al_init();
   al_init_image_addon();

   AllegroFlare::BitmapBin assets_bitmap_bin;
   assets_bitmap_bin.set_full_path(ASSETS_FULL_PATH);
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_assets_bitmap_bin(&assets_bitmap_bin);
   //Robieo::CSVToLevelLoader loader;
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load();

   ASSERT_EQ(true, loader.level_exists("grotto_walk"));

   AllegroFlare::AssetStudio::Asset *actual_level = loader.find_level("grotto_walk");
   ASSERT_NE(nullptr, actual_level);
   EXPECT_EQ(1, actual_level->id);
   EXPECT_EQ("grotto_walk", actual_level->identifier);

   // Check the setup on the animation
   ASSERT_NE(nullptr, actual_level->animation);
   EXPECT_EQ(3, actual_level->animation->get_frames().size());
/*

   EXPECT_EQ("3. Forest", actual_level.get_title());
   EXPECT_EQ("level-4-13.obj", actual_level.get_world_model_obj_filename());
   EXPECT_EQ("level-4-13.png", actual_level.get_world_model_texture_filename());

   ASSERT_EQ(1, actual_level.get_tile_maps_ref().size());
   auto &tile_map = actual_level.get_tile_maps_ref()[0];
   //actual_level.get_tile_maps_ref().size());
   //EXPECT_EQ("the_cave.png", actual_level.get_tile_map_tile_elevation_bitmap_filename());
   //EXPECT_EQ("the_cave-type.png", actual_level.get_tile_map_tile_type_bitmap_filename());

   //EXPECT_EQ(AllegroFlare::Vec2D(22, 28), actual_level.get_tile_map_origin_offset());
   //EXPECT_EQ(10.0, actual_level.get_tile_map_ceiling_height());
   //EXPECT_EQ(0.0, actual_level.get_tile_map_groundlevel_height());
   //EXPECT_EQ(-2.0, actual_level.get_tile_map_floor_height());

   EXPECT_EQ("robot-holly_jolly", actual_level.get_song_to_perform_identifier());
   EXPECT_EQ(15.0, actual_level.get_song_to_perform_duration_sec());
*/

   assets_bitmap_bin.clear();
   al_uninstall_system();
}


TEST(Robieo_CSVToLevelLoaderTest, load__on_production_csv__will_not_blow_up)
{
   al_init();
   al_init_image_addon();

   AllegroFlare::BitmapBin assets_bitmap_bin;
   assets_bitmap_bin.set_full_path(ASSETS_FULL_PATH);
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_assets_bitmap_bin(&assets_bitmap_bin);
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load();
   SUCCEED();

   assets_bitmap_bin.clear();
   al_uninstall_system();
}


TEST(Robieo_CSVToLevelLoaderTest,
   comma_separated_quoted_strings_to_vector_of_strings__will_split_a_string_as_expected)
{
   std::vector<std::pair<std::string, std::vector<std::string>>> test_data = {
      { "\"foo\", \"bar\", \"baz\"", { "foo", "bar", "baz" } },
      { "\"foo, and comma\", \"should work\", \"as, expected\"", { "foo, and comma", "should work", "as, expected" } },
   };

   for (auto &test_datum : test_data)
   {
      std::string input_string = test_datum.first;
      std::vector<std::string> expected_parsed_data = test_datum.second;
      std::vector<std::string> actual_parsed_data =
         AllegroFlare::AssetStudio::DatabaseCSVLoader::comma_separated_quoted_strings_to_vector_of_strings(
               input_string
            );
      EXPECT_EQ(expected_parsed_data, actual_parsed_data) << input_string;
   }
}


