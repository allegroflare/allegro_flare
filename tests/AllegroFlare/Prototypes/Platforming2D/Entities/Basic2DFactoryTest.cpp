
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


static void my_tmj_loader_callback(
   std::string object_type,
   float x,
   float y,
   float width,
   float height,
   int id,
   std::string name,
   std::string object_layer_name,
   std::string map_name,
   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties, 
   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>* entity_pool,
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory* basic2dfactory,
   void* data
)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   if (object_type == "hopper")
   {
      entity_pool->push_back(basic2dfactory->create_enemy_move_left("unset-map-name", x, y));
      entity_pool->back()->set(TMJ_OBJECT_TYPE, "hopper");
      entity_pool->back()->set(TMJ_OBJECT_ID, id);
      entity_pool->back()->set(TMJ_OBJECT_NAME, "some_name"); // probably empty in the test data
      entity_pool->back()->set("object_layer_name", object_layer_name); // this property is probably not typically
                                                                        // included on the object itself
   }
   else if (object_type == "spawn_puck")
   {
      // Ignore for now
   }
   else if (object_type == "door")
   {
      // TODO: Parse these values from custom params
      std::string target_map_name = "yet-to-be-parsed-target-map_name";
      float target_spawn_x = 123.0f;
      float target_spawn_y = 456.0f;
      entity_pool->push_back(
         basic2dfactory->create_door("unset-map-name", x, y, target_map_name, target_spawn_x, target_spawn_y)
      );
      entity_pool->back()->set(TMJ_OBJECT_TYPE, "door");
      entity_pool->back()->set(TMJ_OBJECT_ID, id);
      entity_pool->back()->set(TMJ_OBJECT_NAME, "some_name"); // probably empty in the test data
      entity_pool->back()->set("object_layer_name", object_layer_name); // this property is probably not typically
                                                                        // included on the object itself
   }
   else // An unrecognized object type
   {
      // TODO: Test this error emission
      // TODO: Add option to "throw_error" instead of "error_from" here
      // TODO: Add a custom callback option
      AllegroFlare::Logger::error_from(
         "AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory::"
            "create_entities_from_map__tmj_obj_loader_callback_func",
         "Unable to handle object_type \"" + object_type + "\"."
      );
   }

   return;
}


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
      basic2d_factory.create_tile_map(
         "map_a",
         TEST_FIXTURES_PATH "maps/map1-0x.tmj",
         "tiles_dungeon_v1.1.png"
      );

   ASSERT_NE(nullptr, created_tile_map);
   ASSERT_NE(nullptr, created_tile_map->get_tile_atlas());
   ASSERT_NE(nullptr, created_tile_map->get_terrain_tile_mesh());
   // TODO: Test creation of map that includes a background_mesh
   ASSERT_NE(nullptr, created_tile_map->get_collision_tile_mesh());

   EXPECT_EQ(true, created_tile_map->exists(MAP_NAME, "map_a"));

   delete created_tile_map;
};


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryWithAllegroRenderingFixtureTest,
   create_tile_map__with_a_map_that_has_a_background_tilelayer__will_create_a_map_with_expected_background_properties)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::string data_folder_path = TEST_FIXTURES_PATH;
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory basic2d_factory(&get_bitmap_bin_ref());
   AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D *created_tile_map =
      basic2d_factory.create_tile_map(
         "map_a",
         TEST_FIXTURES_PATH "map1-with_background-02.tmj",
         "tiles_dungeon_v1.1.png"
      );

   ASSERT_NE(nullptr, created_tile_map->get_background_tile_mesh());
   EXPECT_EQ(25, created_tile_map->get_background_tile_mesh()->get_num_columns());
   EXPECT_EQ(15, created_tile_map->get_background_tile_mesh()->get_num_rows());
   EXPECT_EQ(174, created_tile_map->get_background_tile_mesh()->get_tile_id(20, 3)); // Testing a specific tile

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

   // TODO: Add check on the created entities for custom properties
   ASSERT_EQ(2, entities.size());

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D &entity1 = *entities[0];
   EXPECT_EQ(true, entity1.exists(TMJ_OBJECT_TYPE, "door"));
   EXPECT_EQ(true, entity1.exists(ON_MAP_NAME, "map_a"));
   EXPECT_EQ(false, entity1.get_draw_debug());

   // TODO: Add this test
   ASSERT_EQ(true, entity1.exists(TMJ_OBJECT_ID));
   //ASSERT_EQ(true, entity1.exists(TMJ_OBJECT_NAME));
   //EXPECT_EQ(999, entity1.get_as_int(TMJ_OBJECT_ID));
   //EXPECT_EQ("some_name", entity1.get_as_string(TMJ_OBJECT_NAME));

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D &entity2 = *entities[1];
   EXPECT_EQ(true, entity2.exists(TMJ_OBJECT_TYPE, "hopper"));
   EXPECT_EQ(true, entity2.exists(ON_MAP_NAME, "map_a"));
   EXPECT_EQ(false, entity2.get_draw_debug());

   for (auto &entity : entities) delete entity;
   entities.clear();
};


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryWithAllegroRenderingFixtureTest,
   create_entities_from_map__will_create_entities_while_retaining_the_options_set_on_the_factory)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
   std::string data_folder_path = TEST_FIXTURES_PATH;

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory basic2d_factory(&get_bitmap_bin_ref());
   basic2d_factory.set_init_entities_drawing_debug(true);
   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> entities =
      basic2d_factory.create_entities_from_map(TEST_FIXTURES_PATH "maps/map_with_objects-x.tmj", "map_a");

   ASSERT_EQ(2, entities.size());

   for (auto &entity : entities)
   {
      EXPECT_EQ(true, entity->get_draw_debug());
   }

   for (auto &entity : entities) delete entity;
   entities.clear();
};


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryWithAllegroRenderingFixtureTest,
   create_entities_from_map__when_a_user_callback_is_present__will_not_blow_up)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
   std::string data_folder_path = TEST_FIXTURES_PATH;

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory basic2d_factory(&get_bitmap_bin_ref());
   basic2d_factory.set_init_entities_drawing_debug(true);

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> entities =
      basic2d_factory.create_entities_from_map(
         TEST_FIXTURES_PATH "maps/map_with_objects-x.tmj",
         "map_a",
         my_tmj_loader_callback,
         nullptr
      );

   ASSERT_EQ(2, entities.size());

   for (auto &entity : entities)
   {
      EXPECT_EQ(true, entity->get_draw_debug());
   }

   for (auto &entity : entities) delete entity;
   entities.clear();
};


