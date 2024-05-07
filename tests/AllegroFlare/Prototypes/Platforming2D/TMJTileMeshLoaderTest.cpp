
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/TMJTileMeshLoader.hpp>

#define TMJ_FIXTURE_FILENAME "map1-02.tmj"
#define TMJ_FIXTURE_WITH_BACKGROUND_FILENAME "map1-with_background-02.tmj"
#define TMJ_FIXTURE_WITH_BACKGROUND_AND_FOREGROUND_FILENAME "map1-with_background_and_foreground-02.tmj"
#define TMJ_FIXTURE_WITH_FLIPPED_TILES "map_with_flipped_tiles.tmj"
#define TILE_ATLAS_FILENAME "tiles_dungeon_v1.1.png"

class AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTest : public ::testing::Test{};
class AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
      AllegroFlare::Prototypes::Platforming2D::TMJTileMeshLoader loader;

public:
   void load_map(std::string tmj_filename)
   {
      loader.set_bitmap_bin(&get_bitmap_bin_ref());
      loader.set_tmj_filename(get_fixtures_path() + tmj_filename);
      loader.set_tile_atlas_bitmap_identifier(TILE_ATLAS_FILENAME);

      loader.load();
   }
};



TEST(AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::TMJTileMeshLoader loader;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTestWithAllegroRenderingFixture,
   load__returns_true)
{
   loader.set_bitmap_bin(&get_bitmap_bin_ref());
   loader.set_tmj_filename(get_fixtures_path() + TMJ_FIXTURE_FILENAME);
   loader.set_tile_atlas_bitmap_identifier(TILE_ATLAS_FILENAME);

   ASSERT_EQ(true, loader.load());

   delete loader.get_terrain_mesh();
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTestWithAllegroRenderingFixture,
   load__creates_the_terrain_mesh_filled_with_the_expected_data)
{
   load_map(TMJ_FIXTURE_FILENAME);

   AllegroFlare::TileMaps::TileMesh *terrain_mesh = loader.get_terrain_mesh();

   ASSERT_NE(nullptr, terrain_mesh);
   EXPECT_EQ(15, terrain_mesh->get_num_rows());
   EXPECT_EQ(25, terrain_mesh->get_num_columns());
   // TODO: include more data members

   delete terrain_mesh;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTestWithAllegroRenderingFixture,
   load__creates_the_collision_tile_map_filled_with_the_expected_data)
{
   load_map(TMJ_FIXTURE_FILENAME);

   AllegroFlare::TileMaps::TileMap<int> *collision_tile_map = loader.get_collision_tile_map();

   ASSERT_NE(nullptr, collision_tile_map);
   // TODO: include more data members

   delete collision_tile_map;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTestWithAllegroRenderingFixture,
   load__when_a_background_tilelayer_is_present__creates_the_background_tile_map_filled_with_the_expected_data)
{
   load_map(TMJ_FIXTURE_WITH_BACKGROUND_FILENAME);

   AllegroFlare::TileMaps::TileMesh *background_mesh = loader.get_background_mesh();

   ASSERT_NE(nullptr, background_mesh);
   EXPECT_EQ(15, background_mesh->get_num_rows());
   EXPECT_EQ(25, background_mesh->get_num_columns());
   EXPECT_EQ(174, background_mesh->get_tile_id(20, 3));

   delete background_mesh;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTestWithAllegroRenderingFixture,
   CAPTURE__will_appear_as_expected_when_loaded_objects_are_rendered)
{
   load_map(TMJ_FIXTURE_WITH_BACKGROUND_AND_FOREGROUND_FILENAME);

   AllegroFlare::TileMaps::TileMesh *terrain_mesh = loader.get_terrain_mesh();
   AllegroFlare::TileMaps::TileMesh *background_mesh = loader.get_background_mesh();
   AllegroFlare::TileMaps::TileMesh *foreground_mesh = loader.get_foreground_mesh();

   float map_width = terrain_mesh->get_real_width();
   float map_height = terrain_mesh->get_real_height();

   AllegroFlare::Placement2D placement;
   placement.position = { 1920/2, 1080/2 };
   placement.size = { map_width, map_height };
   placement.scale = { 3.0f, 3.0f };

   // Render the subject
   placement.start_transform();
   background_mesh->render();
   terrain_mesh->render();
   foreground_mesh->render();
   al_flip_display();
   placement.restore_transform();

   sleep(1.0);

   delete terrain_mesh;
   delete background_mesh;
   delete foreground_mesh;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTestWithAllegroRenderingFixture,
   FOCUS__CAPTURE__with_tiles_that_are_flipped_vertically_and_horizontally__will_render_as_expected)
{
   load_map(TMJ_FIXTURE_WITH_FLIPPED_TILES);

   AllegroFlare::TileMaps::TileMesh *terrain_mesh = loader.get_terrain_mesh();
   float map_width = terrain_mesh->get_real_width();
   float map_height = terrain_mesh->get_real_height();


   AllegroFlare::Placement2D placement;
   placement.position = { 1920/2, 1080/2 };
   placement.size = { map_width, map_height };
   placement.scale = { 5.0f, 5.0f };

   // Render the subject
   placement.start_transform();
   terrain_mesh->render();
   al_flip_display();
   placement.restore_transform();

   sleep(1.0);

   delete terrain_mesh;
}


