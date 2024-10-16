

#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ColorPickingAssertions.hpp>

#include <AllegroFlare/TileMaps/TileMesh.hpp>

const std::string TEST_TILE_MAP_BITMAP = "tiles_dungeon_v1.1.png";
#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro_color.h>
#include <AllegroFlare/Profiler.hpp>


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
      mesh.destroy();
      AllegroFlare::Testing::WithAllegroRenderingFixture::TearDown();
   }

   void fill_with_random_tiles(std::vector<int> possible_random_tiles = {})
   {
      //mesh.enable_holding_vertex_buffer_update_until_refresh(); // NOTE: This is already enabled by default
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

   void render_subject(float duration_sec=1.0f, AllegroFlare::Vec2D position = { 1920/2, 1080/2 })
   {
      AllegroFlare::Placement2D subject_placement;
      subject_placement.position = position; //{ 1920/2, 1080/2 };
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

   EXPECT_THROW_GUARD_ERROR(
      mesh.render(),
      "AllegroFlare::TileMaps::TileMesh::render",
      "initialized"
   );
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTest,
   initialize__will_set_the_number_of_vertices_to_the_expected_amount)
{
   ALLEGRO_BITMAP *atlas_bitmap = get_bitmap_bin_ref()[TEST_TILE_MAP_BITMAP];
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   atlas.duplicate_bitmap_and_load(atlas_bitmap, 16, 16);

   AllegroFlare::TileMaps::TileMesh mesh(&atlas);
   mesh.set_num_columns(30);
   mesh.set_num_rows(10);
   mesh.initialize();

   ASSERT_EQ(30*10*6, mesh.get_vertices_ref().size());
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
   //mesh.enable_holding_vertex_buffer_update_until_refresh();

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
   mesh.disable_holding_vertex_buffer_update_until_refresh();

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
   CAPTURE__VISUAL__remove_vertices_from_index_vertices__will_remove_the_verteces_as_expected_so_they_are_not_\
rendered)
{
   ALLEGRO_COLOR clear_color = ALLEGRO_COLOR{0.6f, 0.2f, 0.8f, 1.0f};

   // Fill the subject with random tiles
   std::vector<int> possible_random_tiles = { 82, 102, 122, 121, 81 };
   fill_with_random_tiles(possible_random_tiles);

   ASSERT_EQ(6, mesh.remove_vertices_from_index_vertices( { 0, 1, 2, 3, 4, 5 } ));
   mesh.refresh_index_buffer();

   // Render the subject
   al_clear_to_color(clear_color);
   mesh.render();

   // HERE, sample the pixel at (tile_x/2, tile_y/2), which should match the background color
   ALLEGRO_COLOR expected_color = clear_color;
   ALLEGRO_BITMAP *surface = al_get_backbuffer(al_get_current_display());
   int pixel_x = mesh.get_tile_width()/2;
   int pixel_y = mesh.get_tile_height()/2;
   EXPECT_PICKED_COLOR_EQ(expected_color, surface, pixel_x, pixel_y);

   al_flip_display();
   al_rest(1.0f);
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   CAPTURE__VISUAL__remove_tile_xy_from_index__will_remove_the_verteces_for_that_tile)
{
   ALLEGRO_COLOR clear_color = ALLEGRO_COLOR{0.6f, 0.2f, 0.8f, 1.0f};

   // Fill the subject with random tiles
   std::vector<int> possible_random_tiles = { 20, 21, 23, 100, 101, 103, 172, 193 };
   fill_with_random_tiles(possible_random_tiles);

   mesh.remove_tile_xy_from_index(3, 2);
   mesh.remove_tile_xy_from_index(11, 7);

   //mesh.refresh_index_buffer();
   mesh.refresh_index_vertices_from_removed_tiles_and_refresh_index_buffer();

   al_clear_to_color(clear_color);
   mesh.render();

   ALLEGRO_COLOR expected_color = clear_color; //AllegroFlare::Testing::WithAllegroRenderingFixture::CLEAR_COLOR;
   ALLEGRO_BITMAP *surface = al_get_backbuffer(al_get_current_display());
   EXPECT_PICKED_COLOR_EQ(expected_color, surface, 3*16.5, 2*16.5);
   EXPECT_PICKED_COLOR_EQ(expected_color, surface, 11*16.5, 7*16.5);

   // Render the subject
   al_flip_display();
   al_rest(1.0f);
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

   mesh.refresh_index_vertices_from_removed_tiles_and_refresh_index_buffer();
   //mesh.refresh_index_buffer();

   // Render the subject
   render_subject(1.0f);
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   FLAKEY__remove_tile_xy_from_index__when_holding_index_buffer_update_until_refresh_is_true__will_not_have_a_\
significant_performance_impact)
{
   std::string TIMER_NAME = "remove_tile_xy_from_index";

   // Set a mesh size that is not small
   int num_columns = 160;
   int num_rows = 67;
   mesh.resize(num_columns, num_rows);

   std::vector<int> possible_random_tiles = { 20, 21, 23, 100, 101, 103, 172, 193 };
   fill_with_random_tiles(possible_random_tiles);

   int num_tiles_to_remove = num_columns * num_rows;

   AllegroFlare::Profiler profiler;
   profiler.start(TIMER_NAME);
   for (int i=0; i<num_tiles_to_remove; i++)
   {
      int tile_x = i % num_columns;
      int tile_y = i / num_columns;
      mesh.remove_tile_xy_from_index(tile_x, tile_y);
   }
   profiler.stop(TIMER_NAME);

   EXPECT_EQ(num_tiles_to_remove, mesh.get_removed_tiles().size());
   EXPECT_LT(profiler.get_timers_ref()[TIMER_NAME].get_elapsed_time_microseconds(), 5000);
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   FLAKEY__refresh_index_vertices_from_removed_tiles_and_refresh_index_buffer__with_large_number_of_removed_\
tiles__will_not_have_a_significant_performance_impact)
{
   std::string TIMER_NAME = "refresh_index_vertices_from_removed_tiles_and_refresh_index_buffer";

   // Set a mesh size that is not small
   int num_columns = 160;
   int num_rows = 67;
   mesh.resize(num_columns, num_rows);

   // Fill the subject with random tiles
   std::vector<int> possible_random_tiles = { 20, 21, 23, 100, 101, 103, 172, 193 };
   fill_with_random_tiles(possible_random_tiles);

   // Remove literally all the tiles
   int num_tiles_to_remove = num_columns * num_rows;
   for (int i=0; i<num_tiles_to_remove; i++)
   {
      int tile_x = i % num_columns;
      int tile_y = i / num_columns;
      mesh.remove_tile_xy_from_index(tile_x, tile_y);
   }
   ASSERT_EQ(num_tiles_to_remove, mesh.get_removed_tiles().size());

   // Refresh
   AllegroFlare::Profiler profiler;
   profiler.start(TIMER_NAME);
   mesh.refresh_index_vertices_from_removed_tiles_and_refresh_index_buffer();
   profiler.stop(TIMER_NAME);
   EXPECT_LT(profiler.get_timers_ref()[TIMER_NAME].get_elapsed_time_microseconds(), 20000);
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   resize__will_set_the_dimensions_of_the_map_and_fill_the_tiles_with_empty_tiles)
{
   // Fill the subject with random tiles
   mesh.resize(160, 67);

   EXPECT_EQ(160, mesh.get_num_columns());
   EXPECT_EQ(67, mesh.get_num_rows());

   bool all_tiles_are_zero = true;
   for (auto &tile : mesh.get_tile_ids())
   {
      if (tile != 0)
      {
         all_tiles_are_zero = false;
         break;
      }
   }

   EXPECT_EQ(true, all_tiles_are_zero);
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   resize__will_set_the_vertex_buffer_and_index_buffer_to_the_expected_size)
{
   mesh.resize(160, 67);
   EXPECT_EQ(64320, mesh.get_vertex_buffer_size());
   EXPECT_EQ(64320, mesh.get_index_buffer_size());
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   resize__will_clear_the_flipped_tiles)
{
   // Flip some tiles
   mesh.set_tile_id(3, 0, 234, true, false, false);
   mesh.set_tile_id(6, 0, 234, false, true, false);
   mesh.set_tile_id(9, 0, 234, true, true, false);
   mesh.set_tile_id(3, 3, 234, true, false, true);
   mesh.set_tile_id(6, 3, 234, false, true, true);
   mesh.set_tile_id(9, 3, 234, true, true, true);

   ASSERT_EQ(false, mesh.get_h_flipped_tiles().empty());
   ASSERT_EQ(false, mesh.get_v_flipped_tiles().empty());
   ASSERT_EQ(false, mesh.get_d_flipped_tiles().empty());

   mesh.resize(160, 67);

   EXPECT_EQ(true, mesh.get_h_flipped_tiles().empty());
   EXPECT_EQ(true, mesh.get_v_flipped_tiles().empty());
   EXPECT_EQ(true, mesh.get_d_flipped_tiles().empty());
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   resize__will_clear_the_removed_tiles)
{
   // Remove some tiles
   mesh.remove_tile_xy_from_index(3, 6);
   mesh.remove_tile_xy_from_index(12, 8);
   mesh.remove_tile_xy_from_index(9, 5);
   ASSERT_EQ(false, mesh.get_removed_tiles().empty());

   mesh.resize(160, 67);

   EXPECT_EQ(true, mesh.get_removed_tiles().empty());
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   CAPTURE__VISUAL__set_tile_id__with_flip_h_and_flip_v_values__will_flip_the_tile_horizontally_and_vertically)
{
   //mesh.enable_holding_vertex_buffer_update_until_refresh();

   mesh.set_tile_id(0, 0, 234, false, false, false);
   mesh.set_tile_id(3, 0, 234, true, false, false);
   mesh.set_tile_id(6, 0, 234, false, true, false);
   mesh.set_tile_id(9, 0, 234, true, true, false);

   mesh.set_tile_id(0, 3, 234, false, false, true);
   mesh.set_tile_id(3, 3, 234, true, false, true);
   mesh.set_tile_id(6, 3, 234, false, true, true);
   mesh.set_tile_id(9, 3, 234, true, true, true);

   mesh.refresh_vertex_buffer();

   // Render the subject
   render_subject(1.0f);
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   get_file_filp__will_return_expected_values_for_horizontal_and_vertical_flip_on_a_tile)
{
   //mesh.enable_holding_vertex_buffer_update_until_refresh();

   mesh.set_tile_id(0, 0, 234, false, false, false);
   mesh.set_tile_id(3, 0, 234, true, false, false);
   mesh.set_tile_id(6, 0, 234, false, true, false);
   mesh.set_tile_id(9, 0, 234, true, true, false);

   mesh.set_tile_id(0, 3, 234, false, false, true);
   mesh.set_tile_id(3, 3, 234, true, false, true);
   mesh.set_tile_id(6, 3, 234, false, true, true);
   mesh.set_tile_id(9, 3, 234, true, true, true);

   // TODO: Update this with three bools
   std::tuple<bool, bool, bool> expected_flip;

   expected_flip = { false, false, false };
   EXPECT_EQ(expected_flip, mesh.get_tile_flip(0, 0));

   expected_flip = { true, false, false };
   EXPECT_EQ(expected_flip, mesh.get_tile_flip(3, 0));

   expected_flip = { false, true, false };
   EXPECT_EQ(expected_flip, mesh.get_tile_flip(6, 0));

   expected_flip = { true, true, false };
   EXPECT_EQ(expected_flip, mesh.get_tile_flip(9, 0));


   expected_flip = { false, false, true };
   EXPECT_EQ(expected_flip, mesh.get_tile_flip(0, 3));

   expected_flip = { true, false, true };
   EXPECT_EQ(expected_flip, mesh.get_tile_flip(3, 3));

   expected_flip = { false, true, true };
   EXPECT_EQ(expected_flip, mesh.get_tile_flip(6, 3));

   expected_flip = { true, true, true };
   EXPECT_EQ(expected_flip, mesh.get_tile_flip(9, 3));
}


TEST_F(AllegroFlare_TileMaps_TileMeshWithAllegroRenderingFixtureTestWithSetup,
   CAPTURE__VISUAL__render__will_render_the_mesh_as_expected__solid_tiles_example__2)
{
   // Fill the subject with random tiles
   // TODO: Use a different tilemap that has shapes and white tile for better testing
   std::vector<int> possible_random_tiles = { 0 };
   fill_with_random_tiles(possible_random_tiles);

   std::vector<ALLEGRO_COLOR> possible_random_colors = {
      ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0},
      ALLEGRO_COLOR{0.7, 0.0, 0.0, 1.0},
      ALLEGRO_COLOR{0.0, 0.7, 0.0, 1.0},
      ALLEGRO_COLOR{0.0, 0.0, 0.7, 1.0},
      ALLEGRO_COLOR{0.0, 0.7, 0.7, 1.0},
      ALLEGRO_COLOR{0.7, 0.0, 0.7, 1.0},
      ALLEGRO_COLOR{0.7, 0.7, 0.0, 1.0},
   };

   AllegroFlare::Random random;
   ALLEGRO_COLOR random_color;
   for (int y=0; y<mesh.get_num_rows(); y++)
   {
      for (int x=0; x<mesh.get_num_columns(); x++)
      {
         int random_i = random.get_random_int(0, possible_random_colors.size()-1);
         random_color = possible_random_colors[random_i];
         mesh.set_tile_color(x, y, random_color);
      }
   }
   mesh.refresh_vertex_buffer();

   // Render the subject
   render_subject(1.0f);
}


