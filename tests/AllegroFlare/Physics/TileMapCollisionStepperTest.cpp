
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/Logger.hpp>
#include <allegro5/allegro_color.h>

class AllegroFlare_Physics_TileMapCollisionStepperTest : public ::testing::Test
{};
class AllegroFlare_Physics_TileMapCollisionStepperTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Physics_TileMapCollisionStepperTestWithInteractionFixture :
   public AllegroFlare::Testing::WithInteractionFixture
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
   step__without_a_collision_tile_map__initialized__raises_an_error)
{
   AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::Physics::TileMapCollisionStepper::step",
      "collision_tile_map"
   );
   EXPECT_THROW_WITH_MESSAGE(tile_map_collision_stepper.step(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest, step__without_an_aabb2d__raises_an_error)
{
   AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
   AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper(&collision_tile_map);
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::Physics::TileMapCollisionStepper::step",
      "aabb2d"
   );
   EXPECT_THROW_WITH_MESSAGE(tile_map_collision_stepper.step(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   world_coords_to_tile_coords__will_return_the_tile_coordinates_of_a_world_coordinate)
{
   EXPECT_EQ(2, AllegroFlare::Physics::TileMapCollisionStepper::world_coords_to_tile_coords(32+1, 16));
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   world_coords_to_tile_coords__will_provide_correct_coordinates_with_negative_numbers)
{
   EXPECT_EQ(-3, AllegroFlare::Physics::TileMapCollisionStepper::world_coords_to_tile_coords(-32-1, 16));
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTestWithInteractionFixture,
   //INTERACTIVE__world_coords_to_tile_coords__will_provide_expected_tile_coordinates)
   DISABLED__INTERACTIVE__world_coords_to_tile_coords__will_provide_expected_tile_coordinates)
{
   float coord_x = 0.0f;
   float coord_y = 0.0f;
   float tile_size = 32;
   ALLEGRO_COLOR tile_color = al_color_name("aquamarine");

   ALLEGRO_TRANSFORM camera_transform;
   al_identity_transform(&camera_transform);
   al_scale_transform(&camera_transform, 2.0, 2.0);
   al_translate_transform(&camera_transform, 1920/2, 1080/2);

   ALLEGRO_TRANSFORM hud_transform;
   al_identity_transform(&hud_transform);

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            clear();

            // Draw world
            al_use_transform(&camera_transform);

            int tile_coord_x =
               AllegroFlare::Physics::TileMapCollisionStepper::world_coords_to_tile_coords(coord_x, tile_size);
            int tile_coord_y =
               AllegroFlare::Physics::TileMapCollisionStepper::world_coords_to_tile_coords(coord_y, tile_size);

            draw_crosshair(coord_x, coord_y);
            al_draw_rectangle(
               tile_coord_x * tile_size,
               tile_coord_y * tile_size,
               tile_coord_x * tile_size + tile_size,
               tile_coord_y * tile_size + tile_size,
               tile_color,
               1.0
            );

            // Draw some debug text
            al_use_transform(&hud_transform);

            ALLEGRO_FONT *font = get_any_font();
            int lh = al_get_font_line_height(font);
            al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 20+lh*0, 0, "coord_x: %.3f", coord_x);
            al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 20+lh*1, 0, "coord_y: %.3f", coord_y);

            interactive_test_render_status();
            al_flip_display();
         }
         break;

         //// For example:
         //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         //{
            //std::cout << "[AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture]: INFO: "
                      //<< "Play sound effect event was emitted. "
                      //<< std::endl;
         //}
         //break;

         //// For example:
         case ALLEGRO_EVENT_KEY_CHAR: {
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_RIGHT:
                  coord_x += 1.0;
               break;

               case ALLEGRO_KEY_LEFT:
                  coord_x -= 1.0;
               break;

               case ALLEGRO_KEY_UP:
                  coord_y -= 1.0;
               break;

               case ALLEGRO_KEY_DOWN:
                  coord_y += 1.0;
               break;
            }
         } break;
      }
   }
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTestWithInteractionFixture,
   get_next_collided_tile_coords_1d__will_provide_expected_tile_coordinates)
{
   float coord_x = 4.0f;
   float coord_y = 1.0f;
   float coord_w = 8.0f;
   float coord_h = 16.0f;
   float horizontal_velocity = 6.0;
   float tile_size = 16;

   std::vector<AllegroFlare::Physics::Int2D> expected_next_tile_coords = {
      { 1, 0 }, { 1, 1 }
   };

   std::vector<AllegroFlare::Physics::Int2D> actual_next_tile_coords =
      AllegroFlare::Physics::TileMapCollisionStepper::get_next_collided_tile_coords_1d(
         coord_x,
         coord_y,
         horizontal_velocity,
         coord_w,
         coord_h,
         tile_size,
         tile_size
      );

   EXPECT_EQ(expected_next_tile_coords, actual_next_tile_coords);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTestWithInteractionFixture,
   get_next_collided_tile_coords_1d__will_provide_expected_tile_coordinates_when_in_negative_values)
{
   float coord_x = 4.0f;
   float coord_y = -8.0f;
   float coord_w = 8.0f;
   float coord_h = 16.0f;
   float horizontal_velocity = 6.0;
   float tile_size = 16;

   std::vector<AllegroFlare::Physics::Int2D> expected_next_tile_coords = {
      { 1, -1 }, { 1, 0 }
   };

   std::vector<AllegroFlare::Physics::Int2D> actual_next_tile_coords =
      AllegroFlare::Physics::TileMapCollisionStepper::get_next_collided_tile_coords_1d(
         coord_x,
         coord_y,
         horizontal_velocity,
         coord_w,
         coord_h,
         tile_size,
         tile_size
      );

   EXPECT_EQ(expected_next_tile_coords, actual_next_tile_coords);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTestWithInteractionFixture,
   //INTERACTIVE__get_next_collided_tile_coords_1d__will_provide_expected_tile_coordinates)
   DISABLED__INTERACTIVE__get_next_collided_tile_coords_1d__will_provide_expected_tile_coordinates)
{
   float coord_x = 0.0f;
   float coord_y = 0.0f;
   float coord_w = 8.0f;
   float coord_h = 16.0f;
   float horizontal_velocity = 6.0;
   float tile_size = 32;
   ALLEGRO_COLOR player_color = al_color_name("blueviolet");
   ALLEGRO_COLOR tile_color = al_color_name("aquamarine");
   ALLEGRO_COLOR next_tile_color = al_color_name("yellow");
   ALLEGRO_COLOR grid_color = al_color_name("slategray");
   ALLEGRO_FONT *font = get_any_font();

   float camera_scale = 2.0f;
   ALLEGRO_TRANSFORM camera_transform;
   al_identity_transform(&camera_transform);
   al_scale_transform(&camera_transform, camera_scale, camera_scale);
   al_translate_transform(&camera_transform, 1920/2, 1080/2);

   ALLEGRO_TRANSFORM hud_transform;
   al_identity_transform(&hud_transform);

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            clear();

            // Draw world
            al_use_transform(&camera_transform);

            // Draw a baisc grid showing positive and negative space
            int grid_line_width = 1920/6;
            int grid_line_height = 1080/6;
            al_draw_line(-grid_line_width, 0, grid_line_width, 0, grid_color, 1.0);
            al_draw_line(0, -grid_line_height, 0, grid_line_height, grid_color, 1.0);

            int tile_coord_x =
               AllegroFlare::Physics::TileMapCollisionStepper::world_coords_to_tile_coords(coord_x, tile_size);
            int tile_coord_y =
               AllegroFlare::Physics::TileMapCollisionStepper::world_coords_to_tile_coords(coord_y, tile_size);
            std::vector<AllegroFlare::Physics::Int2D> next_tile_coords_x =
               AllegroFlare::Physics::TileMapCollisionStepper::get_next_collided_tile_coords_1d(
                  coord_x,
                  coord_y,
                  horizontal_velocity,
                  coord_w,
                  coord_h,
                  tile_size,
                  tile_size
               );

            // Draw player point
            al_draw_rectangle(
               coord_x,
               coord_y,
               coord_x + coord_w,
               coord_y + coord_h,
               player_color,
               1.0
            );
            draw_crosshair(coord_x, coord_y);

            // Draw Current box rectangle
            al_draw_rectangle(
               tile_coord_x * tile_size,
               tile_coord_y * tile_size,
               tile_coord_x * tile_size + tile_size,
               tile_coord_y * tile_size + tile_size,
               tile_color,
               1.0
            );

            // Draw the next_tile_coords_x
            for (auto &next_tile_coord_x : next_tile_coords_x)
            {
               //next_tile_coord_x
               al_draw_rectangle(
                  next_tile_coord_x.get_x() * tile_size,
                  next_tile_coord_x.get_y() * tile_size,
                  next_tile_coord_x.get_x() * tile_size + tile_size,
                  next_tile_coord_x.get_y() * tile_size + tile_size,
                  next_tile_color,
                  1.0
               );
            }

            // Draw some debug text
            al_use_transform(&hud_transform);

            int lh = al_get_font_line_height(font);
            al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 20+lh*0, 0, "coord_x: %.3f", coord_x);
            al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 20+lh*1, 0, "coord_y: %.3f", coord_y);
            //al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 20+lh*1, 0, "camera_scale: %.3f", coord_y);
            al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 20+lh*3, 0, "camera_scale: %.3f", camera_scale);
            al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 20+lh*4, 0, "horizontal_velocity: %.3f", horizontal_velocity);
            al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 20+lh*5, 0, "tile_size: %.3f", tile_size);

            interactive_test_render_status();
            al_flip_display();
         }
         break;

         //// For example:
         //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         //{
            //std::cout << "[AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture]: INFO: "
                      //<< "Play sound effect event was emitted. "
                      //<< std::endl;
         //}
         //break;

         //// For example:
         case ALLEGRO_EVENT_KEY_CHAR: {
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_RIGHT:
                  coord_x += 1.0;
               break;

               case ALLEGRO_KEY_LEFT:
                  coord_x -= 1.0;
               break;

               case ALLEGRO_KEY_UP:
                  coord_y -= 1.0;
               break;

               case ALLEGRO_KEY_DOWN:
                  coord_y += 1.0;
               break;
            }
         } break;
      }
   }
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
   AllegroFlare::Physics::AABB2D aabb2d(80, 60, 8 - 1, 6*2 - 1);
   collision_tile_map.initialize();
   load_test_map(collision_tile_map);
   AllegroFlare::Placement2D camera;
   camera.scale.x = 4.8 * 0.7;
   camera.scale.y = 4.5 * 0.7;
   camera.position.x = 100;
   camera.position.y = 100;

   bool aabb2d_adjacent_to_bottom_edge = false;
   bool aabb2d_adjacent_to_top_edge = false;
   bool aabb2d_adjacent_to_right_edge = false;
   bool aabb2d_adjacent_to_left_edge = false;

   bool invert_gravity = false;
   bool gravity_enabled = false;
   bool vertical_movement_controls_active = true;
   //bool debug_trap_on = false;

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
                 aabb2d.set_velocity_y(invert_gravity ? 4.0f : -4.0f);
               break;

               case ALLEGRO_KEY_I:
                 invert_gravity = !invert_gravity;
               break;

               case ALLEGRO_KEY_G:
                 gravity_enabled = !gravity_enabled;
                 vertical_movement_controls_active = !vertical_movement_controls_active;
               break;

               //case ALLEGRO_KEY_V:
                 //vertical_movement_controls_active = !vertical_movement_controls_active;
               //break;

               //case ALLEGRO_KEY_D:
                 //aabb2d.set_velocity_x(1);
                 //debug_trap_on = true;
               //break;
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
               //if (debug_trap_on) tile_map_collision_stepper.debug_trap_on = debug_trap_on;
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
   float player_w = tile_width - 4;
   // TODO: Perform the step (larger than tile, same as tile, smaller than tile
   float player_h = (tile_height*2) - 8;

   int num_steps_x = tile_map_num_columns; // TODO: Expand this to more than 100 tiles
   int num_steps_y = tile_map_num_rows;

   float depth_out_from_edge;
   float velocity_x;
   float reposition_offset;

   //{ // Simple depth
      //depth_out_from_edge = 1.0f;
      //velocity_x = (tile_width * 0.5);
      //float reposition_offset = AllegroFlare::Physics::TileMapCollisionStepper::DEFAULT_REPOSITION_OFFSET;
   //}
   { // Narrow depth
      depth_out_from_edge = 0.001f;
      velocity_x = 0.0011f;
      //reposition_offset = AllegroFlare::Physics::TileMapCollisionStepper::DEFAULT_REPOSITION_OFFSET;
      reposition_offset = 0.0001f;
   }
   
   for (int i=0; i<num_steps_x; i++)
   {
      for (int j=0; j<num_steps_y; j++)
      {
         solid_tile_x = i;
         solid_tile_y = j;

         float test_position_align_y = 0.0; // TODO: Modify this value across 0.0 - 1.0

         collision_tile_map.clear();
         collision_tile_map.set_tile(solid_tile_x, solid_tile_y, 1); // "1" is a default solid tile

         // TODO: Update to acomodate multiple steps-sizes (very narrow, normal, passing-through)
         float player_x = (solid_tile_x*tile_width) - player_w - depth_out_from_edge;
         float player_y = (solid_tile_y*tile_height) // set the anchor point where y is tested
                        - (player_h * test_position_align_y) // align the player box vertically
                        + ((test_position_align_y*2 - 1.0)) // offset by one pixel into the collision target
                        ;
         float player_vx = velocity_x; // moving to the right at a velocity of 1/2 a tile per step
         //float player_vx = (tile_width * 0.5); // moving to the right at a velocity of 1/2 a tile per step
         float player_vy = 0;
         AllegroFlare::Physics::AABB2D aabb2d(player_x, player_y, player_w, player_h, player_vx, player_vy);

         // TODO: Add test that the reposition offset, when applied to the player position, will result in a
         // distance from the edge

         //float position_x_before = player_x;
         //float position_y_before = player_y;

         // TODO: Perform the step bottom of box, center of box, top of box
         // Perform the step
         AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper(
            &collision_tile_map,
            &aabb2d,
            tile_width,
            tile_height,
            reposition_offset
         );
         tile_map_collision_stepper.step();

         //float position_x_after = aabb2d.get_x();
         //float position_y_after = aabb2d.get_y();

         float expected_result_bb_x = (solid_tile_x*tile_width) - player_w - reposition_offset;
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


//
// Tests related to collisions that are *outside* (in whole or in part) the bounds of the collision_tile_map
// Author: Gemini
//

TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   step__with_an_aabb_fully_outside_the_map_and_moving_away__does_not_create_a_collision_event)
{
   AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
   collision_tile_map.initialize();
   load_test_map(collision_tile_map);

   AllegroFlare::Physics::AABB2D aabb2d(-100, -100, 10, 10, -2, -2);
   AllegroFlare::Physics::AABB2D expected_aabb2d_after_step(-102, -102, 10, 10, -2, -2);

   AllegroFlare::Physics::TileMapCollisionStepper stepper(&collision_tile_map, &aabb2d);
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> collision_infos = stepper.step();

   // Expect no collision events against solid tiles
   for (auto &collision_info : collision_infos)
   {
      EXPECT_FALSE(collision_info.get_event() == AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST);
   }

   // Expect the AABB to have moved by its velocity without interference
   EXPECT_EQ(expected_aabb2d_after_step, aabb2d);
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   step__with_an_aabb_partially_outside_the_map__collides_with_solid_tiles_on_the_inside)
{
   using AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo;
   auto EVENT_COLLIDED_AGAINST = TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST;
   auto EDGE_TOP = TileMapCollisionStepperCollisionInfo::CollidingBlockEdge::EDGE_TOP;

   AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
   collision_tile_map.initialize();
   load_test_map(collision_tile_map); // Map bottom row (y=14) is solid. Tile top edge is at y=224.

   AllegroFlare::Physics::AABB2D aabb2d(-5, 210, 10, 10, 0, 15);

   AllegroFlare::Physics::TileMapCollisionStepper stepper(&collision_tile_map, &aabb2d);
   std::vector<TileMapCollisionStepperCollisionInfo> actual_collisions = stepper.step();

   TileMapCollisionStepperCollisionInfo expected_collision({0, 14}, 1, 0, 15, true, EVENT_COLLIDED_AGAINST, EDGE_TOP);

   // Find and validate the collision event within the list of all returned events
   bool found_collision_event = false;
   for (auto &collision : actual_collisions)
   {
      if (collision.get_event() == EVENT_COLLIDED_AGAINST)
      {
         EXPECT_EQ(expected_collision, collision);
         found_collision_event = true;
      }
   }
   ASSERT_TRUE(found_collision_event) << "The expected EVENT_COLLIDED_AGAINST was not found.";

   // Validate final AABB state
   float tile_top_edge = 14 * 16.0f;
   float expected_repositioned_y = tile_top_edge - aabb2d.get_h() - stepper.get_reposition_offset();
   EXPECT_FLOAT_EQ(expected_repositioned_y, aabb2d.get_y());
   EXPECT_FLOAT_EQ(0.0f, aabb2d.get_velocity_y());
}


TEST_F(AllegroFlare_Physics_TileMapCollisionStepperTest,
   step__with_an_aabb_moving_in_from_outside_the_map__collides_with_the_edge_tile_and_generates_correct_event_info)
{
   using AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo;
   auto EVENT_COLLIDED_AGAINST = TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST;
   auto EDGE_RIGHT = TileMapCollisionStepperCollisionInfo::CollidingBlockEdge::EDGE_RIGHT;

   AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
   collision_tile_map.initialize();
   load_test_map(collision_tile_map); // Map right edge (x=24) is solid.

   AllegroFlare::Physics::AABB2D aabb2d(405, 100, 10, 10, -10, 0);

   AllegroFlare::Physics::TileMapCollisionStepper stepper(&collision_tile_map, &aabb2d);
   std::vector<TileMapCollisionStepperCollisionInfo> actual_collisions = stepper.step();

   // Expect a collision with tile (24, 6) on its right edge.
   TileMapCollisionStepperCollisionInfo expected_collision({24, 6}, 1, -10, 0, true, EVENT_COLLIDED_AGAINST, EDGE_RIGHT);

   bool found_collision_event = false;
   for (auto &collision : actual_collisions)
   {
      if (collision.get_event() == EVENT_COLLIDED_AGAINST)
      {
         EXPECT_EQ(expected_collision, collision);
         found_collision_event = true;
      }
   }
   ASSERT_TRUE(found_collision_event) << "The expected EVENT_COLLIDED_AGAINST was not found.";

   // Validate final AABB state
   float tile_right_edge = (24 + 1) * 16.0f;
   float expected_repositioned_x = tile_right_edge + stepper.get_reposition_offset();
   EXPECT_FLOAT_EQ(expected_repositioned_x, aabb2d.get_x());
   EXPECT_FLOAT_EQ(0.0f, aabb2d.get_velocity_x());
}


