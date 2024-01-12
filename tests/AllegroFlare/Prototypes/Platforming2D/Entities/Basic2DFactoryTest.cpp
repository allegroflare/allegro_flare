
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2DFactory.hpp>

class AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryTest : public ::testing::Test {};
class AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};

#if defined(_WIN32) || defined(_WIN64)
#define TEST_FIXTURES_PATH "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/"
#else
#define TEST_FIXTURES_PATH "/Users/markoates/Repos/allegro_flare/tests/fixtures/"
#endif

#include <AllegroFlare/Prototypes/Platforming2D/EntityFlagNames.hpp>



TEST(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory basic2dfactory;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryWithAllegroRenderingFixtureTest,
   create_from_bitmap_filename__returns_a_basic2d_entity_with_the_expected_bitmap_and_size_and_bitmap_alignment_strategy)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   bitmap_bin.set_full_path(TEST_FIXTURES_PATH "bitmaps/");

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory basic2d_factory(&get_bitmap_bin_ref());
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D *created_entity =
      basic2d_factory.create_from_bitmap_filename("map_a", "test-sprite-128.png", "bottom_centered");

   AllegroFlare::vec2d expected_dimensions = {128, 128};
   AllegroFlare::vec2d actual_dimensions = created_entity->get_place_ref().size;

   ASSERT_NE(nullptr, created_entity->get_bitmap());
   ASSERT_EQ("bottom_centered", created_entity->get_bitmap_alignment_strategy());
   ASSERT_EQ(expected_dimensions, actual_dimensions);
   ASSERT_EQ(true, created_entity->exists(ON_MAP_NAME, "map_a"));

   delete created_entity;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryWithAllegroRenderingFixtureTest,
   create_tile_map__will_create_a_map_from_the_map_json_filename)
   //INTERACTIVE__in_an_AllegroFlare_Frameworks_Full_context__will_run_as_expected)
   //DISABLED__INTERACTIVE__in_an_AllegroFlare_Frameworks_Full_context__will_run_as_expected)
{
   //AllegroFlare::Frameworks::Full framework;
   //framework.set_deployment_environment("test");
   //framework.disable_auto_created_config_warning();
   //framework.disable_clear_render_surface_before_calling_primary_timer_funcs();
   //framework.disable_fullscreen();
   //framework.initialize();

   std::string data_folder_path = TEST_FIXTURES_PATH;


   //AllegroFlare::Prototypes::Platforming2D::Screen platforming_2d;
   //platforming_2d.set_bitmap_bin(&framework.get_bitmap_bin_ref());
   //platforming_2d.set_display(framework.get_primary_display());
   //platforming_2d.set_event_emitter(&framework.get_event_emitter_ref());

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory basic2d_factory(&get_bitmap_bin_ref());
   AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D *created_tile_map =
      basic2d_factory.create_tile_map(TEST_FIXTURES_PATH "maps/map1-0x.tmj", "map_a");


   //platforming_2d.set_map_dictionary({
      //{ "map_a", data_folder_path + "maps/map1-0x.tmj" },
      //{ "map_b", data_folder_path + "maps/map1b-0x.tmj" },
   //});
   //platforming_2d.initialize_maps();
   //platforming_2d.set_currently_active_map("map_a");

   // create some entities




   // create an animation book (to create an frame_animated type from the factory)
};

