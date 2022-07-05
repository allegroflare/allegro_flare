
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

class AllegroFlare_Screens_GameWonScreenTest : public ::testing::Test
{};

class AllegroFlare_Screens_GameWonScreenTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Screens/GameWonScreen.hpp>

#include <AllegroFlare/EventNames.hpp>


TEST_F(AllegroFlare_Screens_GameWonScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::GameWonScreen game_over_screen;
}


TEST_F(AllegroFlare_Screens_GameWonScreenTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::GameWonScreen game_over_screen;
   std::string expected_error_message =
      "GameWonScreen::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(game_over_screen.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Screens_GameWonScreenTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   //get_font_bin_ref().set_full_path("/Users/markoates/Repos/Wicked/bin/programs/data/fonts");

   AllegroFlare::Screens::GameWonScreen game_over_screen;
   game_over_screen.set_font_bin(&get_font_bin_ref());

   game_over_screen.render();

   al_flip_display();
   //sleep_for(2);
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_GameWonScreenTestWithAllegroRenderingFixture,
   select_menu_option__without_an_event_emitter__will_raise_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_GameWonScreenTestWithAllegroRenderingFixture,
   select_menu_option__with_an_unrecognized_value_on_the_menu_option__will_raise_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_GameWonScreenTestWithAllegroRenderingFixture,
   select_menu_option__will_emit_an_event_for_the_current_selected_menu_options)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_GameWonScreenTestWithAllegroRenderingFixture,
   INTERACTIVE__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   //al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // setup environment
   //get_font_bin_ref().set_full_path("/Users/markoates/Repos/Wicked/bin/programs/data/fonts");
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject
   AllegroFlare::Screens::GameWonScreen game_over_screen;
   game_over_screen.set_font_bin(&get_font_bin_ref());
   game_over_screen.set_event_emitter(&event_emitter);

   // run the interactive test
   al_start_timer(primary_timer);
   while(!abort)
   {
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
            game_over_screen.key_char_func(&event);
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            game_over_screen.primary_timer_func();
            al_flip_display();
         break;

         case ALLEGRO_FLARE_EVENT_GAME_EVENT:
            abort = true;
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


