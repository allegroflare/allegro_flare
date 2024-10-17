
#include <gtest/gtest.h>

#include <AllegroFlare/AssetStudio/Database.hpp>


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


TEST(AllegroFlare_AssetStudio_DatabaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AssetStudio::Database database;
}


TEST(AllegroFlare_AssetStudio_DatabaseTest,
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


TEST(AllegroFlare_AssetStudio_DatabaseTest,
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


TEST(AllegroFlare_AssetStudio_DatabaseTest,
   record_identifiers__will_return_the_list_of_records_that_are_present)
{
   AllegroFlare::AssetStudio::Database database;
   std::vector<AllegroFlare::AssetStudio::Record> records = {
      build_basic_record("foobar", "animation"),
      build_basic_record("boobaz", "animation"),
      build_basic_record("blabla", "tileset"),
   };
   database.set_records(records);
   std::set<std::string> expected_record_identifiers = {
      "foobar", "boobaz", "blabla",
   };
   std::set<std::string> actual_record_identifiers = database.record_identifiers();
   EXPECT_EQ(expected_record_identifiers, actual_record_identifiers);
}


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


