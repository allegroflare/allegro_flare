

#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/TileMaps/TileMesh.hpp>

const std::string TEST_TILE_MAP_BITMAP = "tiles_dungeon_v1.1.png";
#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro_color.h>


class AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   ALLEGRO_BITMAP *atlas_bitmap;
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   AllegroFlare::TileMaps::TileMesh mesh; //(&atlas, 30, 10, 1, 1); // Set the initial tile size to 1

   AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup()
      : atlas_bitmap(nullptr)
      , atlas()
      , mesh()
   {}

   void SetUp() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();

      atlas_bitmap = get_bitmap_bin_ref()[TEST_TILE_MAP_BITMAP];
      atlas.duplicate_bitmap_and_load(atlas_bitmap, 16, 16);
      get_bitmap_bin_ref().destroy(TEST_TILE_MAP_BITMAP);

      mesh.set_atlas(&atlas);
      mesh.set_num_columns(20);
      mesh.set_num_rows(10);
      mesh.set_tile_width(16);
      mesh.set_tile_height(16);

      mesh.initialize();
   }

   void TearDown() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::TearDown();
   }

   void fill_with_random_tiles(std::vector<int> possible_random_tiles = {})
   {
      mesh.enable_holding_vertex_buffer_update_until_refresh();
      AllegroFlare::Random random;
      for (int y=0; y<mesh.get_num_rows(); y++)
      {
         for (int x=0; x<mesh.get_num_columns(); x++)
         {
            int random_tile = 0;

            if (possible_random_tiles.empty())
            {
               random_tile = random.get_random_int(0, atlas.get_tile_index_size());
            }
            else
            {
               random_tile = possible_random_tiles[random.get_random_int(0, possible_random_tiles.size()-1)];
            }
            mesh.set_tile_id(x, y, random_tile);
         }
      }
      mesh.refresh_vertex_buffer();
   }

   void render_subject(float duration_sec=1.0f)
   {
      AllegroFlare::Placement2D subject_placement;
      subject_placement.position = { 1920/2, 1080/2 };
      subject_placement.scale = { 4.0f, 4.0f };
      subject_placement.size = { (float)mesh.get_real_width(), (float)mesh.get_real_height() };
      subject_placement.align = { 0.5f, 0.5f };

      clear();

      subject_placement.start_transform();
      mesh.render();
      subject_placement.restore_transform();

      al_flip_display();
      al_rest(duration_sec);
   }
};


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTest, render__without_initialized__throws_an_error)
{
   AllegroFlare::TileMaps::TileMesh mesh;

   ASSERT_THROW_WITH_MESSAGE(
      mesh.render(),
      std::runtime_error,
      "TileMesh::render: error: guard \"initialized\" not met"
   );
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTest,
   initialize__will_set_the_number_of_vertices_to_the_expected_amount)
{
   return;

   ALLEGRO_BITMAP *atlas_bitmap = get_bitmap_bin_ref()[TEST_TILE_MAP_BITMAP];
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   AllegroFlare::TileMaps::TileMesh mesh(&atlas, 30, 20, 16, 16);
   atlas.duplicate_bitmap_and_load(atlas_bitmap, 16, 16);
   mesh.initialize();

   ASSERT_EQ(30*20*6, mesh.get_vertices_ref().size());
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTest,
   get_real_width__will_return_the_real_world_horizontal_size_of_the_mesh)
{
   // TODO
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTest,
   get_real_height__will_return_the_real_world_vertical_size_of_the_mesh)
{
   // TODO
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTest,
   DISABLED__rescale_tile_dimensions_to__with_any_argument_with_a_value_less_than_or_equal_to_zero__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTest,
   rescale_tile_dimensions_to__will_resize_all_of_the_vertices_to_the_new_dimensions)
{
   ALLEGRO_BITMAP *atlas_bitmap = get_bitmap_bin_ref()[TEST_TILE_MAP_BITMAP];
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;

   AllegroFlare::TileMaps::TileMesh mesh(&atlas, 30, 10, 1, 1); // Set the initial tile size to 1
   atlas.duplicate_bitmap_and_load(atlas_bitmap, 16, 16);
   mesh.initialize();

   // Fill the tile mesh with random values
   mesh.enable_holding_vertex_buffer_update_until_refresh();

   std::vector<int> possible_random_tiles = { 82, 102, 122, 121, 81 };
   AllegroFlare::Random random;
   for (int y=0; y<mesh.get_num_rows(); y++)
   {
      for (int x=0; x<mesh.get_num_columns(); x++)
      {
         int random_tile = possible_random_tiles[random.get_random_int(0, possible_random_tiles.size()-1)];
         //int random_tile = random.get_random_int(0, atlas.get_tile_index_size());
         mesh.set_tile_id(x, y, random_tile);
      }
   }

   // Rescale the tile dimensions to something more arbitrary
   mesh.rescale_tile_dimensions_to(24, 24);

   mesh.refresh_vertex_buffer();

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
   al_flip_display();

   al_use_transform(&prev);
   al_rest(1);
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTest,
   CAPTURE__VISUAL__render__will_render_the_mesh_as_expected)
{
   ALLEGRO_BITMAP *atlas_bitmap = get_bitmap_bin_ref()[TEST_TILE_MAP_BITMAP];
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;

   AllegroFlare::TileMaps::TileMesh mesh(&atlas, 30, 10, 16, 16);
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



TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   CAPTURE__VISUAL__render__will_render_the_mesh_as_expected__solid_tiles_example)
{
   // Fill the subject with random tiles
   std::vector<int> possible_random_tiles = { 82, 102, 122, 121, 81 };
   fill_with_random_tiles(possible_random_tiles);

   // Render the subject
   render_subject(1.0f);
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   CAPTURE__VISUAL__remove_vertices_from_index_vertices__will_remove_the_verteces_as_expected)
{
   // Fill the subject with random tiles
   std::vector<int> possible_random_tiles = { 82, 102, 122, 121, 81 };
   fill_with_random_tiles(possible_random_tiles);

   ASSERT_EQ(6, mesh.remove_vertices_from_index_vertices( { 0, 1, 2, 3, 4, 5 } ));

   // Render the subject
   render_subject(1.0f);
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   CAPTURE__VISUAL__remove_tile_xy_from_index__will_remove_the_verteces_for_that_tile)
{
   // Fill the subject with random tiles
   std::vector<int> possible_random_tiles = { 20, 21, 23, 100, 101, 103, 172, 193 };
   fill_with_random_tiles(possible_random_tiles);

   mesh.remove_tile_xy_from_index(3, 2);
   mesh.remove_tile_xy_from_index(11, 7);

   // Render the subject
   render_subject(1.0f);
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   CAPTURE__VISUAL__remove_tile_xy_from_index__on_the_last_tile__will_remove_the_tile)
{
   // Fill the subject with random tiles
   std::vector<int> possible_random_tiles = { 20, 21, 23, 100, 101, 103, 172, 193 };
   fill_with_random_tiles(possible_random_tiles);

   //mesh.remove_tile_xy_from_index(3, 2);
   int tile_to_remove_y = mesh.get_num_rows() - 1;
   int tile_to_remove_x = mesh.get_num_columns() - 1;
   mesh.remove_tile_xy_from_index(tile_to_remove_x, tile_to_remove_y);

   // Render the subject
   render_subject(1.0f);
}


