
#include <gtest/gtest.h>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Screens_AchievementsTest : public ::testing::Test
{};

class AllegroFlare_Screens_AchievementsTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};

#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Achievements.hpp>
#include <AllegroFlare/VirtualControls.hpp>


#include <AllegroFlare/Screens/Achievements.hpp>


TEST_F(AllegroFlare_Screens_AchievementsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Achievements achievements_screen;
}


TEST_F(AllegroFlare_Screens_AchievementsTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::Achievements achievements_screen;
   std::string expected_thrown_error_message =
      "Achievements::initialize: error: guard \"al_is_system_installed()\" not met";

   testing::internal::CaptureStdout();
   testing::internal::CaptureStderr();

   ASSERT_THROW_WITH_MESSAGE(achievements_screen.initialize(), std::runtime_error, expected_thrown_error_message);

   std::string actual_cout_output = testing::internal::GetCapturedStdout();
   std::string actual_cerr_output = testing::internal::GetCapturedStderr();

   std::string expected_cerr_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Achievements::initialize", "al_is_system_installed()");
   std::string expected_cerr_output = expected_cerr_error_message;

   // TODO: replace below with something like "EXPECT_THAT(expected_cout_output.empty(), ::testing::IsEmpty());"
   EXPECT_EQ(true, actual_cout_output.empty());
   EXPECT_EQ(actual_cerr_output, expected_cerr_output);
}


TEST_F(AllegroFlare_Screens_AchievementsTest, DISABLED__initialize__without_font_addon_initialized__raises_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_AchievementsTest, DISABLED__initialize__without_a_font_bin__raises_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_AchievementsTest, DISABLED__initialize__without_an_event_emitter__raises_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_AchievementsTest, DISABLED__initialize__without_an_achievements__raises_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_AchievementsTest,
   DISABLED__after_initialization__setting_the_event_emitter_will_raise_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_AchievementsTest,
   DISABLED__on_activate__when_the_scrollbar_will_be_showing__sets_the_input_hints_to_include_scrollbar_control_hints)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_AchievementsTest,
   DISABLED__on_activate__when_the_scrollbar_will_not_be_showing__sets_the_input_hints_without_scrollbar_control_hints)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_AchievementsTestWithAllegroRenderingFixture,
   primary_timer_func__before_initialization__will_raise_an_exception)
{
   AllegroFlare::Screens::Achievements achievements_screen;
   std::string expected_thrown_error_message =
      "Achievements::primary_timer_func: error: guard \"initialized\" not met";

   testing::internal::CaptureStdout();
   testing::internal::CaptureStderr();

   ASSERT_THROW_WITH_MESSAGE(achievements_screen.primary_timer_func(), std::runtime_error, expected_thrown_error_message);

   std::string actual_cout_output = testing::internal::GetCapturedStdout();
   std::string actual_cerr_output = testing::internal::GetCapturedStderr();

   std::string expected_cerr_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Achievements::primary_timer_func", "initialized");
   std::string expected_cerr_output = expected_cerr_error_message;

   // TODO: replace below with something like "EXPECT_THAT(expected_cout_output.empty(), ::testing::IsEmpty());"
   EXPECT_EQ(true, actual_cout_output.empty()) << actual_cout_output;
   EXPECT_EQ(actual_cerr_output, expected_cerr_output) << actual_cerr_output;
}


TEST_F(AllegroFlare_Screens_AchievementsTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Achievements achievements;
   AllegroFlare::Screens::Achievements achievements_screen(&get_font_bin_ref(), &event_emitter, &achievements);
   achievements_screen.initialize();
   achievements_screen.render();
}


TEST_F(AllegroFlare_Screens_AchievementsTestWithAllegroRenderingFixture,
   refresh_achievements_list__will_refresh_the_list_from_the_source_achievements)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Achievements achievements;
   AllegroFlare::Screens::Achievements achievements_screen(&get_font_bin_ref(), &event_emitter, &achievements);
   achievements_screen.initialize();

   EXPECT_EQ(0, achievements_screen.get_achievements_list_ref().get_achievements().size());
   achievements.set_achievements({
      { "win_the_day",
         new AllegroFlare::Achievement("Win the Day", "Accomplish the task you set out to do"),
         false,
         false,
      },
      { "add_several_achievements",
         new AllegroFlare::Achievement("And Another One", "Add another achievement to the test data"),
         false,
         false
      },
   });
   achievements_screen.refresh_achievements_list();
   EXPECT_EQ(2, achievements_screen.get_achievements_list_ref().get_achievements().size());
}


TEST_F(AllegroFlare_Screens_AchievementsTestWithAllegroRenderingFixture,
   //INTERACTIVE__will_work_as_expected)
   DISABLED__INTERACTIVE__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // setup environment
   AllegroFlare::Achievements achievements;
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // Add some test data achievements
   achievements.set_achievements({
      { "win_the_day",
         new AllegroFlare::Achievement("Win the Day", "Accomplish the task you set out to do"),
         false,
         false,
      },
      { "add_several_achievements",
         new AllegroFlare::Achievement("And Another One", "Add another achievement to the test data"),
         false,
         false
      },
   });

   // initialize test subject
   AllegroFlare::Screens::Achievements achievements_screen;
   achievements_screen.set_achievements(&achievements);
   achievements_screen.set_font_bin(&get_font_bin_ref());
   achievements_screen.set_event_emitter(&event_emitter);
   achievements_screen.initialize();

   // run the interactive test
   al_start_timer(primary_timer);
   achievements_screen.on_activate();
   while(!abort)
   {
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
         {
            int button_num = 0;
            if (event.keyboard.keycode == ALLEGRO_KEY_UP) button_num = AllegroFlare::VirtualControls::BUTTON_UP;
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) button_num = AllegroFlare::VirtualControls::BUTTON_DOWN;
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) button_num = AllegroFlare::VirtualControls::BUTTON_A;
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) abort = true;

            if (button_num != 0) achievements_screen.virtual_control_button_down_func(0, button_num, event.keyboard.repeat);
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            achievements_screen.primary_timer_func();
            al_flip_display();
         break;

         case ALLEGRO_FLARE_EVENT_GAME_EVENT:
            abort = true;
         break;
      }
   }

   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.
   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}


