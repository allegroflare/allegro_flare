
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Screens/GameWonScreen.hpp>

class AllegroFlare_Screens_GameWonScreenTest : public ::testing::Test
{};

class AllegroFlare_Screens_GameWonScreenTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};

#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>


TEST_F(AllegroFlare_Screens_GameWonScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::GameWonScreen game_won_screen;
}


TEST_F(AllegroFlare_Screens_GameWonScreenTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::GameWonScreen game_won_screen;
   EXPECT_THROW_GUARD_ERROR(
      game_won_screen.render(),
      "AllegroFlare::Screens::GameWonScreen::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Screens_GameWonScreenTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Screens::GameWonScreen game_won_screen;
   game_won_screen.set_font_bin(&get_font_bin_ref());

   game_won_screen.render();

   al_flip_display();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_GameWonScreenTestWithAllegroRenderingFixture,
   CAPTURE__render__with_customized_fonts_and_text__will_render_as_expected)
{
   AllegroFlare::Screens::GameWonScreen game_won_screen;
   game_won_screen.set_font_bin(&get_font_bin_ref());

   game_won_screen.set_title_text("You Have Already Won");
   game_won_screen.set_title_font_name("Lora-MediumItalic.ttf");
   game_won_screen.set_title_font_size(-74);
   game_won_screen.set_instruction_text("Press any key to continue");
   game_won_screen.set_instruction_font_name("Lora-Medium.ttf");
   game_won_screen.set_instruction_font_size(-34);

   game_won_screen.render();

   al_flip_display();
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
   DISABLED__background__when_set__will_render_as_expected)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_GameWonScreenTestWithAllegroRenderingFixture,
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
   AllegroFlare::Screens::GameWonScreen game_won_screen;
   game_won_screen.set_font_bin(&get_font_bin_ref());
   game_won_screen.set_event_emitter(&event_emitter);

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
               game_won_screen.virtual_control_button_down_func(nullptr, nullptr, button_num, event.keyboard.repeat);
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            game_won_screen.primary_timer_func();
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


