
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

class AllegroFlare_Physics_TileMapCollisionStepperTest : public ::testing::Test
{};

class AllegroFlare_Physics_TileMapCollisionStepperTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Physics/TileMapCollisionStepper.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>

#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/Int2D.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/AABB2D.hpp>

static void load_increment_tile_num_map(AllegroFlare::TileMaps::TileMap<int> &tile_map)
{
   tile_map.resize(5, 6);
   int tile_num = 0;
   for (int y=0; y<tile_map.get_num_rows(); y++)
      for (int x=0; x<tile_map.get_num_columns(); x++)
   {
      tile_map.set_tile(x, y, tile_num);
      tile_num++;
   }
}

static void load_test_map(AllegroFlare::TileMaps::TileMap<int> &tile_map)
{
   tile_map.resize(25, 15);

   // fill the top and bottom rows with solid blocks
   for (int x=0; x<tile_map.get_num_columns(); x++)
   {
      tile_map.set_tile(x, 0, 1);
      tile_map.set_tile(x, tile_map.get_num_rows()-1, 1);
   }

   // fill the left and right columns with solid blocks
   for (int y=0; y<tile_map.get_num_rows(); y++)
   {
      tile_map.set_tile(0, y, 1);
      tile_map.set_tile(tile_map.get_num_columns()-1, y, 1);
   }

   // add a simple pillar on the left
   tile_map.set_tile(4, tile_map.get_num_rows()-1, 1);
   tile_map.set_tile(4, tile_map.get_num_rows()-2, 1);
   tile_map.set_tile(4, tile_map.get_num_rows()-3, 1);
   tile_map.set_tile(4, tile_map.get_num_rows()-4, 1);

   // add a simple pillar on the top right
   tile_map.set_tile(tile_map.get_num_columns()-4, 0, 1);
   tile_map.set_tile(tile_map.get_num_columns()-4, 1, 1);
   tile_map.set_tile(tile_map.get_num_columns()-4, 2, 1);
   tile_map.set_tile(tile_map.get_num_columns()-4, 3, 1);

   // add 2 blocks in the middle
   tile_map.set_tile(8, 8, 1);
   tile_map.set_tile(9, 8, 1);
   tile_map.set_tile(8, 9, 1);
   tile_map.set_tile(9, 9, 1);

   tile_map.set_tile(8+3, 8, 1);
   tile_map.set_tile(9+3, 8, 1);
   tile_map.set_tile(8+3, 9, 1);
   tile_map.set_tile(9+3, 9, 1);

   // add a little cavern on the bottom right
   tile_map.set_tile(tile_map.get_num_columns()-5, tile_map.get_num_rows()-4, 1);
   tile_map.set_tile(tile_map.get_num_columns()-4, tile_map.get_num_rows()-4, 1);
   tile_map.set_tile(tile_map.get_num_columns()-3, tile_map.get_num_rows()-4, 1);
   tile_map.set_tile(tile_map.get_num_columns()-2, tile_map.get_num_rows()-4, 1);
   tile_map.set_tile(tile_map.get_num_columns()-1, tile_map.get_num_rows()-4, 1);

   // remove tiles on the left
   tile_map.set_tile(0, tile_map.get_num_rows()-4, 0);
   tile_map.set_tile(0, tile_map.get_num_rows()-3, 0);
   tile_map.set_tile(0, tile_map.get_num_rows()-2, 0);

   // remove tiles on the right
   tile_map.set_tile(tile_map.get_num_columns()-1, tile_map.get_num_rows()-5, 0);
   tile_map.set_tile(tile_map.get_num_columns()-1, tile_map.get_num_rows()-6, 0);
   tile_map.set_tile(tile_map.get_num_columns()-1, tile_map.get_num_rows()-7, 0);

   // remove tiles on the bottom
   tile_map.set_tile(6, tile_map.get_num_rows()-1, 0);
   tile_map.set_tile(7, tile_map.get_num_rows()-1, 0);
   tile_map.set_tile(8, tile_map.get_num_rows()-1, 0);

   // remove tiles on the top
   tile_map.set_tile(6, 0, 0);
   tile_map.set_tile(7, 0, 0);
   tile_map.set_tile(8, 0, 0);
}

#include <allegro5/allegro_primitives.h>
void static render_tile_map(
      AllegroFlare::TileMaps::TileMap<int> &tile_map,
      float tile_width=16.0f,
      float tile_height=16.0f
   )
{
   if (!al_is_primitives_addon_initialized()) throw std::runtime_error("render_tile_map: primitives must be init");

   for (int y=0; y<tile_map.get_num_rows(); y++)
      for (int x=0; x<tile_map.get_num_columns(); x++)
      {
         int tile_type = tile_map.get_tile(x, y);
         switch(tile_type)
         {
            case 0:
              //al_draw_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 //ALLEGRO_COLOR{0.2, 0.2, 0.21, 0.21}, 1.0);
            break;

            case 1:
              al_draw_filled_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 ALLEGRO_COLOR{0.65, 0.62, 0.6, 1.0});
            break;

            default:
              //al_draw_filled_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 //ALLEGRO_COLOR{0.8, 0.32, 0.4, 1.0});
            break;
         }
      }
}

void render_aabb2d(
      AllegroFlare::Physics::AABB2D &aabb2d,
      bool adjacent_to_top_edge=false,
      bool adjacent_to_right_edge=false,
      bool adjacent_to_bottom_edge=false,
      bool adjacent_to_left_edge=false
   )
{
   al_draw_filled_rectangle(aabb2d.get_x(), aabb2d.get_y(), aabb2d.get_right_edge(), aabb2d.get_bottom_edge(),
      ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0});

   ALLEGRO_COLOR orange = ALLEGRO_COLOR{1.0, 0.5, 0.0, 1.0};

   if (adjacent_to_bottom_edge)
   {
      al_draw_line(
         aabb2d.get_x(),
         aabb2d.get_bottom_edge(),
         aabb2d.get_right_edge(),
         aabb2d.get_bottom_edge(),
         orange,
         2.0
      );
   }
   if (adjacent_to_top_edge)
   {
      al_draw_line(aabb2d.get_x(), aabb2d.get_y(), aabb2d.get_right_edge(), aabb2d.get_y(), orange, 2.0);
   }
   if (adjacent_to_left_edge)
   {
      al_draw_line(aabb2d.get_x(), aabb2d.get_y(), aabb2d.get_x(), aabb2d.get_bottom_edge(), orange, 2.0);
   }
   if (adjacent_to_right_edge)
   {
      al_draw_line(
         aabb2d.get_right_edge(),
         aabb2d.get_y(),
         aabb2d.get_right_edge(),
         aabb2d.get_bottom_edge(),
         orange,
         2.0
      );
   }
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper;
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   render__without_a_collision_tile_map__initialized__raises_an_error)
{
   AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper;
   std::string expected_error_message =
      "TileMapCollisionStepper::step: error: guard \"collision_tile_map\" not met";
   ASSERT_THROW_WITH_MESSAGE(tile_map_collision_stepper.step(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest, render__without_an_aabb2d__raises_an_error)
{
   AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
   AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper(&collision_tile_map);
   std::string expected_error_message =
      "TileMapCollisionStepper::step: error: guard \"aabb2d\" not met";
   ASSERT_THROW_WITH_MESSAGE(tile_map_collision_stepper.step(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   world_coords_to_tile_coords__will_return_the_tile_coordinates_of_a_world_coordinate)
{
   EXPECT_EQ(2, AllegroFlare::Physics::TileMapCollisionStepper::world_coords_to_tile_coords(32+1, 16));
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   world_coords_to_tile_coords__will_provide_correct_coordinaets_with_negative_numbers)
{
   EXPECT_EQ(-3, AllegroFlare::Physics::TileMapCollisionStepper::world_coords_to_tile_coords(-32-1, 16));
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTestWithAllegroRenderingFixture,
   DISABLED__INTERACTIVE__will_work_as_expected)
   //INTERACTIVE__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // initialize test subject(s)
   AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
   AllegroFlare::Physics::AABB2D aabb2d(80, 60, 16 - 1, 16*2 - 1);
   collision_tile_map.initialize();
   load_test_map(collision_tile_map);
   AllegroFlare::Placement2D camera;
   camera.scale.x = 4.8;
   camera.scale.y = 4.5;

   bool aabb2d_adjacent_to_bottom_edge = false;
   bool aabb2d_adjacent_to_top_edge = false;
   bool aabb2d_adjacent_to_right_edge = false;
   bool aabb2d_adjacent_to_left_edge = false;

   bool invert_gravity = false;
   bool gravity_enabled = true;
   bool vertical_movement_controls_active = false;

   // run the interactive test
   al_wait_for_vsync();
   al_start_timer(primary_timer);
   while(!abort)
   {
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_DOWN:
            switch(event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                 if (vertical_movement_controls_active) aabb2d.set_velocity_y(-1);
               break;

               case ALLEGRO_KEY_DOWN:
                 if (vertical_movement_controls_active) aabb2d.set_velocity_y(1);
               break;

               case ALLEGRO_KEY_LEFT:
                 aabb2d.set_velocity_x(-1);
               break;

               case ALLEGRO_KEY_RIGHT:
                 aabb2d.set_velocity_x(1);
               break;

               case ALLEGRO_KEY_SPACE:
                 aabb2d.set_velocity_y(invert_gravity ? 3.0f : -3.0f);
               break;

               case ALLEGRO_KEY_I:
                 invert_gravity = !invert_gravity;
               break;

               case ALLEGRO_KEY_G:
                 gravity_enabled = !gravity_enabled;
               break;

               case ALLEGRO_KEY_V:
                 vertical_movement_controls_active = !vertical_movement_controls_active;
               break;
            }
         break;

         case ALLEGRO_EVENT_KEY_UP:
            switch(event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
               case ALLEGRO_KEY_DOWN:
                 aabb2d.set_velocity_y(0);
               break;

               case ALLEGRO_KEY_LEFT:
               case ALLEGRO_KEY_RIGHT:
                 aabb2d.set_velocity_x(0);
               break;
            }
         break;

         case ALLEGRO_EVENT_TIMER:
            { // update
               // add gravity
               if (gravity_enabled) aabb2d.set_velocity_y(aabb2d.get_velocity_y() + (invert_gravity ? -0.1 : 0.1));
               
               // update the aabb2d collsion on the map using the stepper
               AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper(
                  &collision_tile_map,
                  &aabb2d,
                  16.0f,
                  16.0f
               );
               tile_map_collision_stepper.step();

               aabb2d_adjacent_to_top_edge = tile_map_collision_stepper.adjacent_to_top_edge(16.0f, 16.0f);
               aabb2d_adjacent_to_right_edge = tile_map_collision_stepper.adjacent_to_right_edge(16.0f, 16.0f);
               aabb2d_adjacent_to_bottom_edge = tile_map_collision_stepper.adjacent_to_bottom_edge(16.0f, 16.0f);
               aabb2d_adjacent_to_left_edge = tile_map_collision_stepper.adjacent_to_left_edge(16.0f, 16.0f);
            }
            { // draw
               al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
               camera.start_transform();
               render_tile_map(collision_tile_map, 16.0f, 16.0f);
               render_aabb2d(
                  aabb2d,
                  aabb2d_adjacent_to_top_edge,
                  aabb2d_adjacent_to_right_edge,
                  aabb2d_adjacent_to_bottom_edge,
                  aabb2d_adjacent_to_left_edge
               );
               camera.restore_transform();
               al_flip_display();
            }
         break;
      }

      if (event.type == ALLEGRO_EVENT_KEY_CHAR && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) abort = true;
   }
   
   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.
   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   get_tile_coords_below_left_foot__returns_tile_coords_just_below_the_left_edge)
{
   // TODO
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   get_tile_coords_below_right_foot__returns_tile_coords_just_below_the_right_edge)
{
   // TODO
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   step__when_a_collision_occurs_along_the_positive_x_axis__will_return_collision_info_with_the_expected_values)
{
   // TODO
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   step__when_a_collision_occurs_along_the_negative_x_axis__will_return_collision_info_with_the_expected_values)
{
   // TODO
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   step__when_a_collision_occurs_along_the_positive_y_axis__will_return_collision_info_with_the_expected_values)
{
   // TODO
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   step__when_a_collision_occurs_along_the_negative_y_axis__will_return_collision_info_with_the_expected_values)
{
   // TODO
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest, tiles_within__returns_the_expected_values)
{
   AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper;
   std::vector<AllegroFlare::Physics::Int2D> expected_result_tiles = {
      {20, 7},  {21, 7},  {22, 7},  {23, 7},
      {20, 8},  {21, 8},  {22, 8},  {23, 8},
      {20, 9},  {21, 9},  {22, 9},  {23, 9},
      {20, 10}, {21, 10}, {22, 10}, {23, 10},
      {20, 11}, {21, 11}, {22, 11}, {23, 11}
   };
   std::vector<AllegroFlare::Physics::Int2D> actual_result_tiles =
      tile_map_collision_stepper.tiles_within(80, 60, 16-1, 16*2-1, 4, 8);

   EXPECT_EQ(expected_result_tiles, actual_result_tiles);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest, get_stepped_tile_collisions__returns_the_expected_values)
{
   using AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo;
   auto EVENT_ENTERED = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED;
   auto EVENT_STAYED_ON = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_STAYED_ON;
   auto EVENT_EXITED = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_EXITED;

   AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper;
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> expected_result_collisions =
   {
      TileMapCollisionStepperCollisionInfo({3, 4}, -999, -8, 8, false, EVENT_STAYED_ON),
      TileMapCollisionStepperCollisionInfo({3, 5}, -999, -8, 8, false, EVENT_STAYED_ON),
      TileMapCollisionStepperCollisionInfo({2, 4}, -999, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({2, 5}, -999, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({2, 6}, -999, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({3, 6}, -999, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({3, 3}, -999, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 3}, -999, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 4}, -999, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 5}, -999, -8, 8, false, EVENT_EXITED),
   };
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> actual_result_collisions =
      tile_map_collision_stepper.get_stepped_tile_collisions(50, 60, -8, 8, 16-1, 16*2-1, 16, 16);

   EXPECT_EQ(expected_result_collisions, actual_result_collisions);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   get_stepped_tile_collisions__returns_the_expected_values_when_a_collision_tile_map_is_present)
{
   using AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo;
   auto EVENT_ENTERED = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED;
   auto EVENT_STAYED_ON = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_STAYED_ON;
   auto EVENT_EXITED = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_EXITED;

   AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
   collision_tile_map.initialize();
   load_increment_tile_num_map(collision_tile_map);

   AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper(&collision_tile_map);
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> expected_result_collisions =
   {
      TileMapCollisionStepperCollisionInfo({3, 4}, 23, -8, 8, false, EVENT_STAYED_ON),
      TileMapCollisionStepperCollisionInfo({3, 5}, 28, -8, 8, false, EVENT_STAYED_ON),
      TileMapCollisionStepperCollisionInfo({2, 4}, 22, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({2, 5}, 27, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({2, 6}, -1, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({3, 6}, -1, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({3, 3}, 18, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 3}, 19, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 4}, 24, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 5}, 29, -8, 8, false, EVENT_EXITED),
   };
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> actual_result_collisions =
      tile_map_collision_stepper.get_stepped_tile_collisions(50, 60, -8, 8, 16-1, 16*2-1, 16, 16);

   EXPECT_EQ(expected_result_collisions, actual_result_collisions);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   step__when_there_are_no_solid_blocks__returns_expected_results)
{
   using AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo;
   auto EVENT_ENTERED = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED;
   auto EVENT_STAYED_ON = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_STAYED_ON;
   auto EVENT_EXITED = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_EXITED;

   AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
   collision_tile_map.initialize();
   load_increment_tile_num_map(collision_tile_map);

   AllegroFlare::Physics::AABB2D aabb2d(50, 60, 16-2, 16*2-1, -8, 8);

   AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper(&collision_tile_map, &aabb2d);
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> expected_result_collisions =
   {
      TileMapCollisionStepperCollisionInfo({3, 4}, 23, -8, 8, false, EVENT_STAYED_ON),
      TileMapCollisionStepperCollisionInfo({3, 5}, 28, -8, 8, false, EVENT_STAYED_ON),
      TileMapCollisionStepperCollisionInfo({2, 4}, 22, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({2, 5}, 27, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({2, 6}, -1, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({3, 6}, -1, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({3, 3}, 18, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 3}, 19, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 4}, 24, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 5}, 29, -8, 8, false, EVENT_EXITED),
   };
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> actual_result_collisions =
      tile_map_collision_stepper.step();

   EXPECT_EQ(expected_result_collisions, actual_result_collisions);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   step__when_solid_blocks_are_present__returns_expected_results)
{
   using AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo;
   auto EVENT_COLLIDED_AGAINST = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST;
   auto EVENT_ENTERED = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED;
   auto EVENT_STAYED_ON = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_STAYED_ON;
   auto EVENT_EXITED = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_EXITED;

   AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
   collision_tile_map.initialize();
   load_increment_tile_num_map(collision_tile_map);

   // add a "solid" tile to the map, blocking the path of the aabb2d within this step
   collision_tile_map.set_tile(2, 4, 1); // "1" is a default solid tile

   AllegroFlare::Physics::AABB2D aabb2d(50, 60, 16-2, 16*2-1, -8, 8);

   AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper(&collision_tile_map, &aabb2d);
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> expected_result_collisions =
   {
      TileMapCollisionStepperCollisionInfo({2, 4}, 1, -8, 8, true, EVENT_COLLIDED_AGAINST),
      TileMapCollisionStepperCollisionInfo({3, 4}, 23, -8, 8, false, EVENT_STAYED_ON),
      TileMapCollisionStepperCollisionInfo({3, 5}, 28, -8, 8, false, EVENT_STAYED_ON),
      TileMapCollisionStepperCollisionInfo({3, 6}, -1, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({3, 3}, 18, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 3}, 19, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 4}, 24, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 5}, 29, -8, 8, false, EVENT_EXITED),
   };
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> actual_result_collisions =
      tile_map_collision_stepper.step();

   EXPECT_EQ(expected_result_collisions, actual_result_collisions);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   DISABLED__step__when_solid_blocks_are_present__will_reposition_the_aabb2d_ajacent_to_the_collided_block)
{
   using AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo;
   AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
   collision_tile_map.initialize();
   load_increment_tile_num_map(collision_tile_map);
   collision_tile_map.set_tile(2, 4, 1); // "1" is a default solid tile
   AllegroFlare::Physics::AABB2D aabb2d(50, 60, 16-2, 16*2-1, -8, 8);

   AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper(&collision_tile_map, &aabb2d);

   // TODO: Fix this test data
   // TODO: Undisable this test
   AllegroFlare::Physics::AABB2D expected_result_aabb2d(50, 60, 16-2, 16*2-1, -8, 8);
   FAIL() << "Test data is not correct.";
   // TODO: Use "expected_result_aabb2d" in this test
   EXPECT_EQ(aabb2d, aabb2d);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   step__when_solid_blocks_are_placed_at_any_location_on_the_map__will_reposition_aabb2d_as_expected)
{
   // TODO: Add deeper test coverage for the following test conditions:
   // - size
   // - center-of-mass
   // - edge-of-mass
   // - moving up
   // - moving down
   // - moving left
   // - moving right
   // - distance-to-edge

   int tile_map_num_columns = 300;
   int tile_map_num_rows = 100;

   using AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo;
   AllegroFlare::TileMaps::TileMap<int> collision_tile_map(tile_map_num_columns, tile_map_num_rows);
   collision_tile_map.initialize();

   float tile_width = 16.0f;
   float tile_height = 16.0f;

   int solid_tile_x = 0;
   int solid_tile_y = 0;
   float player_w = tile_width - 1;
   // TODO: Perform the step (larger than tile, same as tile, smaller than tile
   float player_h = (tile_height*2) - 1;

   int num_steps_x = tile_map_num_columns; // TODO: Expand this to more than 100 tiles
   int num_steps_y = tile_map_num_rows;


   for (int i=0; i<num_steps_x; i++)
   //int i= 149; // passing
   //int i= 150; // failing
   {
      for (int j=0; j<num_steps_y; j++)
      {
         solid_tile_x = i;
         solid_tile_y = j;

         float test_position_align_y = 0.0; // TODO: Modify this value across 0.0 - 1.0

         collision_tile_map.clear();
         collision_tile_map.set_tile(solid_tile_x, solid_tile_y, 1); // "1" is a default solid tile

         // TODO: Update to acomodate multiple steps-sizes (very narrow, normal, passing-through)
         float player_x = (solid_tile_x*tile_width) - player_w - 1;
         float player_y = (solid_tile_y*tile_height) // set the anchor point where y is tested
                        - (player_h * test_position_align_y) // align the player box vertically
                        + ((test_position_align_y*2 - 1.0)) // offset by one pixel into the collision target
                        ;
         float player_vx = (tile_width * 0.5); // moving to the right at a velocity of 1/2 a tile per step
         float player_vy = 0;
         AllegroFlare::Physics::AABB2D aabb2d(player_x, player_y, player_w, player_h, player_vx, player_vy);

         // TODO: Perform the step bottom of box, center of box, top of box
         // Perform the step
         AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper(
            &collision_tile_map,
            &aabb2d,
            tile_width,
            tile_height
         );
         tile_map_collision_stepper.step();

         float expected_result_bb_x = (solid_tile_x*tile_width) - player_w - 0.0001;
         AllegroFlare::Physics::AABB2D expected_result_aabb2d(expected_result_bb_x, 0, 16-1, 16*2-1, 0, 0);

         // TODO: Work in this image capture on error
         //float threshold = 0.00001;
         //bool error_expected = (expected_result_aabb2d.get_x() != aabb2d.get_x());

         //if (error_expected)
         //{
            // Work in this tests code to capture image of error state
            //al_init();
            //ALLEGRO_BITMAP *result_bitmap = al_create_bitmap(1920, 1080);
            //al_set_target_bitmap(result_bitmap);
            //al_clear_to_color(ALLEGRO_COLOR{1, 1, 1, 1});
            //std::string asdf = "/Users/markoates/Desktop/asf.png";
            //al_save_bitmap(asdf.c_str(), result_bitmap);
            //al_uninstall_system();
         //}

         ASSERT_FLOAT_EQ(expected_result_aabb2d.get_x(), aabb2d.get_x()) << "Test on tile ("
                                                                         << solid_tile_x << ", "
                                                                         << solid_tile_y << "), ";
      }
   }
}


