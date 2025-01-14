
#include <gtest/gtest.h>

#include <AllegroFlare/Integrations/AssetStudioDatabaseValidator.hpp>
#include <AllegroFlare/AssetStudio/Database.hpp>
#include <AllegroFlare/AssetStudio/DatabaseCSVLoader.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>


// TODO: See if this hard-coded pathing can be improved - move it to a fixture variable, in-test variable, for example
#define ASSETS_FULL_PATH "/Users/markoates/Assets/"
#define ASSETS_DB_CSV_FILENAME ASSETS_FULL_PATH "assets_db.csv"


TEST(AllegroFlare_Integrations_AssetStudioDatabaseValidatorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Integrations::AssetStudioDatabaseValidator validator;
}


// TODO: Add these tests

// TODO: Add test on assets_bitmap_bin guard


TEST(AllegroFlare_Integrations_AssetStudioDatabaseValidatorTest, load_records__on_production_database__will_not_blow_up)
{
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load_records();
}


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest,
   when_loading_records_from_the_assets_db_csv_file__will_work_as_expected)
{
   al_init();
   al_init_image_addon();

   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load_records();

   EXPECT_EQ(true, loader.record_exists("seethingswarm/catset/cat01_walk_strip8"));
   // TODO: Consider testing additional records and fields

   al_uninstall_system();
}


TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest,
   when_loading_assets_from_records_imported_from_the_csv_records__will_work_as_expected)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string data_path = deployment_environment.get_data_folder_path();

   al_init();
   al_init_image_addon();

   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_csv_full_path(ASSETS_DB_CSV_FILENAME);
   loader.load_records();

   AllegroFlare::BitmapBin assets_bitmap_bin;
   assets_bitmap_bin.set_full_path("/Users/markoates/Assets/");
   AllegroFlare::AssetStudio::Database database;
   database.set_assets_bitmap_bin(&assets_bitmap_bin);
   database.set_global_records(loader.get_records());
   database.load_all_global_assets_from_all_global_records();

   //EXPECT_EQ(true, loader.record_exists("seethingswarm/catset/cat01_walk_strip8"));
   // TODO: Destroy database?

   al_uninstall_system();
}


/*
TEST(AllegroFlare_AssetStudio_DatabaseCSVLoaderTest,
   //load__when_loading_from_the_source_data__will_create_the_expected_records)
   load__when_loading_from_the_source_data__will_load_assets_with_the_expected_data)
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
   DISABLED__load__when_loading_from_the_source_data__will_load_assets_with_the_expected_data_2)
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

*/
