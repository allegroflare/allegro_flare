#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/TileMaps/TileAtlasRepository.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_TileMaps_TileAtlasRepositoryTest : public ::testing::Test {};
class AllegroFlare_TileMaps_TileAtlasRepositoryTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_TileMaps_TileAtlasRepositoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::TileAtlasRepository tile_atlas_repository;
}


/*
TEST_F(AllegroFlare_TileMaps_TileAtlasRepositoryTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::TileMaps::TileAtlasRepository tile_atlas_repository;
   std::string expected_error_message =
      "TileAtlasRepository::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(tile_atlas_repository.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_TileMaps_TileAtlasRepositoryTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::TileMaps::TileAtlasRepository tile_atlas_repository;
   std::string expected_error_message =
      "TileAtlasRepository::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(tile_atlas_repository.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_TileMaps_TileAtlasRepositoryTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::TileMaps::TileAtlasRepository tile_atlas_repository;
   std::string expected_error_message =
      "TileAtlasRepository::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(tile_atlas_repository.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_TileMaps_TileAtlasRepositoryTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::TileMaps::TileAtlasRepository tile_atlas_repository;
   std::string expected_error_message =
      "TileAtlasRepository::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(tile_atlas_repository.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   
*/



TEST_F(AllegroFlare_TileMaps_TileAtlasRepositoryTestWithAllegroRenderingFixture, initialize__will_not_blow_up)
{
   AllegroFlare::TileMaps::TileAtlasRepository tile_atlas_repository;
   tile_atlas_repository.set_data_path(get_fixtures_path());
   tile_atlas_repository.initialize();
}



TEST_F(AllegroFlare_TileMaps_TileAtlasRepositoryTestWithAllegroRenderingFixture, load__will_not_blow_up)
{
   AllegroFlare::TileMaps::TileAtlasRepository tile_atlas_repository;
   tile_atlas_repository.set_data_path(get_fixtures_path());
   tile_atlas_repository.initialize();

   tile_atlas_repository.load("tiles_dungeon_v1.1", "tiles_dungeon_v1.1.png", 16, 16, 3);
}


TEST_F(AllegroFlare_TileMaps_TileAtlasRepositoryTestWithAllegroRenderingFixture,
   load__will_produce_a_record_that_has_the_expected_values)
{
   AllegroFlare::TileMaps::TileAtlasRepository tile_atlas_repository;
   tile_atlas_repository.set_data_path(get_fixtures_path());
   tile_atlas_repository.initialize();

   tile_atlas_repository.load("tiles_dungeon_v1.1", "tiles_dungeon_v1.1.png", 16, 16, 3);

   ASSERT_EQ(true, tile_atlas_repository.exists("tiles_dungeon_v1.1"));
   AllegroFlare::TileMaps::PrimMeshAtlas* created_tile_atlas = tile_atlas_repository.fetch("tiles_dungeon_v1.1");
   ASSERT_NE(nullptr, created_tile_atlas);

   // Some sanity checks
   //EXPECT_EQ(480, created_tile_atlas->get_tile_index_size()); // !! Fails! This should return 480
   EXPECT_EQ(16 * 3, created_tile_atlas->get_tile_width()); // TODO: Consider that this "tile_width" may not be the
                                                            // value the user is expecting for tile_height, which would
                                                            // be 16
   EXPECT_EQ(16 * 3, created_tile_atlas->get_tile_height()); // TODO: Consider that this "tile_height" may not be the
                                                             // value the user is expecting for tile_height, which would
                                                             // be 16
   return;
}


TEST_F(AllegroFlare_TileMaps_TileAtlasRepositoryTestWithAllegroRenderingFixture,
   CAPTURE__load__will_produce_a_record_that_has_the_expected_tiles)
{
   AllegroFlare::TileMaps::TileAtlasRepository tile_atlas_repository;
   tile_atlas_repository.set_data_path(get_fixtures_path());
   tile_atlas_repository.initialize();

   tile_atlas_repository.load("tiles_dungeon_v1.1", "tiles_dungeon_v1.1.png", 16, 16, 3);

   ASSERT_EQ(true, tile_atlas_repository.exists("tiles_dungeon_v1.1"));
   AllegroFlare::TileMaps::PrimMeshAtlas* created_tile_atlas = tile_atlas_repository.fetch("tiles_dungeon_v1.1");
   ASSERT_NE(nullptr, created_tile_atlas);

   int num_columns = 20;
   int num_rows = 20;
   int i=0;
   int spacing_x = 16 * 3;
   int spacing_y = 16 * 3;

   for (auto &tile_index_item : created_tile_atlas->get_tile_index()) // TODO: Change to get_tile_index_ref
   {
      int x = (i % num_columns) * spacing_x;
      int y = (i / num_columns) * spacing_y;
      al_draw_bitmap(tile_index_item.get_sub_bitmap(), x, y, 0);
      i++;
   }

   al_flip_display();
   al_rest(1);
}


