
#include <gtest/gtest.h>

#include <AllegroFlare/AssetStudio/Database.hpp>


TEST(AllegroFlare_AssetStudio_DatabaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AssetStudio::Database database;
}


TEST(AllegroFlare_AssetStudio_DatabaseTest,
   prefix_global_identifier_prefix_to_identifier__will_add_the_prefix_to_all_the_identifiers)
{
   AllegroFlare::AssetStudio::Database database;

   std::map<std::string, AllegroFlare::AssetStudio::Asset*> assets = {
      { "foobar", nullptr },
      { "boobaz", nullptr },
      { "blabla", nullptr },
   };

   database.set_assets(assets);
   database.prefix_global_identifier_prefix_to_identifiers("asset_studio::");

   std::set<std::string> expected_asset_identifiers = {
      "asset_studio::foobar", "asset_studio::boobaz", "asset_studio::blabla",
   };
   std::set<std::string> actual_asset_identifiers = database.asset_identifiers();

   EXPECT_EQ(expected_asset_identifiers, actual_asset_identifiers);
}


