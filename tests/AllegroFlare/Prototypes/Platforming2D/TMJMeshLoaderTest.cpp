
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/TMJMeshLoader.hpp>

// TODO: improve this:
#if defined(_WIN32) || defined(_WIN64)
#define TMJ_FIXTURE_PATH "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/"
#else
#define TMJ_FIXTURE_PATH "/Users/markoates/Repos/allegro_flare/tests/fixtures/"
#endif
#define TMJ_FIXTURE_FILENAME "map1-02.tmj"
#define TMJ_FIXTURE_WITH_BACKGROUND_FILENAME "map1-with_background-02.tmj"
//#define TILE_ATLAS_FILENAME "tiles_dungeon_v1.1.png"

class AllegroFlare_Prototypes_Platforming2D_TMJMeshLoaderTest : public ::testing::Test{};
class AllegroFlare_Prototypes_Platforming2D_TMJMeshLoaderTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture {};



TEST(AllegroFlare_Prototypes_Platforming2D_TMJMeshLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::TMJMeshLoader tmjmesh_loader;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJMeshLoaderTestWithAllegroRenderingFixture,
   load__returns_true)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   bitmap_bin.set_full_path(TMJ_FIXTURE_PATH);
   AllegroFlare::Prototypes::Platforming2D::TMJMeshLoader tmjmesh_loader(
         &bitmap_bin,
         std::string(TMJ_FIXTURE_PATH) + TMJ_FIXTURE_FILENAME
      );

   ASSERT_EQ(true, tmjmesh_loader.load());

   delete tmjmesh_loader.get_mesh();
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJMeshLoaderTestWithAllegroRenderingFixture,
   load__creates_the_mesh_filled_with_the_expected_data)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   bitmap_bin.set_full_path(TMJ_FIXTURE_PATH);
   AllegroFlare::Prototypes::Platforming2D::TMJMeshLoader tmjmesh_loader(
         &bitmap_bin,
         std::string(TMJ_FIXTURE_PATH) + TMJ_FIXTURE_FILENAME
      );

   tmjmesh_loader.load();

   AllegroFlare::TileMaps::PrimMesh *mesh = tmjmesh_loader.get_mesh();

   ASSERT_NE(nullptr, mesh);
   EXPECT_EQ(15, mesh->get_num_rows());
   EXPECT_EQ(25, mesh->get_num_columns());
   // TODO: include more data members

   delete mesh;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJMeshLoaderTestWithAllegroRenderingFixture,
   load__creates_the_collision_tile_map_filled_with_the_expected_data)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   bitmap_bin.set_full_path(TMJ_FIXTURE_PATH);
   AllegroFlare::Prototypes::Platforming2D::TMJMeshLoader tmjmesh_loader(
         &bitmap_bin,
         std::string(TMJ_FIXTURE_PATH) + TMJ_FIXTURE_FILENAME
      );

   tmjmesh_loader.load();

   AllegroFlare::TileMaps::TileMap<int> *collision_tile_map = tmjmesh_loader.get_collision_tile_map();

   ASSERT_NE(nullptr, collision_tile_map);
   //EXPECT_EQ(15, mesh->get_num_rows());
   // TODO: include more data members

   delete collision_tile_map;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJMeshLoaderTestWithAllegroRenderingFixture, CAPTURE__works_as_expected)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   bitmap_bin.set_full_path(TMJ_FIXTURE_PATH);
   AllegroFlare::Prototypes::Platforming2D::TMJMeshLoader tmjmesh_loader(
         &bitmap_bin,
         std::string(TMJ_FIXTURE_PATH) + TMJ_FIXTURE_FILENAME
      );

   tmjmesh_loader.load();

   AllegroFlare::TileMaps::PrimMesh *mesh = tmjmesh_loader.get_mesh();
   mesh->render();
   al_flip_display();
   //sleep(2.0);

   delete mesh;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_TMJMeshLoaderTestWithAllegroRenderingFixture,
   load__when_a_background_tilelayer_is_present__creates_the_background_tile_map_filled_with_the_expected_data)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   bitmap_bin.set_full_path(TMJ_FIXTURE_PATH);
   AllegroFlare::Prototypes::Platforming2D::TMJMeshLoader tmjmesh_loader(
         &bitmap_bin,
         std::string(TMJ_FIXTURE_PATH) + TMJ_FIXTURE_WITH_BACKGROUND_FILENAME
      );

   tmjmesh_loader.load();

   AllegroFlare::TileMaps::PrimMesh *background_mesh = tmjmesh_loader.get_background_mesh();

   ASSERT_NE(nullptr, background_mesh);
   EXPECT_EQ(15, background_mesh->get_num_rows());
   EXPECT_EQ(25, background_mesh->get_num_columns());
   EXPECT_EQ(174, background_mesh->get_tile_id(20, 3));

   delete background_mesh;
}


