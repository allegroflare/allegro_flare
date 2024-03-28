
#include <gtest/gtest.h>

#include <AllegroFlare/AssetStudio/Database.hpp>


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


