
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/MultiList.hpp>

//#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
//#include <allegro5/allegro_primitives.h>

//#include <AllegroFlare/Screens/Subscreen/Panes/CharacterProfiles.hpp>


class AllegroFlare_Elements_MultiListTest : public ::testing::Test {};
class AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   std::vector<std::vector<std::pair<std::string, std::string>>> build_lists()
   {
      std::vector<std::vector<std::pair<std::string, std::string>>> result_lists = {
         {
            { "Standard Blaster", "blaster" },
            { "Double Turret", "turret" },
            { "Laser", "laser" },
            { "Missle", "missle" },
         },
         {
            { "Standard Shields", "standard" },
            { "Double Walled", "double_walled" },
            { "Plasma", "plasma" },
         },
         {
            { "Hypersonic Boost", "hypersonic_boost" },
            { "Cloaking", "cloak" },
            { "Wide Area EMP", "wide_area_emp" },
            { "Echo Sonar", "echo_sonar" },
         },
      };
      return result_lists;
   }
};


TEST_F(AllegroFlare_Elements_MultiListTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::MultiList multi_list;
}


TEST_F(AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::MultiList multi_list;
   multi_list.set_font_bin(&get_font_bin_ref());
   multi_list.initialize();

   multi_list.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture, CAPTURE__render__will_render_as_expected)
{
   AllegroFlare::Elements::MultiList multi_list;
   multi_list.set_font_bin(&get_font_bin_ref());
   multi_list.initialize();

   multi_list.set_lists(build_lists());

   multi_list.get_placement_ref().position.x = 180;
   multi_list.get_placement_ref().position.y = 200;
   multi_list.set_cursor_position(2, 1);

   multi_list.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture, calculate_width__will_return_the_expected_size)
{
   // TODO: See if this test can be trimmed down
   AllegroFlare::Elements::MultiList multi_list;
   multi_list.set_font_bin(&get_font_bin_ref());
   multi_list.initialize();

   multi_list.set_lists(build_lists());

   EXPECT_EQ(1600, multi_list.calculate_width()); // TODO: Check if this is actually correct
}


TEST_F(AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture,
   CAPTURE__move_cursor_right__will_work_as_expected)
{
   // TODO: See if this test can be trimmed down
   AllegroFlare::Elements::MultiList multi_list;
   multi_list.set_font_bin(&get_font_bin_ref());
   multi_list.initialize();

   multi_list.set_lists(build_lists());

   int passes = 4;
   for (int i=0; i<passes; i++)
   {
      clear();
      multi_list.render();
      al_flip_display();
      al_rest(0.1);

      multi_list.move_cursor_right();
   }
}


TEST_F(AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture,
   CAPTURE__move_cursor_left__will_work_as_expected)
{
   // TODO: See if this test can be trimmed down
   AllegroFlare::Elements::MultiList multi_list;
   multi_list.set_font_bin(&get_font_bin_ref());
   multi_list.initialize();

   multi_list.set_lists(build_lists());

   int passes = 4;
   for (int i=0; i<passes; i++)
   {
      clear();
      multi_list.render();
      al_flip_display();
      al_rest(0.1);

      multi_list.move_cursor_left();
   }
}


TEST_F(AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture,
   TIMED_INTERACTIVE__will_work_as_expected)
{
   // Setup interactive components not already setup in WithAllegroRenderingFixture
   al_install_keyboard();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   // Setup subject here
   AllegroFlare::Elements::MultiList multi_list;
   multi_list.set_font_bin(&get_font_bin_ref());
   multi_list.initialize();
   multi_list.set_lists(build_lists());

   // Setup the timed interactive
   float duration_to_auto_abort_test = 6.0;
   bool auto_abort_halted = false;

   // Start the interactive loop
   al_start_timer(primary_timer);
   bool abort = false;
   while(!abort)
   {
      double time_now = al_get_time();
      ALLEGRO_EVENT current_event;
      al_wait_for_event(event_queue, &current_event);
      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            // Update
            if (!auto_abort_halted && (time_now >= duration_to_auto_abort_test)) abort = true;

            // Render
            clear();
            multi_list.render();
            if (!auto_abort_halted)
            {
               int seconds_left = (int)(duration_to_auto_abort_test - time_now) + 1;
               al_draw_textf(get_user_prompt_font(), ALLEGRO_COLOR{0.3, 0.3, 0.3, 1}, 30, 1080-60, ALLEGRO_ALIGN_LEFT,
                  "Interactive test will auto-close in %d seconds. Otherwise press any key.", seconds_left);
            }
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

         case ALLEGRO_EVENT_KEY_UP:
         {
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  // Nothing
               break;

               case ALLEGRO_KEY_DOWN:
                  // Nothing
               break;

               case ALLEGRO_KEY_LEFT:
                  // Nothing
               break;

               case ALLEGRO_KEY_RIGHT:
                  // Nothing
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_KEY_DOWN:
         {
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  multi_list.move_cursor_up();
               break;

               case ALLEGRO_KEY_DOWN:
                  multi_list.move_cursor_down();
               break;

               case ALLEGRO_KEY_LEFT:
                  multi_list.move_cursor_left();
               break;

               case ALLEGRO_KEY_RIGHT:
                  multi_list.move_cursor_right();
               break;

               case ALLEGRO_KEY_ENTER:
                  multi_list.activate_selection_at_current_cursor_position();
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            auto_abort_halted = true;
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {

               case ALLEGRO_KEY_UP:
                  // Nothing
               break;

               case ALLEGRO_KEY_DOWN:
                  // Nothing
               break;

               case ALLEGRO_KEY_LEFT:
                  // Nothing
               break;

               case ALLEGRO_KEY_RIGHT:
                  // Nothing
               break;

               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;
            }
         }
         break;
      }
   }

   //al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_timer(primary_timer);
}


