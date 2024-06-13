
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>

class AllegroFlare_Screens_TitleScreenTest : public ::testing::Test
{};

class AllegroFlare_Screens_TitleScreenTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};

class AllegroFlare_Screens_TitleScreenTestWithAllegroFlareFrameworksFullFixture :
   public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{
   virtual void SetUp() override
   {
      // HERE:
      get_framework_ref().disable_using_display_backbuffer_as_primary_render_surface();
      AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::SetUp();
   }
};


#include <AllegroFlare/Screens/TitleScreen.hpp>

#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>


TEST_F(AllegroFlare_Screens_TitleScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::TitleScreen title_screen;
}


TEST_F(AllegroFlare_Screens_TitleScreenTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::TitleScreen title_screen;
   EXPECT_THROW_GUARD_ERROR(
      title_screen.render(),
      "AllegroFlare::Screens::TitleScreen::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Screens_TitleScreenTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Screens::TitleScreen title_screen;
   EXPECT_THROW_GUARD_ERROR(
      title_screen.render(),
      "AllegroFlare::Screens::TitleScreen::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_Screens_TitleScreenTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Screens::TitleScreen title_screen;
   title_screen.set_font_bin(&get_font_bin_ref());
   title_screen.set_bitmap_bin(&get_bitmap_bin_ref());

   title_screen.render();

   al_flip_display();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_TitleScreenTestWithAllegroRenderingFixture,
   CAPTURE__render__will_support_copyright_text_as_multiple_lines)
{
   AllegroFlare::Screens::TitleScreen title_screen;
   title_screen.set_font_bin(&get_font_bin_ref());
   title_screen.set_bitmap_bin(&get_bitmap_bin_ref());
   title_screen.set_copyright_text("Copyright 2022 - Gametastic Games\nALL RIGHTS RESERVED\nVersion 0.1alpha");

   title_screen.render();

   al_flip_display();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_TitleScreenTestWithAllegroRenderingFixture,
   DISABLED__select_menu_option__without_an_event_emitter__will_raise_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_TitleScreenTestWithAllegroRenderingFixture,
   DISABLED__select_menu_option__with_an_unrecognized_value_on_the_menu_option__will_raise_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_TitleScreenTestWithAllegroRenderingFixture,
   DISABLED__select_menu_option__will_emit_an_event_for_the_current_selected_menu_options)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_TitleScreenTestWithAllegroRenderingFixture,
   DISABLED__on_activate__will_reset_the_cursor_to_the_top_of_the_menu)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_TitleScreenTestWithAllegroRenderingFixture,
   DISABLED__infer_current_menu_option_value__will_reset_the_cursor_to_the_top_of_the_menu)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_TitleScreenTestWithAllegroRenderingFixture,
   TIMED_INTERACTIVE__will_work_as_expected)
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
   AllegroFlare::Screens::TitleScreen title_screen;
   title_screen.set_font_bin(&get_font_bin_ref());
   title_screen.set_bitmap_bin(&get_bitmap_bin_ref());
   title_screen.set_event_emitter(&event_emitter);

   // run the interactive test
   al_start_timer(primary_timer);

   // activate the screen (typically this is done by the framework)
   title_screen.on_activate();
   float duration_until_abort_sec = 3.0f;
   float interactive_started_at = al_get_time();
   bool abort_timer_in_effect = true;
   while(!abort)
   {
      if (abort_timer_in_effect && (al_get_time() - interactive_started_at) > duration_until_abort_sec) break;

      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
         {
            abort_timer_in_effect = false;
            int button_num = 0;
            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
               button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_UP;
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
               button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN;
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
               button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_A;
            if (button_num != 0)
               title_screen.virtual_control_button_down_func(nullptr, nullptr, button_num, event.keyboard.repeat);
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            title_screen.primary_timer_func();
            al_flip_display();
         break;

         case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
            std::cout << "Event emitted to play sound effect." << std::endl;
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


TEST_F(AllegroFlare_Screens_TitleScreenTestWithAllegroFlareFrameworksFullFixture,
   TIMED_INTERACTIVE__will_work_in_a_frameworks_full_context__with_a_non_display_backbuffer)
{
   AllegroFlare::Screens::TitleScreen title_screen;
   title_screen.set_event_emitter(get_framework_event_emitter());
   title_screen.set_font_bin(get_framework_font_bin());
   title_screen.set_bitmap_bin(get_framework_bitmap_bin());

   framework_register_and_activate_screen("title_screen", &title_screen);

   framework_run_loop(3);
}


TEST_F(AllegroFlare_Screens_TitleScreenTestWithAllegroFlareFrameworksFullFixture,
   TIMED_INTERACTIVE__will_work_in_a_frameworks_full_context__with_a_non_display_backbuffer_2)
{
   AllegroFlare::Screens::TitleScreen title_screen;
   title_screen.set_event_emitter(get_framework_event_emitter());
   title_screen.set_font_bin(get_framework_font_bin());
   title_screen.set_bitmap_bin(get_framework_bitmap_bin());

   framework_register_and_activate_screen("title_screen", &title_screen);

   framework_run_loop(3);
}


