
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/TMJTileMeshLoader.hpp>

// TODO: improve this:
#if defined(_WIN32) || defined(_WIN64)
#define TMJ_FIXTURE_PATH "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/"
#else
#define TMJ_FIXTURE_PATH "/Users/markoates/Repos/allegro_flare/tests/fixtures/"
#endif
#define TMJ_FIXTURE_FILENAME "map1-02.tmj"
#define TMJ_FIXTURE_WITH_BACKGROUND_FILENAME "map1-with_background-02.tmj"
//#define TILE_ATLAS_FILENAME "tiles_dungeon_v1.1.png"

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
      loader.set_tmj_filename(tmj_filename);
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
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   AllegroFlare::Prototypes::Platforming2D::TMJTileMeshLoader loader(
         &bitmap_bin,
         std::string(TMJ_FIXTURE_PATH) + TMJ_FIXTURE_FILENAME
      );

   ASSERT_EQ(true, loader.load());

   delete loader.get_mesh();
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTestWithAllegroRenderingFixture,
   load__creates_the_mesh_filled_with_the_expected_data)
{
   load_map(std::string(TMJ_FIXTURE_PATH) + TMJ_FIXTURE_FILENAME);

   AllegroFlare::TileMaps::PrimMesh *mesh = loader.get_mesh();

   ASSERT_NE(nullptr, mesh);
   EXPECT_EQ(15, mesh->get_num_rows());
   EXPECT_EQ(25, mesh->get_num_columns());
   // TODO: include more data members

   delete mesh;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTestWithAllegroRenderingFixture,
   load__creates_the_collision_tile_map_filled_with_the_expected_data)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   AllegroFlare::Prototypes::Platforming2D::TMJTileMeshLoader loader(
         &bitmap_bin,
         std::string(TMJ_FIXTURE_PATH) + TMJ_FIXTURE_FILENAME
      );

   loader.load();

   AllegroFlare::TileMaps::TileMap<int> *collision_tile_map = loader.get_collision_tile_map();

   ASSERT_NE(nullptr, collision_tile_map);
   //EXPECT_EQ(15, mesh->get_num_rows());
   // TODO: include more data members

   delete collision_tile_map;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTestWithAllegroRenderingFixture,
   CAPTURE__prim_mesh__will_appear_as_expected_when_rendered)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   AllegroFlare::Prototypes::Platforming2D::TMJTileMeshLoader loader(
         &bitmap_bin,
         std::string(TMJ_FIXTURE_PATH) + TMJ_FIXTURE_FILENAME
      );

   loader.load();

   AllegroFlare::TileMaps::PrimMesh *mesh = loader.get_mesh();
   mesh->render();
   al_flip_display();
   sleep(1.0);

   delete mesh;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJTileMeshLoaderTestWithAllegroRenderingFixture,
   load__when_a_background_tilelayer_is_present__creates_the_background_tile_map_filled_with_the_expected_data)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   AllegroFlare::Prototypes::Platforming2D::TMJTileMeshLoader loader(
         &bitmap_bin,
         std::string(TMJ_FIXTURE_PATH) + TMJ_FIXTURE_WITH_BACKGROUND_FILENAME
      );

   loader.load();

   AllegroFlare::TileMaps::PrimMesh *background_mesh = loader.get_background_mesh();

   ASSERT_NE(nullptr, background_mesh);
   EXPECT_EQ(15, background_mesh->get_num_rows());
   EXPECT_EQ(25, background_mesh->get_num_columns());
   EXPECT_EQ(174, background_mesh->get_tile_id(20, 3));

   delete background_mesh;
}


