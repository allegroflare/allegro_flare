
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithInteractionFixture.hpp>


class TestClassFor_AllegroFlare_Testing_WithInteractionFixture
   : public AllegroFlare::Testing::WithInteractionFixture
{};


TEST_F(TestClassFor_AllegroFlare_Testing_WithInteractionFixture, will_setup_and_teardown_without_blowing_up)
{
   // This test is testing the fixture
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithInteractionFixture, will_work_with_the_expected_context)
{
   while(!get_aborted())
   {
      double time_now = al_get_time();
      ALLEGRO_EVENT current_event;
      al_wait_for_event(get_event_queue(), &current_event);

      handle_interactive_test_event(&current_event);

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            clear();
            render_interactive_test_status();
            al_flip_display();
         }
         break;

         //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         //{
            //std::cout << "[AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture]: INFO: "
                      //<< "Play sound effect event was emitted. "
                      //<< std::endl;
         //}
         //break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_ESCAPE:
                  abort();
               break;
            }
         }
         break;
      }
   }
}


