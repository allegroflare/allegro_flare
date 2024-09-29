
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>



class AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTest : public ::testing::Test {};
class AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTestWithInteractionFixture
   : public AllegroFlare::Testing::WithInteractionFixture
{};



TEST_F(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTest,
   process_script_event__on_a_subscribed_event_type__with_unknown_event_data_type__will_output_an_error_message_to_cout)
{
   // TODO
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTestWithInteractionFixture,
   CAPTURE__TIMED_INTERACTIVE__will_operate_as_expected)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;
   fixed_room_2d.set_font_bin(&get_font_bin_ref());
   fixed_room_2d.set_bitmap_bin(&get_bitmap_bin_ref());
   fixed_room_2d.set_event_emitter(&event_emitter);
   fixed_room_2d.initialize();

   //load_configuration.initialize();

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER: {
            clear();

            fixed_room_2d.update();
            fixed_room_2d.render();

            interactive_test_render_status();
            al_flip_display();
         } break;

         case ALLEGRO_EVENT_MOUSE_AXES: {
            int cursor_distance_x = current_event.mouse.dx;
            int cursor_distance_y = current_event.mouse.dy;
            fixed_room_2d.move_cursor(cursor_distance_x, cursor_distance_y);
         } break;

         //// For example:
         //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         //{
            //std::cout << "[AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture]: INFO: "
                      //<< "Play sound effect event was emitted. "
                      //<< std::endl;
         //}
         //break;

         //// For example:
         //case ALLEGRO_EVENT_KEY_DOWN:
         //{
            //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            //switch(current_event.keyboard.keycode)
            //{
               //case ALLEGRO_KEY_ENTER:
                  //// Do something
               //break;
            //}
         //}
         //break;
      }
   }
   
}


