#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Prototypes_MindDive_MindDiveTest : public ::testing::Test {};
class AllegroFlare_Prototypes_MindDive_MindDiveTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Prototypes/MindDive/MindDive.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/EventEmitter.hpp>


TEST_F(AllegroFlare_Prototypes_MindDive_MindDiveTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::MindDive mind_dive;
}


TEST_F(AllegroFlare_Prototypes_MindDive_MindDiveTestWithAllegroRenderingFixture,
   CAPTURE__basic_update_and_render_will_work_as_expected)
{
   AllegroFlare::Prototypes::MindDive::MindDive mind_dive(&get_bitmap_bin_ref(), &get_font_bin_ref());
   mind_dive.initialize();

   clear();

   mind_dive.update();
   mind_dive.render();

   al_flip_display();
}


TEST_F(AllegroFlare_Prototypes_MindDive_MindDiveTestWithAllegroRenderingFixture,
   INTERACTIVE__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   //al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // setup environment
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject
   
   AllegroFlare::Prototypes::MindDive::MindDive mind_dive;
   mind_dive.set_bitmap_bin(&get_bitmap_bin_ref());
   mind_dive.set_font_bin(&get_font_bin_ref());
   mind_dive.initialize();
   //mind_dive.set_event_emitter(&event_emitter);

   // start the level
   mind_dive.reset();

   // run the interactive test
   al_start_timer(primary_timer);
   while(!abort)
   {
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_DOWN:
         {
            switch(event.keyboard.keycode)
            {
               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;

               case ALLEGRO_KEY_UP:
                  mind_dive.surfer_accelerate();
               break;

               case ALLEGRO_KEY_DOWN:
                  mind_dive.surfer_reverse();
               break;

               case ALLEGRO_KEY_RIGHT:
                  mind_dive.surfer_move_right();
               break;

               case ALLEGRO_KEY_LEFT:
                  mind_dive.surfer_move_left();
               break;

               case ALLEGRO_KEY_R:
                  mind_dive.reset();
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_KEY_UP:
         {
            switch(event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
               case ALLEGRO_KEY_DOWN:
                  mind_dive.surfer_stop();
               break;

               case ALLEGRO_KEY_RIGHT:
                  mind_dive.surfer_move_horizontal_none();
               break;

               case ALLEGRO_KEY_LEFT:
                  mind_dive.surfer_move_horizontal_none();
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            mind_dive.update();

            clear();
            mind_dive.render();
            al_flip_display();
         break;
      }

      //if (event.type == ALLEGRO_EVENT_KEY_CHAR && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) abort = true;
   }
   
   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.
   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}


