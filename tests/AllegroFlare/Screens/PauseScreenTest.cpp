
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

class AllegroFlare_Screens_PauseScreenTest : public ::testing::Test
{};

class AllegroFlare_Screens_PauseScreenTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Screens/PauseScreen.hpp>

#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <AllegroFlare/Elements/Backgrounds/Image.hpp>


TEST_F(AllegroFlare_Screens_PauseScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::PauseScreen pause_screen;
}


TEST_F(AllegroFlare_Screens_PauseScreenTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::PauseScreen pause_screen;
   std::string expected_error_message =
      "PauseScreen::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(pause_screen.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Screens_PauseScreenTest, render__without_primitives_addon_initialized__raises_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_PauseScreenTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Screens::PauseScreen pause_screen;
   pause_screen.set_font_bin(&get_font_bin_ref());
   pause_screen.set_bitmap_bin(&get_bitmap_bin_ref());

   pause_screen.render();

   al_flip_display();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_PauseScreenTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_with_a_title_bitmap_and_menu_selector_color)
{
   AllegroFlare::Screens::PauseScreen pause_screen;
   pause_screen.set_font_bin(&get_font_bin_ref());
   pause_screen.set_bitmap_bin(&get_bitmap_bin_ref());

   pause_screen.set_title_bitmap_name("paused_title-01.png");
   pause_screen.set_menu_selector_color(ALLEGRO_COLOR{0.906, 0.22, 0.573, 1.0});

   pause_screen.render();

   al_flip_display();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_PauseScreenTestWithAllegroRenderingFixture,
   select_menu_option__without_an_event_emitter__will_raise_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_PauseScreenTestWithAllegroRenderingFixture,
   select_menu_option__will_emit_a_game_event_with_the_current_selected_menu_options)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_PauseScreenTestWithAllegroRenderingFixture,
   on_activate__will_reset_the_cursor_to_the_top_of_the_menu)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_PauseScreenTestWithAllegroRenderingFixture,
   render__when_show_footer_text_is_true__will_render_the_footer_text)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_PauseScreenTestWithAllegroRenderingFixture,
   CAPTURE__render__when_show_footer_text_is_false__will_not_render_the_footer_text)
{
   AllegroFlare::Screens::PauseScreen pause_screen(nullptr, &get_font_bin_ref(), &get_bitmap_bin_ref());
   pause_screen.set_show_footer_text(false);

   pause_screen.render();

   al_flip_display();
}


TEST_F(AllegroFlare_Screens_PauseScreenTestWithAllegroRenderingFixture,
   CAPTURE__render__when_a_background_is_present__it_will_be_rendered)
{
   AllegroFlare::Elements::Backgrounds::Image image_identifier_background(
      &get_bitmap_bin_ref(),
      "deep-green-leaves-white-veins-960x540.jpg"
   );
   AllegroFlare::Screens::PauseScreen pause_screen(nullptr, &get_font_bin_ref(), &get_bitmap_bin_ref());
   pause_screen.set_background(&image_identifier_background);

   pause_screen.set_show_footer_text(false);

   pause_screen.render();

   al_flip_display();
}


TEST_F(AllegroFlare_Screens_PauseScreenTestWithAllegroRenderingFixture,
   DISABLED__INTERACTIVE__will_work_as_expected)
   // TODO: Upgrade this to TIMED_INTERACTIVE
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
   AllegroFlare::Screens::PauseScreen pause_screen;
   pause_screen.set_font_bin(&get_font_bin_ref());
   pause_screen.set_bitmap_bin(&get_bitmap_bin_ref());
   pause_screen.set_event_emitter(&event_emitter);

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
               pause_screen.virtual_control_button_down_func(nullptr, nullptr, button_num, event.keyboard.repeat);
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            pause_screen.primary_timer_func();
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


