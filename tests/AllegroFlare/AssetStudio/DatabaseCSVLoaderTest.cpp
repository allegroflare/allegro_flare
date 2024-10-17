
#include <gtest/gtest.h>

#include <AllegroFlare/AssetStudio/DatabaseCSVLoader.hpp>
#include <AllegroFlare/BitmapBin.hpp>


// TODO: Consider loading some test data csv, and then separately from the production data set
//#define ASSETS_FULL_PATH "/Users/markoates/Assets/"
//#define ASSETS_FULL_PATH "/Volumes/markoates/Assets/"
#define ASSETS_FULL_PATH "/Users/markoates/Assets/"
#define ASSETS_DB_CSV_FILENAME ASSETS_FULL_PATH "assets_db.csv"


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
}



/*
         int id;
         std::string identifier;
         int source_csv_column_num;
         std::string status;
         bool visibility;
         std::string type;
         std::string asset_pack_identifier;
         std::string intra_pack_identifier;
         int cell_width;
         int cell_height;
         float align_x;
         float align_y;
         float align_in_container_x;
         float align_in_container_y;
         float anchor_x;
         float anchor_y;
         std::string image_filename;
         std::vector<std::string> images_list;
         std::string full_path_to_initial_image;
         std::string playmode;
         //std::vector<int> extracted_palette_data;
         std::string notes;
         int frame_data__build_n_frames__num_frames;
         int frame_data__build_n_frames__start_from_frame;
         float frame_data__build_n_frames__each_frame_duration;
         bool frame_data__in_hash;
         Record();
         ~Record();
*/




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
   load__when_loading_from_the_source_data__will_create_the_expected_records)
{
   al_init();
   al_init_image_addon();

   AllegroFlare::BitmapBin assets_bitmap_bin;
   assets_bitmap_bin.set_full_path(ASSETS_FULL_PATH);
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_assets_bitmap_bin(&assets_bitmap_bin);
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load();

   EXPECT_EQ(true, loader.asset_exists("seethingswarm/catset/cat01_walk_strip8"));

   assets_bitmap_bin.clear();
   al_uninstall_system();
}


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest,
   //load__when_loading_from_the_source_data__will_create_the_expected_records)
   load__when_loading_from_the_source_data__will_load_records_with_the_expected_data)
{
   // TODO: Consider testing more records and more values on the loaded data
   al_init();
   al_init_image_addon();

   AllegroFlare::BitmapBin assets_bitmap_bin;
   assets_bitmap_bin.set_full_path(ASSETS_FULL_PATH);
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_assets_bitmap_bin(&assets_bitmap_bin);
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load();

   ASSERT_EQ(true, loader.asset_exists("seethingswarm/catset/cat01_walk_strip8"));
   AllegroFlare::AssetStudio::Asset *actual_asset = loader.find_asset("seethingswarm/catset/cat01_walk_strip8");
   ASSERT_NE(nullptr, actual_asset);
   ASSERT_NE(nullptr, actual_asset->animation);

   AllegroFlare::FrameAnimation::Animation animation = *actual_asset->animation;
   animation.initialize();
   EXPECT_EQ(8, animation.get_num_frames());
   for (auto &frame : animation.get_frames())
   {
      //EXPECT_EQ(0.425f, frame.get_align_in_container_y());
      EXPECT_EQ(1.0f, frame.get_align_in_container_y());
   }

   assets_bitmap_bin.clear();
   al_uninstall_system();
}


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest,
   // TODO: Re-enable this test
   DISABLED__load__when_loading_from_the_source_data__will_load_records_with_the_expected_data_2)
{
   al_init();
   al_init_image_addon();

   AllegroFlare::BitmapBin assets_bitmap_bin;
   assets_bitmap_bin.set_full_path(ASSETS_FULL_PATH);
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_assets_bitmap_bin(&assets_bitmap_bin);
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load();

   ASSERT_EQ(true, loader.asset_exists("grotto_walk"));

   AllegroFlare::AssetStudio::Asset *actual_asset = loader.find_asset("grotto_walk");
   ASSERT_NE(nullptr, actual_asset);
   EXPECT_EQ(1, actual_asset->id);
   EXPECT_EQ("grotto_walk", actual_asset->identifier);

   // Check the setup on the animation
   ASSERT_NE(nullptr, actual_asset->animation);
   EXPECT_EQ(3, actual_asset->animation->get_frames().size());

   assets_bitmap_bin.clear();
   al_uninstall_system();
}


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest, load__on_production_csv__will_not_blow_up)
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


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest, load_records__on_production_csv__will_not_blow_up)
{
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load_records();
   EXPECT_NE(0, loader.num_records()); // Number of assets will change, as long as it's not 0
}


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest,
   record_exists__on_production_csv__will_return_true_on_records_that_exist)
{
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load_records();

   // Cherry pick some specific assets
   EXPECT_EQ(true, loader.record_exists("ansimuz/warped-humanoid-enemies/roboid"));
   EXPECT_EQ(true, loader.record_exists("ansimuz/warped-explosions-pack-8/explosion-g"));
   EXPECT_EQ(true, loader.record_exists("seethingswarm/bunnypack/bunny_sit_strip12"));
   EXPECT_EQ(true, loader.record_exists("seethingswarm/catset/cat01_jump_strip4"));
}


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest,
   record_exists__on_production_csv__will_return_false_on_records_that_do_not_exist)
{
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load_records();
   EXPECT_EQ(false, loader.record_exists("an/asset/that/does-not-exist"));
}


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest, comma_separated_quoted_strings_to_vector_of_strings__will_split_\
a_string_as_expected)
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


