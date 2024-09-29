
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ConfigurationFactory.hpp>



class AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTest : public ::testing::Test {};
class AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTestWithInteractionFixture
   : public AllegroFlare::Testing::WithInteractionFixture
{
public:
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;

public:
   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithInteractionFixture::SetUp();

      fixed_room_2d.set_font_bin(&get_font_bin_ref());
      fixed_room_2d.set_bitmap_bin(&get_bitmap_bin_ref());
      fixed_room_2d.set_event_emitter(&event_emitter);
      fixed_room_2d.initialize();
   }
   void load_configuration()
   {
      // TODO: Build configuration locally
      // TODO: Use room-01.png
      AllegroFlare::Prototypes::FixedRoom2D::Configuration source_configuration =
        AllegroFlare::Prototypes::FixedRoom2D::ConfigurationFactory::build_testing_configuration(
          &get_bitmap_bin_ref(), &get_font_bin_ref(), &event_emitter, &fixed_room_2d.get_entity_collection_helper_ref());
      fixed_room_2d.load_configuration(source_configuration);
   }
   void enter_start_room()
   {
      fixed_room_2d.enter_start_room();
   }
};



TEST_F(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTest,
   process_script_event__on_a_subscribed_event_type__with_unknown_event_data_type__will_output_an_error_message_to_cout)
{
   // TODO
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__when_no_room_is_loaded__will_render_a_void_room_and_an_empty_room_message)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;
   fixed_room_2d.set_font_bin(&get_font_bin_ref());
   fixed_room_2d.set_bitmap_bin(&get_bitmap_bin_ref());
   fixed_room_2d.set_event_emitter(&event_emitter);
   fixed_room_2d.initialize();

   clear();
   fixed_room_2d.render();
   al_flip_display();
   al_rest(1);
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTestWithInteractionFixture,
   FOCUS__CAPTURE__TIMED_INTERACTIVE__will_operate_as_expected)
{
   load_configuration();

   enter_start_room();

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


