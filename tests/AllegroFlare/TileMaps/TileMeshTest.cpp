

#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

class AllegroFlare_TileMaps_PrimMeshWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
   //AllegroFlare_TileMaps_PrimMeshWithAllegroRenderingFixtureTest()
      //: AllegroFlare::Testing::WithAllegroRenderingFixture(
     //     "/Users/markoates/Repos/Tilo/tests/fixtures/",
      //    "/Users/markoates/Repos/Tilo/tests/fixtures/"
      //)
   //{}
   //virtual ~AllegroFlare_TileMaps_PrimMeshWithAllegroRenderingFixtureTest() {}
};


#include <AllegroFlare/TileMaps/PrimMesh.hpp>

const std::string TEST_TILE_MAP_BITMAP = "tiles_dungeon_v1.1.png";

#include <AllegroFlare/Random.hpp>
#include <allegro5/allegro_color.h>


TEST_F(AllegroFlare_TileMaps_PrimMeshWithAllegroRenderingFixtureTest, render__without_initialized__throws_an_error)
{
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   AllegroFlare::TileMaps::PrimMesh mesh(&atlas);

   //ASSERT_THROW_WITH_MESSAGE(
   //   mesh.render(nullptr),
   //   std::runtime_error,
   //   "[AllegroFlare::TileMaps::PrimMesh::render] error: initialized can not be nullptr"
   //);
}


TEST_F(AllegroFlare_TileMaps_PrimMeshWithAllegroRenderingFixtureTest,
   initialize__will_set_the_number_of_vertexes_to_the_expected_amount)
{
   return;

   ALLEGRO_BITMAP *atlas_bitmap = get_bitmap_bin_ref()[TEST_TILE_MAP_BITMAP];
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   AllegroFlare::TileMaps::PrimMesh mesh(&atlas, 30, 20, 16, 16);
   atlas.duplicate_bitmap_and_load(atlas_bitmap, 16, 16);
   mesh.initialize();

   ASSERT_EQ(30*20*6, mesh.get_vertexes_ref().size());
}


TEST_F(AllegroFlare_TileMaps_PrimMeshWithAllegroRenderingFixtureTest,
   get_real_width__will_return_the_real_world_horizontal_size_of_the_mesh)
{
   // TODO
}


TEST_F(AllegroFlare_TileMaps_PrimMeshWithAllegroRenderingFixtureTest,
   get_real_height__will_return_the_real_world_vertical_size_of_the_mesh)
{
   // TODO
}


TEST_F(AllegroFlare_TileMaps_PrimMeshWithAllegroRenderingFixtureTest,
   CAPTURE__VISUAL__render__will_render_the_mesh_as_expected)
{
   ALLEGRO_BITMAP *atlas_bitmap = get_bitmap_bin_ref()[TEST_TILE_MAP_BITMAP];
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;

   AllegroFlare::TileMaps::PrimMesh mesh(&atlas, 30, 10, 16, 16);
   atlas.duplicate_bitmap_and_load(atlas_bitmap, 16, 16);
   mesh.initialize();

   AllegroFlare::Random random;
   for (int y=0; y<mesh.get_num_rows(); y++)
   {
      for (int x=0; x<mesh.get_num_columns(); x++)
      {
         int random_tile = random.get_random_int(0, atlas.get_tile_index_size());
         //int random_tile = 1;
         mesh.set_tile_id(x, y, random_tile);
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
   al_rest(1.0);
}



TEST_F(AllegroFlare_TileMaps_PrimMeshWithAllegroRenderingFixtureTest,
   rescale_tile_dimensions_to__will_resize_all_of_the_vertexes_to_the_new_dimensions)
{
   ALLEGRO_BITMAP *atlas_bitmap = get_bitmap_bin_ref()[TEST_TILE_MAP_BITMAP];
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;

   AllegroFlare::TileMaps::PrimMesh mesh(&atlas, 30, 10, 1, 1); // Set the initial tile size to 1
   atlas.duplicate_bitmap_and_load(atlas_bitmap, 16, 16);
   mesh.initialize();

   // Fill the tile mesh with random values
   AllegroFlare::Random random;
   for (int y=0; y<mesh.get_num_rows(); y++)
   {
      for (int x=0; x<mesh.get_num_columns(); x++)
      {
         int random_tile = random.get_random_int(0, atlas.get_tile_index_size());
         mesh.set_tile_id(x, y, random_tile);
      }
   }

   // Rescale the tile dimensions to something more arbitrary
   mesh.rescale_tile_dimensions_to(24, 24);

   al_clear_to_color(al_color_name("dodgerblue"));

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

   al_flip_display();
   al_rest(1.0);
}


TEST_F(AllegroFlare_TileMaps_PrimMeshWithAllegroRenderingFixtureTest,
   DISABLED__rescale_tile_dimensions_to__with_any_argument_with_a_value_less_than_or_equal_to_zero__will_throw_an_error)
{
   // TODO
}





/*

#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <vector>


namespace AllegroFlare::TileMaps
{
   // TODO: Consider renaming this to TileMesh (also renaming PrimMeshAtlas to TileMeshAtlas)
   class PrimMesh
   {
   private:
      AllegroFlare::TileMaps::PrimMeshAtlas *atlas;
      std::vector<ALLEGRO_VERTEX> vertexes;
      ALLEGRO_VERTEX_BUFFER *vertex_buffer;
         // NOTE: "vertex_buffer" features are disabled for now, because the specific operation "set_tile_uv" is
         // astronimacally slow at init time when loading the tile maps.  There could be a "refresh_vertex_buffer" in
         // the future, but there are many users of this PrimMesh class and everything would need to be updated
         // downstream
      std::vector<int> tile_ids;
      int num_columns;
      int num_rows;
      int tile_width;
      int tile_height;
      bool initialized;
      bool yz_swapped;

      void set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2);
      int infer_num_vertexes();

   public:
      PrimMesh(
         AllegroFlare::TileMaps::PrimMeshAtlas *atlas=nullptr,
         int num_columns=0,
         int num_rows=0,
         int tile_width=1,
         int tile_heigh=1
      );
      ~PrimMesh();

      void initialize();
      bool get_initialized();

      void resize(int num_columns=0, int num_rows=0); // should be renamed clear_and_resize()

      std::vector<ALLEGRO_VERTEX> &get_vertexes_ref();

      int get_num_columns() const;
      int get_num_rows() const;
      int infer_num_tiles() const;

      void rescale_tile_dimensions_to(int new_tile_width, int new_tile_height);
      void set_tile_width(int tile_width);
      void set_tile_height(int tile_height);
      int get_tile_width() const;
      int get_tile_height() const;
      int get_real_width() const;
      int get_real_height() const;

      bool set_tile_id(int tile_x, int tile_y, int tile_id);
      int get_tile_id(int tile_x, int tile_y) const;
      std::vector<int> get_tile_ids() const;
      AllegroFlare::TileMaps::PrimMeshAtlas *get_atlas() const;
      void set_atlas(AllegroFlare::TileMaps::PrimMeshAtlas *atlas);
   
      void swap_yz();
      void render(bool draw_outline=false);
   };
}


*/



