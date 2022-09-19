

#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

class Tileo_MeshWithAllegroRenderingFixtureTest : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
   //Tileo_MeshWithAllegroRenderingFixtureTest()
      //: AllegroFlare::Testing::WithAllegroRenderingFixture(
     //     "/Users/markoates/Repos/Tilo/tests/fixtures/",
      //    "/Users/markoates/Repos/Tilo/tests/fixtures/"
      //)
   //{}
   //virtual ~Tileo_MeshWithAllegroRenderingFixtureTest() {}
};


#include <Tileo/Mesh.hpp>

const std::string TEST_TILE_MAP_BITMAP = "tiles_dungeon_v1.1.png";

#include <AllegroFlare/Random.hpp>
#include <allegro5/allegro_color.h>


TEST_F(Tileo_MeshWithAllegroRenderingFixtureTest, render__without_initialized__throws_an_error)
{
   Tileo::Atlas atlas;
   Tileo::Mesh mesh(&atlas);

   //ASSERT_THROW_WITH_MESSAGE(
   //   mesh.render(nullptr),
   //   std::runtime_error,
   //   "[Tileo::Mesh;:render] error: initialized can not be nullptr"
   //);
}


TEST_F(Tileo_MeshWithAllegroRenderingFixtureTest, initialize__will_set_the_number_of_vertexes_to_the_expected_amount)
{
   return;

   ALLEGRO_BITMAP *atlas_bitmap = get_bitmap_bin_ref()[TEST_TILE_MAP_BITMAP];
   Tileo::Atlas atlas;
   Tileo::Mesh mesh(&atlas, 30, 20, 16, 16);
   atlas.duplicate_bitmap_and_load(atlas_bitmap, 16, 16);
   mesh.initialize();

   ASSERT_EQ(30*20*6, mesh.get_vertexes_ref().size());
}


TEST_F(Tileo_MeshWithAllegroRenderingFixtureTest,
   get_real_width__will_return_the_real_world_horizontal_size_of_the_mesh)
{
   // TODO
}


TEST_F(Tileo_MeshWithAllegroRenderingFixtureTest, get_real_height__will_return_the_real_world_vertical_size_of_the_mesh)
{
   // TODO
}


TEST_F(Tileo_MeshWithAllegroRenderingFixtureTest, render__will_render_the_mesh_as_expected)
{
   return;

   ALLEGRO_BITMAP *atlas_bitmap = get_bitmap_bin_ref()[TEST_TILE_MAP_BITMAP];
   Tileo::Atlas atlas;

   Tileo::Mesh mesh(&atlas, 30, 10, 16, 16);
   atlas.duplicate_bitmap_and_load(atlas_bitmap, 16, 16);
   mesh.initialize();

   AllegroFlare::Random random;
   for (int y=0; y<mesh.get_num_rows(); y++)
   {
      for (int x=0; x<mesh.get_num_columns(); x++)
      {
         int random_tile = random.get_random_int(0, atlas.get_tile_index_size());
         //int random_tile = 1;
         mesh.set_tile(x, y, random_tile);
      }
   }

   al_clear_to_color(al_color_name("orange"));

   // render the actual mesh

   float x = 100;
   float y = 50;

   float sx = 3;
   float sy = 3;

   ALLEGRO_TRANSFORM prev, transform;
   al_copy_transform(&prev, al_get_current_transform());
   al_identity_transform(&transform);
   al_translate_transform(&transform, x, y);
   al_scale_transform(&transform, sx, sy);
   al_use_transform(&transform);

   mesh.render();

   al_use_transform(&prev);


   // flip the display and sleep
   al_flip_display();
   sleep(1);
}


