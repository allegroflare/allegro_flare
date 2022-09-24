
#include <gtest/gtest.h>

#include <Wicked/LevelLoader.hpp>

TEST(Wicked_LevelLoaderTest, can_be_created_without_blowing_up)
{
   LevelLoader level_loader;
}


TEST(Wicked_LevelLoaderTest, to_json__will_serialize_a_tileo_atlas_as_expected)
{
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   atlas.set_bitmap_filename("some-atlas-bitmap.png");

   nlohmann::json j = atlas;

   std::string expected_values =
R"({
  "bitmap_filename": "some-atlas-bitmap.png",
  "tile_height": 1,
  "tile_spacing": 0,
  "tile_width": 1
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(Wicked_LevelLoaderTest, to_json__will_serialize_a_tileo_mesh_as_expected)
{
   //AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   //atlas.set_bitmap_filename("some-atlas-bitmap.png");
   AllegroFlare::TileMaps::PrimMesh mesh;

   nlohmann::json j = mesh;

   std::string expected_values =
R"({
  "num_columns": 0,
  "num_rows": 0,
  "tiles": []
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(Wicked_LevelLoaderTest, to_json__with_an_atlas_present__will_serialize_a_tileo_mesh_as_expected)
{
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   atlas.set_bitmap_filename("some-atlas-bitmap.png");
   AllegroFlare::TileMaps::PrimMesh mesh(&atlas);

   nlohmann::json j = mesh;
   nlohmann::json atlas_j = j["atlas"];

   std::string expected_values =
R"({
  "bitmap_filename": "some-atlas-bitmap.png",
  "tile_height": 1,
  "tile_spacing": 0,
  "tile_width": 1
})";

   std::string actual_values = atlas_j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(Wicked_LevelLoaderTest, from_json__will_serialize_a_tileo_atlas_as_expected)
{
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;

   std::string atlas_json =
R"({
  "atlas": {
    "bitmap_filename": "some-atlas-bitmap.png",
    "tile_height": 9,
    "tile_spacing": 2,
    "tile_width": 6
  }
})";

   nlohmann::json parsed_json = nlohmann::json::parse(atlas_json);

   parsed_json.at("atlas").get_to(atlas);

   EXPECT_EQ("some-atlas-bitmap.png", atlas.get_bitmap_filename());
   EXPECT_EQ(6, atlas.get_tile_width());
   EXPECT_EQ(9, atlas.get_tile_height());
   EXPECT_EQ(2, atlas.get_tile_spacing());
}


TEST(Wicked_LevelLoaderTest, from_json__will_leave_the_atlas_in_an_invalid_state_requiring_a_refresh)
{
   // TODO
   // and actually this would duplicate testing that should be in AllegroFlare::TileMaps::PrimMeshAtlas
}



