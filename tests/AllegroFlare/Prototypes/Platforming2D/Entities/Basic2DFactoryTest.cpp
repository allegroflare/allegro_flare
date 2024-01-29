
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
   create_tile_map__will_create_a_map_with_the_expected_properties)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::string data_folder_path = TEST_FIXTURES_PATH;
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory basic2d_factory(&get_bitmap_bin_ref());
   AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D *created_tile_map =
      basic2d_factory.create_tile_map(TEST_FIXTURES_PATH "maps/map1-0x.tmj", "map_a");

   ASSERT_NE(nullptr, created_tile_map);
   ASSERT_NE(nullptr, created_tile_map->get_tile_atlas());
   ASSERT_NE(nullptr, created_tile_map->get_tile_mesh());
   ASSERT_NE(nullptr, created_tile_map->get_collision_tile_mesh());

   EXPECT_EQ(true, created_tile_map->exists(MAP_NAME, "map_a"));

   delete created_tile_map;
};


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryWithAllegroRenderingFixtureTest,
   create_entities_from_map__will_create_entities_with_the_expected_properties)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
   std::string data_folder_path = TEST_FIXTURES_PATH;

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory basic2d_factory(&get_bitmap_bin_ref());
   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> entities =
      basic2d_factory.create_entities_from_map(TEST_FIXTURES_PATH "maps/map_with_objects-x.tmj", "map_a");

   // TODO: Test the created entities
   ASSERT_EQ(2, entities.size());

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D &entity2 = *entities[1];
   ASSERT_EQ(true, entity2.exists("enemy_class_name", "hopper"));
   //ASSERT_NE(nullptr, created_tile_map->get_tile_atlas());
   //ASSERT_NE(nullptr, created_tile_map->get_tile_mesh());
   //ASSERT_NE(nullptr, created_tile_map->get_collision_tile_mesh());

   //EXPECT_EQ(true, created_tile_map->exists(MAP_NAME, "map_a"));

   for (auto &entity : entities) delete entity;
   entities.clear();
};


