
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


// TODO: Replace these tests with a test fixture file.

// TODO: Ensure there is at least one test that loads the production CSV, ensuring that it loads without error


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
   EXPECT_EQ(true, loader.record_exists("ansimuz/warped-humanoid-enemies/exoskeleton-crouch"));
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


