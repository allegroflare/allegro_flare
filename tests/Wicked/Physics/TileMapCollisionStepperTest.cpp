
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Logger.hpp>

class Wicked_Physics_TileMapCollisionStepperTest : public ::testing::Test
{};

class Wicked_Physics_TileMapCollisionStepperTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <Wicked/Physics/TileMapCollisionStepper.hpp>

#include <AllegroFlare/Placement2D.hpp>

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
static void render_tile_map(
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
      Wicked::Physics::AABB2D &aabb2d,
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
      al_draw_line(aabb2d.get_x(), aabb2d.get_bottom_edge(), aabb2d.get_right_edge(), aabb2d.get_bottom_edge(), orange, 2.0);
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
      al_draw_line(aabb2d.get_right_edge(), aabb2d.get_y(), aabb2d.get_right_edge(), aabb2d.get_bottom_edge(), orange, 2.0);
   }
}

TEST_F(Wicked_Physics_TileMapCollisionStepperTest, can_be_created_without_blowing_up)
{
   Wicked::Physics::TileMapCollisionStepper tile_map_collision_stepper;
}


TEST_F(Wicked_Physics_TileMapCollisionStepperTest, step__without_a_collision_tile_map__initialized__raises_an_error)
{
   Wicked::Physics::TileMapCollisionStepper tile_map_collision_stepper;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Wicked::Physics::TileMapCollisionStepper::step",
      "collision_tile_map"
   );
   EXPECT_THROW_WITH_MESSAGE(tile_map_collision_stepper.step(), std::runtime_error, expected_error_message);
}


TEST_F(Wicked_Physics_TileMapCollisionStepperTest, step__without_an_aabb2d__raises_an_error)
{
   AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
   Wicked::Physics::TileMapCollisionStepper tile_map_collision_stepper(&collision_tile_map);
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Wicked::Physics::TileMapCollisionStepper::step",
      "aabb2d"
   );
   EXPECT_THROW_WITH_MESSAGE(tile_map_collision_stepper.step(), std::runtime_error, expected_error_message);
}


TEST_F(Wicked_Physics_TileMapCollisionStepperTestWithAllegroRenderingFixture,
   DISABLED__INTERACTIVE__will_work_as_expected)
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
   Wicked::Physics::AABB2D aabb2d(80, 60, 16 - 1, 16*2 - 1);
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
               Wicked::Physics::TileMapCollisionStepper tile_map_collision_stepper(
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


TEST_F(Wicked_Physics_TileMapCollisionStepperTest,
   get_tile_coords_below_left_foot__returns_tile_coords_just_below_the_left_edge)
{
   // TODO
}


TEST_F(Wicked_Physics_TileMapCollisionStepperTest,
   get_tile_coords_below_right_foot__returns_tile_coords_just_below_the_right_edge)
{
   // TODO
}


