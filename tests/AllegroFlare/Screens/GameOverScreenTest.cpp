
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

class AllegroFlare_Screens_GameOverScreenTest : public ::testing::Test
{};

class AllegroFlare_Screens_GameOverScreenTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Screens/GameOverScreen.hpp>

#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>


TEST_F(AllegroFlare_Screens_GameOverScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::GameOverScreen game_over_screen;
}


TEST_F(AllegroFlare_Screens_GameOverScreenTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::GameOverScreen game_over_screen;
   std::string expected_error_message =
      "GameOverScreen::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(game_over_screen.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Screens_GameOverScreenTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Screens::GameOverScreen game_over_screen;
   game_over_screen.set_font_bin(&get_font_bin_ref());
   game_over_screen.initialize();

   game_over_screen.render();

   al_flip_display();
   //sleep_for(2);
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_GameOverScreenTestWithAllegroRenderingFixture,
   select_menu_option__without_an_event_emitter__will_raise_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_GameOverScreenTestWithAllegroRenderingFixture,
   select_menu_option__with_an_unrecognized_value_on_the_menu_option__will_raise_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_GameOverScreenTestWithAllegroRenderingFixture,
   select_menu_option__will_emit_an_event_for_the_current_selected_menu_options)
{
   // TODO
}



TEST_F(AllegroFlare_Screens_GameOverScreenTestWithAllegroRenderingFixture,
   DISABLED__INTERACTIVE__will_work_as_expected)
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
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject
   AllegroFlare::Screens::GameOverScreen game_over_screen;
   game_over_screen.set_font_bin(&get_font_bin_ref());
   game_over_screen.set_event_emitter(&event_emitter);
   game_over_screen.initialize();

   // run the interactive test
   al_start_timer(primary_timer);
   while(!abort)
   {
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
         {
            int button_num = 0;
            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
               button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_UP;
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
               button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN;
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
               button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_A;
            if (button_num != 0)
               game_over_screen.virtual_control_button_down_func(nullptr, nullptr, button_num, event.keyboard.repeat);
         }
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


