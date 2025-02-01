#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/RepeatingBitmapLogic.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/Camera2D.hpp>


class AllegroFlare_RepeatingBitmapLogicTest : public ::testing::Test {};
class AllegroFlare_RepeatingBitmapLogicTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_RepeatingBitmapLogicTestWithInteractionFixture : public AllegroFlare::Testing::WithInteractionFixture
{};



TEST_F(AllegroFlare_RepeatingBitmapLogicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RepeatingBitmapLogic repeating_bitmap_logic;
}


TEST_F(AllegroFlare_RepeatingBitmapLogicTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   ALLEGRO_BITMAP *bitmap = get_bitmap_bin_ref()["backgrounds/SkyAndCloud5.png"];
   AllegroFlare::Camera2D camera;
   camera.size = { 1920, 1080 };
   camera.set_zoom({ 0.8, 0.8 });

   clear();

   camera.start_reverse_transform();
   AllegroFlare::RepeatingBitmapLogic repeating_bitmap_logic(bitmap);
   repeating_bitmap_logic.draw_repeating_rows_and_columns();
   camera.restore_transform();

   al_flip_display();
}


//#include <AllegroFlare/EventEmitter.hpp>
//#include <AllegroFlare/EventNames.hpp>

TEST_F(AllegroFlare_RepeatingBitmapLogicTestWithInteractionFixture, CAPTURE__INTERACTIVE__will_work_as_expected)
{
   //al_install_keyboard();
   //ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   //ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   //AllegroFlare::EventEmitter event_emitter;
   //event_emitter.initialize();
   //al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   //al_register_event_source(event_queue, al_get_keyboard_event_source());
   //al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // Setup our resources
   //AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   //ALLEGRO_FONT *font = get_any_font();
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   ALLEGRO_BITMAP *bitmap = bitmap_bin["backgrounds/SkyAndCloud5.png"];

   //AllegroFlare::Elements::Backgrounds::MultiLayer::Layers::SingleObject single_object;
   //single_object.set_bitmap(bitmap_bin.auto_get("backgrounds/Cloud2.png"));
   //single_object.set_bitmap(bitmap_bin.auto_get("backgrounds/cloud_dark-01.png"));
   //AllegroFlare::Velocity2D &object_velocity = single_object.get_velocity_ref();
   //single_object.fit_placement_dimensions_to_bitmap_dimensions();
   //single_object.set_repeat_along_x_axis(true);
   //single_object.fit_repeat_x_distance_to_bitmap_width();
   //single_object.set_repeat_along_y_axis(true);
   //single_object.set_repeat_y_distance(400);
   //single_object.fit_repeat_y_distance_to_bitmap_height();
   //single_object.set_scroll_rate_x(0.5);
   //single_object.set_scroll_rate_y(0.5);
   //single_object.get_placement_ref().align = { 0, 0 };

   // Setup camera variables
   //double step_duration = 1.0/60.0;
   //float camera_x = 0.0f;
   //float camera_y = 0.0f;
   //float camera_velocity_x = -1.0f;
   //float camera_velocity_y = 0.0f;
   //AllegroFlare::Placement2D camera;
   AllegroFlare::Camera2D camera;
   camera.size = { 1920, 1080 };
   camera.set_zoom({ 0.8, 0.8 });

   AllegroFlare::Vec2D camera_control_movement;

   //al_start_timer(primary_timer);
   //bool abort = false;
   //while(!abort)
   while(interactive_test_wait_for_event())
   {
      //ALLEGRO_EVENT current_event;
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();
      //al_wait_for_event(event_queue, &current_event);

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            camera.position.x += camera_control_movement.x * 10;
            camera.position.y += camera_control_movement.y * 10;

            clear();

            camera.start_reverse_transform();

            float camera_frame_top, camera_frame_right, camera_frame_bottom, camera_frame_left;
            std::tie(camera_frame_top, camera_frame_right, camera_frame_bottom, camera_frame_left) =
                  camera.get_outermost_coordinates_trbl();

            AllegroFlare::RepeatingBitmapLogic repeating_bitmap_logic(bitmap, -3, -2, 3, 2);
            //repeating_bitmap_logic.set_scroll_rate_x(0.5);
            //repeating_bitmap_logic.set_scroll_rate_y(0.5);
            repeating_bitmap_logic.fit_loop_width_to_bitmap_width();
            repeating_bitmap_logic.fit_loop_height_to_bitmap_height();
            repeating_bitmap_logic.fit_rows_and_columns_to_frame(
                  camera_frame_left,
                  camera_frame_top,
                  camera_frame_right,
                  camera_frame_bottom
               );
            repeating_bitmap_logic.fit_placement_dimensions_to_bitmap_dimensions();
            repeating_bitmap_logic.get_placement_ref().align = { 0, 0 };
            //repeating_bitmap_logic.get_placement_ref().align = { 0.5, 0.5 };
            //repeating_bitmap_logic.get_placement_ref().size = { 2.5, 2.5 };
            //repeating_bitmap_logic.get_placement_ref().align = { 2.5, 2.5 };
            //float camera_frame_top, camera_frame_right, camera_frame_bottom, camera_frame_left;
            //std::tie(camera_frame_top, camera_frame_right, camera_frame_bottom, camera_frame_left) =
                  //camera.get_outermost_coordinates_trbl();
            //repeating_bitmap_logic.fit_placement_dimensions_to_bitmap_dimensions

            repeating_bitmap_logic.draw_repeating_rows_and_columns();

            // Origin frame
            //al_draw_rectangle(0, 0, repeating_bitmap_logic.placement.x, repeating_bitmap_logic.placement.y);
            draw_crosshair(0, 0); // Origin crosshair
            camera.restore_transform();

            interactive_test_render_status();
            al_flip_display();
         }
         break;

         //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         //{
            //std::cout << "[AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest]: INFO: "
                      //<< "Play sound effect event was emitted. "
                      //<< std::endl;
         //}
         //break;

         case ALLEGRO_EVENT_KEY_DOWN:
         {
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  camera_control_movement.y = -1.0f;
               break;

               case ALLEGRO_KEY_DOWN:
                  camera_control_movement.y = 1.0f;
               break;

               case ALLEGRO_KEY_LEFT:
                  camera_control_movement.x = -1.0f;
               break;

               case ALLEGRO_KEY_RIGHT:
                  camera_control_movement.x = 1.0f;
               break;

               case ALLEGRO_KEY_PAD_PLUS: {
                  float zoom = camera.get_zoom().x;
                  zoom += 0.2;
                  camera.set_zoom({ zoom, zoom });
               } break;

               case ALLEGRO_KEY_PAD_MINUS: {
                  float zoom = camera.get_zoom().x;
                  zoom -= 0.2;
                  camera.set_zoom({ zoom, zoom });
               } break;

               //case ALLEGRO_KEY_ESCAPE:
                  //abort = true;
               //break;
            }
         }
         break;

         case ALLEGRO_EVENT_KEY_UP:
         {
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  camera_control_movement.y = 0.0f;
               break;

               case ALLEGRO_KEY_DOWN:
                  camera_control_movement.y = 0.0f;
               break;

               case ALLEGRO_KEY_LEFT:
                  camera_control_movement.x = 0.0f;
               break;

               case ALLEGRO_KEY_RIGHT:
                  camera_control_movement.x = 0.0f;
               break;
            }
         }
         break;
      }
   }

   //al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   //al_destroy_timer(primary_timer);
}


