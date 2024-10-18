
#include <gtest/gtest.h>

#include <AllegroFlare/AssetStudio/Database.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>


class AllegroFlare_AssetStudio_DatabaseTest : public ::testing::Test {};
class AllegroFlare_AssetStudio_DatabaseTestWithSetup : public ::testing::Test
{
public:
   AllegroFlare::DeploymentEnvironment deployment_environment;
   AllegroFlare::BitmapBin assets_bitmap_bin;
   AllegroFlare::AssetStudio::Database database;
   ALLEGRO_DISPLAY *display; // display is needed for rendering

   AllegroFlare_AssetStudio_DatabaseTestWithSetup()
      : deployment_environment("test")
      , assets_bitmap_bin()
      , database()
      , display(nullptr)
   {}
   virtual void SetUp() override
   {
      al_init();
      al_init_image_addon();
      ALLEGRO_DISPLAY *display = al_create_display(800, 600);
      std::string data_path = deployment_environment.get_data_folder_path();
      assets_bitmap_bin.set_full_path(data_path + "assets");
      database.set_assets_bitmap_bin(&assets_bitmap_bin);
   }
   virtual void TearDown() override
   {
      assets_bitmap_bin.clear(); // TODO: Audit the requirements of the bitmap lifecycles
      al_shutdown_image_addon();
      al_destroy_display(display);
      al_uninstall_system();
   }
   static AllegroFlare::AssetStudio::Record build_record(
      std::string identifier,
      std::string type
   )
   {
      AllegroFlare::AssetStudio::Record result;
      result.identifier = identifier;
      result.type = type;
      result.asset_pack_identifier = "a_test_asset_pack";

      {
         result.image_filename = "robo-soldier6.png"; // TODO: Change this to images_list
         result.cell_width = 48;
         result.cell_height = 48;
         result.frame_data__build_n_frames__num_frames	= 1; //int
         result.frame_data__build_n_frames__start_from_frame = 0; //	int
         result.frame_data__build_n_frames__each_frame_duration	= 2.0; //float
         result.type = "animation"; // TODO: Change this to use an enum value
         result.playmode = "loop"; // TODO: Change this to use an enum value
      }
      result.frame_data__in_hash = "";
      return result;
   }
};


static AllegroFlare::AssetStudio::Record build_basic_record(
   std::string identifier,
   std::string type
)
{
   AllegroFlare::AssetStudio::Record result;
   result.identifier = identifier;
   result.type = type;
   return result;
}


TEST_F(AllegroFlare_AssetStudio_DatabaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AssetStudio::Database database;
}


TEST_F(AllegroFlare_AssetStudio_DatabaseTest,
   set_global_identifier_prefix__will_add_the_prefix_to_all_the_identifiers)
{
   AllegroFlare::AssetStudio::Database database;
   std::map<std::string, AllegroFlare::AssetStudio::Asset*> global_assets = {
      { "foobar", nullptr },
      { "boobaz", nullptr },
      { "blabla", nullptr },
   };
   database.set_global_assets(global_assets);
   database.set_global_identifier_prefix("asset_studio::");

   std::set<std::string> expected_asset_identifiers = {
      "asset_studio::foobar", "asset_studio::boobaz", "asset_studio::blabla",
   };
   std::set<std::string> actual_asset_identifiers = database.asset_identifiers();
   EXPECT_EQ(expected_asset_identifiers, actual_asset_identifiers);
}


TEST_F(AllegroFlare_AssetStudio_DatabaseTest,
   remove_global_identifier_prefix__will_remove_the_prefix_that_is_currently_in_place_from_all_identifiers)
{
   AllegroFlare::AssetStudio::Database database;
   std::map<std::string, AllegroFlare::AssetStudio::Asset*> global_assets = {
      { "foobar", nullptr },
      { "boobaz", nullptr },
      { "blabla", nullptr },
   };
   database.set_global_assets(global_assets);
   database.set_global_identifier_prefix("asset_studio::");
   //database.prefix_global_identifier_prefix_to_identifiers("asset_studio::");

   database.remove_global_identifier_prefix();
  
   std::set<std::string> expected_asset_identifiers = {
      "foobar", "boobaz", "blabla",
   };
   std::set<std::string> actual_asset_identifiers = database.asset_identifiers();
   EXPECT_EQ(expected_asset_identifiers, actual_asset_identifiers);
}


TEST_F(AllegroFlare_AssetStudio_DatabaseTest,
   global_record_identifiers__will_return_the_list_of_records_that_are_present)
{
   AllegroFlare::AssetStudio::Database database;
   std::vector<AllegroFlare::AssetStudio::Record> global_records = {
      build_basic_record("foobar", "animation"),
      build_basic_record("boobaz", "animation"),
      build_basic_record("blabla", "tileset"),
   };
   database.set_global_records(global_records);
   std::set<std::string> expected_global_record_identifiers = {
      "foobar", "boobaz", "blabla",
   };
   std::set<std::string> actual_global_record_identifiers = database.global_record_identifiers();
   EXPECT_EQ(expected_global_record_identifiers, actual_global_record_identifiers);
}


TEST_F(AllegroFlare_AssetStudio_DatabaseTest,
   local_record_identifiers__will_return_the_list_of_records_that_are_present)
{
   AllegroFlare::AssetStudio::Database database;
   std::vector<AllegroFlare::AssetStudio::Record> local_records = {
      build_basic_record("foobar", "animation"),
      build_basic_record("boobaz", "animation"),
      build_basic_record("blabla", "tileset"),
   };
   database.set_local_records(local_records);
   std::set<std::string> expected_local_record_identifiers = {
      "foobar", "boobaz", "blabla",
   };
   std::set<std::string> actual_local_record_identifiers = database.local_record_identifiers();
   EXPECT_EQ(expected_local_record_identifiers, actual_local_record_identifiers);
}


TEST_F(AllegroFlare_AssetStudio_DatabaseTestWithSetup, load_asset__when_given_a_global_asset_record_identifier__will_\
load_a_global_asset_into_global_assets_with_the_expected_values)
{
   database.set_global_records({
      build_record("a_simple_asset", "animation"),
   });

   database.load_asset("a_simple_asset");

   EXPECT_EQ(true, database.asset_exists("a_simple_asset"));

   // TODO: Validate the loaded contents
   // TODO: Consider the lifecycle state of the asset_bitmap_bin
   // TODO: Validate the sprite_sheets
}


// TODO: Repeat the above test for local_assets


/*
TEST(AllegroFlare_AssetStudio_DatabaseTest,
   // NOTE: This method under test is private, so this test is DISABLED
   DISABLED__prefix_global_identifier_prefix_to_identifier__will_add_the_prefix_to_all_the_identifiers)
{
   AllegroFlare::AssetStudio::Database database;

   std::map<std::string, AllegroFlare::AssetStudio::Asset*> global_assets = {
      { "foobar", nullptr },
      { "boobaz", nullptr },
      { "blabla", nullptr },
   };

   database.set_global_assets(global_assets);
   database.prefix_global_identifier_prefix_to_identifiers("asset_studio::");

   std::set<std::string> expected_asset_identifiers = {
      "asset_studio::foobar", "asset_studio::boobaz", "asset_studio::blabla",
   };
   std::set<std::string> actual_asset_identifiers = database.asset_identifiers();

   EXPECT_EQ(expected_asset_identifiers, actual_asset_identifiers);
}


TEST(AllegroFlare_AssetStudio_DatabaseTest,
   // NOTE: This method under test is private, so this test is DISABLED
   DISABLED__prefix_global_identifier_prefix_to_identifier__will_set_using_global_identifier_prefix_to_true)
{
   AllegroFlare::AssetStudio::Database database;
   std::map<std::string, AllegroFlare::AssetStudio::Asset*> global_assets = { { "foobar", nullptr }, };
   database.set_global_assets(global_assets);

   database.prefix_global_identifier_prefix_to_identifiers("asset_studio::");

   EXPECT_EQ(true, database.get_using_global_identifier_prefix());
}


TEST(AllegroFlare_AssetStudio_DatabaseTest,
   // NOTE: This method under test is private, so this test is DISABLED
   DISABLED__remove_global_identifier_prefixes__will_remove_the_prefix_that_is_currently_in_place_from_all_identifiers)
{
   AllegroFlare::AssetStudio::Database database;
   std::map<std::string, AllegroFlare::AssetStudio::Asset*> global_assets = {
      { "foobar", nullptr },
      { "boobaz", nullptr },
      { "blabla", nullptr },
   };
   database.set_global_assets(global_assets);
   database.prefix_global_identifier_prefix_to_identifiers("asset_studio::");

   database.remove_global_identifier_prefixes();
  
   std::set<std::string> expected_asset_identifiers = {
      "foobar", "boobaz", "blabla",
   };
   std::set<std::string> actual_asset_identifiers = database.asset_identifiers();
   EXPECT_EQ(expected_asset_identifiers, actual_asset_identifiers);
}
*/


