

#include <gtest/gtest.h>

#include <AllegroFlare/Frameworks/Full.hpp>

#include <AllegroFlare/Elements/Notifications/AchievementUnlocked.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Routers/Standard.hpp>



class ScreenTestClass : public AllegroFlare::Screens::Base
{
private:
   AllegroFlare::EventEmitter *event_emitter;
public:
   ScreenTestClass(AllegroFlare::EventEmitter *event_emitter)
      : AllegroFlare::Screens::Base("ScreenTestClass")
      , event_emitter(event_emitter)
   {}
   virtual void on_activate() override
   {
      std::vector<std::string> tokens = {
         "ESC", "%SPACER", "LABEL>>", "Exit test",
         "%SEPARATOR",
         "N", "%SPACER", "LABEL>>", "Post a notification"
         //"%SEPARATOR",
         //"F", "%SPACER", "LABEL>>", "Toggle fullscreen"
      };
      event_emitter->emit_set_input_hints_bar_event(tokens);
      event_emitter->emit_show_input_hints_bar_event();
   }
   virtual void primary_timer_func() override {}
   virtual void key_down_func(ALLEGRO_EVENT *ev) override
   {
      if (ev->keyboard.keycode == ALLEGRO_KEY_N)
      {
         std::string achievement_name_to_emit = randomly_select_an_achievement_name();
         event_emitter->emit_post_unlocked_achievement_notification_event(achievement_name_to_emit);
      }
      //else if (ev->keyboard.keycode == ALLEGRO_KEY_F)
      //{
         //event_emitter->emit_event_to_toggle_fullscreen();
      //}
   }
   std::string randomly_select_an_achievement_name()
   {
      static int i=0; i++;
      std::vector<std::string> achievement_names = {
         "Win the game", "Finish the feature", "Save the day", "Take home the trophy", };
      return achievement_names[i % achievement_names.size()];
   }
};


class ScreenTestClass2 : public AllegroFlare::Screens::Base
{
private:
   AllegroFlare::BitmapBin *bitmap_bin;
   AllegroFlare::RenderSurfaces::Base *render_surface;
   //AllegroFlare::Shaders::Base *post_processing_shader;
   int choo_choo_coordinate;

public:
   ScreenTestClass2(
         AllegroFlare::BitmapBin *bitmap_bin,
         AllegroFlare::RenderSurfaces::Base *render_surface
         //AllegroFlare::Shaders::Base *post_processing_shader
      )
      : AllegroFlare::Screens::Base("ScreenTestClass2")
      , bitmap_bin(bitmap_bin)
      , render_surface(render_surface)
      , choo_choo_coordinate(0)
      //, post_processing_shader(post_processing_shader)
   {}
   virtual void on_activate() override {}
   virtual void primary_timer_func() override
   {
      ALLEGRO_BITMAP* bitmap = bitmap_bin->auto_get("toy-train-02.png");
      al_draw_bitmap(bitmap, choo_choo_coordinate*2, choo_choo_coordinate, 0);
      choo_choo_coordinate++;
   }
   virtual void key_down_func(ALLEGRO_EVENT *ev) override {}
};


class ScreenTestClass3 : public AllegroFlare::Screens::Base
{
private:
   AllegroFlare::EventEmitter *event_emitter;
public:
   ScreenTestClass3(AllegroFlare::EventEmitter *event_emitter)
      : AllegroFlare::Screens::Base("ScreenTestClass3")
      , event_emitter(event_emitter)
   {}
   virtual void on_activate() override
   {
      std::vector<std::string> tokens = {
         "ESC", "%SPACER", "LABEL>>", "Exit test",
         "%SEPARATOR",
         "N", "%SPACER", "LABEL>>", "Post a notification",
         "%SEPARATOR",
         "1", "%SPACER", "LABEL>>", "1920x1080",
         "%SEPARATOR",
         "2", "%SPACER", "LABEL>>", "1080x1920",
         "%SEPARATOR",
         "3", "%SPACER", "LABEL>>", "2520x1080",
         "%SEPARATOR",
         "F", "%SPACER", "LABEL>>", "Toggle fullscreen"
      };
      event_emitter->emit_set_input_hints_bar_event(tokens);
      event_emitter->emit_show_input_hints_bar_event();
   }
   virtual void primary_timer_func() override {}
   virtual void key_down_func(ALLEGRO_EVENT *ev) override
   {
      if (ev->keyboard.keycode == ALLEGRO_KEY_N)
      {
         std::string achievement_name_to_emit = randomly_select_an_achievement_name();
         event_emitter->emit_post_unlocked_achievement_notification_event(achievement_name_to_emit);
      }
      else if (ev->keyboard.keycode == ALLEGRO_KEY_1)
      {
         event_emitter->emit_event_to_set_display_size(1920, 1080);
      }
      else if (ev->keyboard.keycode == ALLEGRO_KEY_2)
      {
         event_emitter->emit_event_to_set_display_size(1080, 1920);
      }
      else if (ev->keyboard.keycode == ALLEGRO_KEY_3)
      {
         event_emitter->emit_event_to_set_display_size(2520, 1080);
      }
      else if (ev->keyboard.keycode == ALLEGRO_KEY_F)
      {
         event_emitter->emit_event_to_toggle_fullscreen();
      }
   }
   std::string randomly_select_an_achievement_name()
   {
      static int i=0; i++;
      std::vector<std::string> achievement_names = {
         "Win the game", "Finish the feature", "Save the day", "Take home the trophy", };
      return achievement_names[i % achievement_names.size()];
   }
};


TEST(AllegroFlare_Frameworks_FullTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Frameworks::Full framework;
}


TEST(AllegroFlare_Frameworks_FullTest, DEFAULT_DISPLAY_WIDTH__has_the_expected_value)
{
   EXPECT_EQ(1920, AllegroFlare::Frameworks::Full::DEFAULT_DISPLAY_WIDTH);
}


TEST(AllegroFlare_Frameworks_FullTest, DEFAULT_DISPLAY_HEIGHT__has_the_expected_value)
{
   EXPECT_EQ(1080, AllegroFlare::Frameworks::Full::DEFAULT_DISPLAY_HEIGHT);
}


TEST(AllegroFlare_Frameworks_FullTest, DEFAULT_CONFIG_FILENAME__has_the_expected_value)
{
   EXPECT_EQ("data/config/config.cfg", AllegroFlare::Frameworks::Full::DEFAULT_CONFIG_FILENAME);
}


TEST(AllegroFlare_Frameworks_FullTest, initialize__will_initialize_allegro)
{
   AllegroFlare::Frameworks::Full framework;

   ASSERT_EQ(false, al_is_system_installed());
   framework.initialize();
   ASSERT_EQ(true, al_is_system_installed());
   framework.shutdown();
}


TEST(AllegroFlare_Frameworks_FullTest, shutdown__will_uninitialize_allegro)
{
   AllegroFlare::Frameworks::Full framework;

   ASSERT_EQ(false, al_is_system_installed());
   framework.initialize();
   ASSERT_EQ(true, al_is_system_installed());
   framework.shutdown();
   ASSERT_EQ(false, al_is_system_installed());
}


TEST(AllegroFlare_Frameworks_FullTest, router__is_nullptr_by_default)
{
   AllegroFlare::Frameworks::Full framework;
   EXPECT_EQ(nullptr, framework.get_router());
}


TEST(AllegroFlare_Frameworks_FullTest,
   initialize__when_display_backbuffer_as_primary_render_surface_set_to_false__will_produce_a_bitmap_\
primary_render_surface)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.disable_fullscreen();
   framework.disable_using_display_backbuffer_as_primary_render_surface();
   framework.initialize();

   AllegroFlare::RenderSurfaces::Base *primary_render_surface = framework.get_primary_render_surface();

   EXPECT_EQ(true, primary_render_surface->is_type(AllegroFlare::RenderSurfaces::Bitmap::TYPE));
}


TEST(AllegroFlare_Frameworks_FullTest,
   run_loop__when_a_non_display_primary_render_surface_is_in_use__will_render_the_surface_to_the_display)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.disable_fullscreen();
   framework.disable_using_display_backbuffer_as_primary_render_surface();
   framework.initialize();

   AllegroFlare::RenderSurfaces::Base *primary_render_surface = framework.get_primary_render_surface();
   ASSERT_EQ(false, primary_render_surface->is_a_display_surface());

   ScreenTestClass2 screen_test_class(&framework.get_bitmap_bin_ref(), primary_render_surface);
   framework.register_and_activate_screen("screen_test_class", &screen_test_class);

   framework.run_loop(3);
   // TODO: Capture
}


TEST(AllegroFlare_Frameworks_FullTest, ALLEGRO_FLARE_EVENT_EXIT_GAME__when_emitted__will_shutdown_the_program)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   event_emitter.emit_event(ALLEGRO_FLARE_EVENT_EXIT_GAME);
   framework.run_loop();

   SUCCEED();
}


TEST(AllegroFlare_Frameworks_FullTest,
   ALLEGRO_FLARE_EVENT_SHOW_INPUT_HINTS_BAR__when_emitted__will_enable_drawing_input_hints)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.disable_fullscreen();
   framework.initialize();
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   EXPECT_EQ(false, framework.get_drawing_inputs_bar_overlay());

   event_emitter.emit_show_input_hints_bar_event();
   framework.process_events_in_queue();

   EXPECT_EQ(true, framework.get_drawing_inputs_bar_overlay());
}


TEST(AllegroFlare_Frameworks_FullTest,
   ALLEGRO_FLARE_EVENT_HIDE_INPUT_HINTS_BAR__when_emitted__will_disable_drawing_input_hints)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.disable_fullscreen();
   framework.initialize();
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   framework.enable_drawing_inputs_bar_overlay();

   event_emitter.emit_hide_input_hints_bar_event();
   framework.process_events_in_queue();

   EXPECT_EQ(false, framework.get_drawing_inputs_bar_overlay());
}


TEST(AllegroFlare_Frameworks_FullTest,
   ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR__when_emitted__will_set_the_tokens_for_the_input_hints)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.disable_fullscreen();
   framework.initialize();
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   std::vector<std::string> tokens = { "ENTER", "%SPACE", "LABEL>>", "Do the thing" };

   event_emitter.emit_set_input_hints_bar_event(tokens);
   framework.process_events_in_queue();

   std::vector<std::string> actual_tokens = framework.get_input_hints_tokens();
   EXPECT_EQ(tokens, actual_tokens);
}


TEST(AllegroFlare_Frameworks_FullTest, input_hints_text_opacity__has_the_expected_default_value)
{
   AllegroFlare::Frameworks::Full framework;
   EXPECT_EQ(0.4f, framework.get_input_hints_text_opacity());
}


TEST(AllegroFlare_Frameworks_FullTest,
   ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR_TEXT_OPACITY__when_emitted__will_set_the_opacity_for_the_input_hints_text)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.disable_fullscreen();
   framework.initialize();
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   float opacity = 0.618033;

   event_emitter.emit_set_input_hints_bar_text_opacity_event(opacity);
   framework.process_events_in_queue();

   float actual_opacity = framework.get_input_hints_text_opacity();
   EXPECT_EQ(opacity, actual_opacity);
}


TEST(AllegroFlare_Frameworks_FullTest,
   ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR_BACKFILL_OPACITY__when_emitted__will_set_the_backfill_opacity_for_the\
_input_hints_bar)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.disable_fullscreen();
   framework.initialize();
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   float opacity = 0.618033;

   event_emitter.emit_set_input_hints_bar_backfill_opacity_event(opacity);
   framework.process_events_in_queue();

   float actual_opacity = framework.get_input_hints_backfill_opacity();
   EXPECT_EQ(opacity, actual_opacity);
}


TEST(AllegroFlare_Frameworks_FullTest,
   when_emitting_an_unlocked_achievement_notification_event__a_notification_will_be_added_with_the_expected_value)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();
   AllegroFlare::Notifications &notifications = framework.get_notifications_ref();

   std::string achievement_name_to_emit = "Unlock an achievement notification";
   event_emitter.emit_post_unlocked_achievement_notification_event(achievement_name_to_emit);
   framework.process_events_in_queue();

   ASSERT_EQ(1, notifications.size());
   ASSERT_NE(nullptr, notifications.get_notifications()[0]);
   ASSERT_EQ("AchievementUnlocked", notifications.get_notifications()[0]->get_type());

   AllegroFlare::Elements::Notifications::AchievementUnlocked *achievement_notification =
      static_cast<AllegroFlare::Elements::Notifications::AchievementUnlocked*>(
         notifications.get_notifications()[0]);

   EXPECT_EQ(achievement_name_to_emit, achievement_notification->get_name());
}


TEST(AllegroFlare_Frameworks_FullTest, initialize__will_initialize_the_audio_controller)
{
   AllegroFlare::Frameworks::Full framework;
   AllegroFlare::AudioController &audio_controller = framework.get_audio_controller_ref();
   ASSERT_EQ(false, audio_controller.get_initialized());

   framework.initialize();

   ASSERT_EQ(true, audio_controller.get_initialized());
}


TEST(AllegroFlare_Frameworks_FullTest, initialize__will_create_a_display_with_the_expected_dimensions)
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.set_deployment_environment("test");
   framework.initialize();

   ALLEGRO_DISPLAY *current_al_display = al_get_current_display();
   ASSERT_NE(nullptr, current_al_display);

   AllegroFlare::Display *primary_framework_display = framework.get_primary_display();
   ASSERT_NE(nullptr, primary_framework_display);

   EXPECT_EQ(current_al_display, primary_framework_display->al_display);
   EXPECT_EQ(1920, primary_framework_display->get_width());
   EXPECT_EQ(1080, primary_framework_display->get_height());
}


TEST(AllegroFlare_Frameworks_FullTest,
   run_loop__will_start_with_emitting_an_ALLEGRO_FLARE_EVENT_GAME_EVENT_with_the_name_parameter_value_of_initialize)
{
   // TODO
}


TEST(AllegroFlare_Frameworks_FullTest,
   run_loop__will_send_ALLEGRO_EVENT_MOUSE_BUTTON_DOWN_events_to_the_screen_manager)
{
   // TODO

   // TODO also for:
   //   case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
   //   case ALLEGRO_EVENT_MOUSE_WARPED:
   //   case ALLEGRO_EVENT_MOUSE_AXES:
}


TEST(AllegroFlare_Frameworks_FullTest,
   when_no_screens_are_registered__will_display_an_empty_state_message)
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.set_deployment_environment("test");

   framework.initialize();

   framework.run_loop(3);
   // TODO: find some way to test for the displayed empty state message
   // TODO: capture this test. Note the display is destroyed when "run_loop" exits
}


TEST(AllegroFlare_Frameworks_FullTest,
   DISABLED__ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT__when_emitter__will_cause_the_audio_to_play)
   // TODO: Fix this crashing test, needs for all sound-effect and music fixture files to be moved
   // to the correct directory under fixtures/sounds which means updating all the other locations
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.set_deployment_environment("test");
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   framework.initialize(); // <-- TODO: consider running this test under "initialize_without_display()";

   event_emitter.emit_play_sound_effect_event("pickup_health-01.ogg");

   framework.run_loop(3); // TODO: add autoshutdown time to several tests
   // TODO: find some way to test for a played sound effect
}


TEST(AllegroFlare_Frameworks_FullTest, INTERACTIVE__with_a_screen__will_work_as_expected)
   // TODO: consider removing this test (is it redundant?)
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.set_deployment_environment("test");
   framework.initialize();

   ScreenTestClass screen_test_class(&framework.get_event_emitter_ref());

   framework.register_and_activate_screen("screen_test_class", &screen_test_class);

   framework.run_loop(3);
}


TEST(AllegroFlare_Frameworks_FullTest,
   disable_fullscreen__will_cause_initialize_to_not_create_the_display_in_fullscreen_mode)
{
   // TODO
}


TEST(AllegroFlare_Frameworks_FullTest,
   initialize__will_create_a_fullscreen_display)
{
   // TODO
}


TEST(AllegroFlare_Frameworks_FullTest,
   initialize__without_a_development_environment_set__will_output_a_warning_message)
{
   // TODO
}


TEST(AllegroFlare_Frameworks_FullTest,
   initialize__without_a_development_environment_set__will_default_to_ENVIRONMENT_DEVELOPMENT)
{
   // TODO
}


TEST(AllegroFlare_Frameworks_FullTest,
   destroy__will_restore_the_initial_working_directory_to_what_it_was_before_being_initializing)
{
   // TODO
}


TEST(AllegroFlare_Frameworks_FullTest,
   screen_fit_mode__when_set_to_scale_to_fit_width_or_height__will_render_horizontal_black_bars_when_the_width_is_greater)
{
   // TODO
}


TEST(AllegroFlare_Frameworks_FullTest,
   screen_fit_mode__when_set_to_scale_to_fit_width_or_height__will_render_vertical_black_bars_when_the_height_is_greater)
{
   // TODO
}


TEST(AllegroFlare_Frameworks_FullTest,
   get_data_folder_path__when_in_test_mode__will_return_the_expected_path)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.initialize();

   EXPECT_EQ("tests/fixtures/", framework.get_data_folder_path());
}


TEST(AllegroFlare_Frameworks_FullTest,
   get_data_folder_path__when_in_production_mode__will_return_the_expected_path)
{
   // NOTE: This test fails due to missing icon file when creating the display on initialize
   // TODO: Consider alternative technique
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("production");
   //framework.initialize();

   EXPECT_EQ("data/", framework.get_data_folder_path());
}


TEST(AllegroFlare_Frameworks_FullTest,
   get_data_folder_path__when_in_demo_mode__will_return_the_expected_path)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("demo");
   framework.initialize();

   EXPECT_EQ("bin/data/", framework.get_data_folder_path());
}


TEST(AllegroFlare_Frameworks_FullTest,
   get_data_folder_path__when_in_development_mode__will_return_the_expected_path)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("development");
   framework.initialize();

   EXPECT_EQ("bin/data/", framework.get_data_folder_path());
}


TEST(AllegroFlare_Frameworks_FullTest,
   initialize__when_a_config_file_value_for_fullscreen_is_set_to_false__will_create_the_display_in_windowed_mode)
{
   static const char* CONFIG_FILENAME = "config/non_fullscreen_display_config.cfg";
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   std::string config_filename_with_fullscreen_false = framework.get_data_folder_path() + CONFIG_FILENAME;
   framework.get_config().set_filename(config_filename_with_fullscreen_false);
   framework.initialize();

   AllegroFlare::Display *framework_display = framework.get_primary_display();
   ASSERT_NE(nullptr, framework_display);

   EXPECT_EQ(2880, framework_display->get_width());
   EXPECT_EQ(1620, framework_display->get_height());
}


TEST(AllegroFlare_Frameworks_FullTest,
   initialize__when_a_config_file_value_for_width_and_height_are_present__will_create_the_display_with_the_expected_\
dimensions)
{
   static const char* CONFIG_FILENAME = "config/non_fullscreen_display_config.cfg";
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   std::string config_filename_with_fullscreen_false = framework.get_data_folder_path() + CONFIG_FILENAME;
   framework.get_config().set_filename(config_filename_with_fullscreen_false);
   framework.initialize();

   AllegroFlare::Display *framework_display = framework.get_primary_display();
   ASSERT_NE(nullptr, framework_display);

   EXPECT_EQ(2880, framework_display->get_width());
   EXPECT_EQ(1620, framework_display->get_height());
}


TEST(AllegroFlare_Frameworks_FullTest, set_disply_to_fullscreen__will_toggle_the_display_to_be_fullscreen)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.disable_fullscreen();
   framework.initialize();

   framework.set_display_to_fullscreen(); // TODO: Do not call this directly, emit an event instead

   // TODO: Confirm fullscreen with assertion
}


TEST(AllegroFlare_Frameworks_FullTest, set_disply_to_windowed__will_toggle_the_display_to_windowed)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.initialize();

   framework.set_display_to_windowed(); // TODO: Do not call this directly, emit an event instead

   // TODO: Confirm windowed with assertion
}


TEST(AllegroFlare_Frameworks_FullTest,
   FOCUS__INTERACTIVE__will_toggle_the_display_between_windowed_and_fullscreen)
{
   AllegroFlare::Frameworks::Full framework;
   //framework.disable_fullscreen();
   framework.set_deployment_environment("test");
   framework.initialize();

   ScreenTestClass3 screen_test_class(&framework.get_event_emitter_ref());

   framework.register_and_activate_screen("screen_test_class", &screen_test_class);

   framework.run_loop(6);
}


