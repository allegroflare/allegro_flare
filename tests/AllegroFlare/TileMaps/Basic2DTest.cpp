#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_TileMaps_Basic2DTest : public ::testing::Test {};
class AllegroFlare_TileMaps_Basic2DTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/TileMaps/Basic2D.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/Camera3D.hpp>


TEST_F(AllegroFlare_TileMaps_Basic2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::Basic2D basic2d_tile_map;
}


TEST_F(AllegroFlare_TileMaps_Basic2DTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::TileMaps::Basic2D basic2d_tile_map;
   std::string expected_error_message =
      "Basic2D::initialize: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(basic2d_tile_map.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_TileMaps_Basic2DTest, render__before_being_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::TileMaps::Basic2D basic2d_tile_map;
   std::string expected_error_message =
      "Basic2D::render: error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(basic2d_tile_map.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_TileMaps_Basic2DTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::TileMaps::Basic2D basic2d_tile_map(&get_bitmap_bin_ref());
   basic2d_tile_map.set_atlas_configuration("uv.png", 100, 100);
   basic2d_tile_map.initialize();
   basic2d_tile_map.render();
   al_flip_display();
}


TEST_F(AllegroFlare_TileMaps_Basic2DTestWithAllegroRenderingFixture,
   get_num_rows__will_return_the_number_of_rows_in_the_tile_map)
{
   AllegroFlare::TileMaps::Basic2D basic2d_tile_map(&get_bitmap_bin_ref());
   basic2d_tile_map.set_atlas_configuration("uv.png", 100, 100);
   basic2d_tile_map.initialize();

   basic2d_tile_map.resize(20, 12);

   EXPECT_EQ(12, basic2d_tile_map.get_num_rows());
}


TEST_F(AllegroFlare_TileMaps_Basic2DTestWithAllegroRenderingFixture,
   get_num_columns__will_return_the_number_of_rows_in_the_tile_map)
{
   AllegroFlare::TileMaps::Basic2D basic2d_tile_map(&get_bitmap_bin_ref());
   basic2d_tile_map.set_atlas_configuration("uv.png", 100, 100);
   basic2d_tile_map.initialize();

   basic2d_tile_map.resize(20, 12);

   EXPECT_EQ(20, basic2d_tile_map.get_num_columns());
}


TEST_F(AllegroFlare_TileMaps_Basic2DTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_mesh_as_expected)
{
   AllegroFlare::TileMaps::Basic2D basic2d_tile_map(&get_bitmap_bin_ref());
   basic2d_tile_map.set_atlas_configuration("tiles_dungeon_v1.1.png", 16, 16);
   basic2d_tile_map.initialize();

   basic2d_tile_map.resize(20, 12);
   basic2d_tile_map.rescale_tile_dimensions_to(32, 32);
   basic2d_tile_map.random_fill();

   AllegroFlare::Placement2D place = build_centered_placement(
      basic2d_tile_map.infer_real_width(),
      basic2d_tile_map.infer_real_height()
   );
   place.scale = {2.0, 2.0};

   clear();

   place.start_transform();
   basic2d_tile_map.render();
   place.restore_transform();

   al_flip_display();
   sleep_for(1);
}


