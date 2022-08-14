
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/EventEmitter.hpp>


class AllegroFlare_Elements_AchievementsListTest : public ::testing::Test
{};

class AllegroFlare_Elements_AchievementsListTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/AchievementsList.hpp>


TEST_F(AllegroFlare_Elements_AchievementsListTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::AchievementsList achievements;
}


TEST_F(AllegroFlare_Elements_AchievementsListTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::AchievementsList achievements;
   std::string expected_error_message =
      "AchievementsList::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(achievements.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_AchievementsListTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::AchievementsList achievements(&get_font_bin_ref());
   achievements.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_AchievementsListTestWithAllegroRenderingFixture, CAPTURE__render__will_render_as_expected)
{
   AllegroFlare::Elements::AchievementsList achievements(&get_font_bin_ref());
   achievements.set_achievements(AllegroFlare::Elements::AchievementsList::build_placeholder_achievements());
   achievements.render();
   al_flip_display();
   sleep_for(1);
   SUCCEED();
}

TEST_F(AllegroFlare_Elements_AchievementsListTestWithAllegroRenderingFixture,
   CAPTURE__render__will_offset_the_list_of_items_by__scroll_offset_y)
{
   AllegroFlare::Elements::AchievementsList achievements(&get_font_bin_ref());
   achievements.set_achievements(AllegroFlare::Elements::AchievementsList::build_placeholder_achievements());

   int num_scrolls = 120;
   float amount_per_scroll = 2.6;
   for (int i=0; i<num_scrolls; i++)
   {
      achievements.set_scroll_offset_y(i * amount_per_scroll);

      clear();
      achievements.render();
      al_flip_display();
   }
}


TEST_F(AllegroFlare_Elements_AchievementsListTestWithAllegroRenderingFixture,
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
   //get_font_bin_ref().set_full_path("/Users/markoates/Repos/allegro_flare/bin/programs/data/fonts");
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject
   AllegroFlare::Elements::AchievementsList achievements_list(&get_font_bin_ref());
   achievements_list.set_achievements(AllegroFlare::Elements::AchievementsList::build_placeholder_achievements());

   // run the interactive test
   al_start_timer(primary_timer);
   while(!abort)
   {
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
         {
            switch(event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
               case ALLEGRO_KEY_PGUP:
                  achievements_list.move_scroll_offset_y(-20.0);
               break;

               case ALLEGRO_KEY_DOWN:
               case ALLEGRO_KEY_PGDN:
                  achievements_list.move_scroll_offset_y(20.0);
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            clear();
            achievements_list.render();
            al_flip_display();
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


