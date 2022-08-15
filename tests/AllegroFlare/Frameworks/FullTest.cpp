

#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#ifdef _WIN32
#define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/fonts/"
#else
#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"
#endif

#include <AllegroFlare/Frameworks/Full.hpp>

#include <AllegroFlare/EventNames.hpp>


#include <AllegroFlare/Screens/Base.hpp>
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
      };
      event_emitter->emit_set_input_hints_bar_event(tokens);
      event_emitter->emit_show_input_hints_bar_event();
   }
   virtual void primary_timer_func() override {}
   virtual void key_down_func(ALLEGRO_EVENT *ev) override
   {
      static int i=0; i++;
      std::vector<std::string> achievement_names = {
         "Win the game", "Finish the feature", "Save the day", "Take home the trophy", };
      std::string achievement_name_to_emit = achievement_names[i % achievement_names.size()];
      if (ev->keyboard.keycode == ALLEGRO_KEY_N)
         event_emitter->emit_post_unlocked_achievement_notification_event(achievement_name_to_emit);
   }
};


TEST(AllegroFlare_Framewors_FullTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Frameworks::Full framework;
}


TEST(AllegroFlare_Framewors_FullTest, initialize__will_initialize_allegro)
{
   AllegroFlare::Frameworks::Full framework;

   ASSERT_EQ(false, al_is_system_installed());
   framework.initialize();
   ASSERT_EQ(true, al_is_system_installed());
   framework.shutdown();
}


TEST(AllegroFlare_Framewors_FullTest, shutdown__will_uninitialize_allegro)
{
   AllegroFlare::Frameworks::Full framework;

   ASSERT_EQ(false, al_is_system_installed());
   framework.initialize();
   ASSERT_EQ(true, al_is_system_installed());
   framework.shutdown();
   ASSERT_EQ(false, al_is_system_installed());
}


TEST(AllegroFlare_Framewors_FullTest, ALLEGRO_FLARE_EVENT_EXIT_GAME__when_emitted__will_shutdown_the_program)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   event_emitter.emit_event(ALLEGRO_FLARE_EVENT_EXIT_GAME);
   framework.run_loop();

   SUCCEED();
}


TEST(AllegroFlare_Framewors_FullTest,
   ALLEGRO_FLARE_EVENT_SHOW_INPUT_HINTS_BAR__when_emitted__will_enable_drawing_input_hints)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();
   framework.get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   EXPECT_EQ(false, framework.get_drawing_inputs_bar_overlay());

   event_emitter.emit_show_input_hints_bar_event();
   framework.process_events_in_queue();

   EXPECT_EQ(true, framework.get_drawing_inputs_bar_overlay());
}


TEST(AllegroFlare_Framewors_FullTest,
   ALLEGRO_FLARE_EVENT_HIDE_INPUT_HINTS_BAR__when_emitted__will_disable_drawing_input_hints)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();
   framework.get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   framework.enable_drawing_inputs_bar_overlay();

   event_emitter.emit_hide_input_hints_bar_event();
   framework.process_events_in_queue();

   EXPECT_EQ(false, framework.get_drawing_inputs_bar_overlay());
}


TEST(AllegroFlare_Framewors_FullTest,
   ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR__when_emitted__will_set_the_tokens_for_the_input_hints)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();
   framework.get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   std::vector<std::string> tokens = { "ENTER", "%SPACE", "LABEL>>", "Do the thing" };

   event_emitter.emit_set_input_hints_bar_event(tokens);
   framework.process_events_in_queue();

   std::vector<std::string> actual_tokens = framework.get_input_hints_tokens();
   EXPECT_EQ(tokens, actual_tokens);
}


TEST(AllegroFlare_Framewors_FullTest, input_hints_text_opacity__has_the_expected_default_value)
{
   AllegroFlare::Frameworks::Full framework;
   EXPECT_EQ(0.4f, framework.get_input_hints_text_opacity());
}


TEST(AllegroFlare_Framewors_FullTest,
   ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR_OPACITY__when_emitted__will_set_the_opacity_for_the_input_hints_text)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();
   framework.get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   float opacity = 0.618033;

   event_emitter.emit_set_input_hints_bar_opacity_event(opacity);
   framework.process_events_in_queue();

   float actual_opacity = framework.get_input_hints_text_opacity();
   EXPECT_EQ(opacity, actual_opacity);
}


TEST(AllegroFlare_Framewors_FullTest,
   DISABLED__ALLEGRO_FLARE_EVENT_POST_ACHIEVEMENT_UNLOCKED_NOTIFICATION__when_emitted__will_append_a_new_notification)
   // TODO: update this test
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();
   AllegroFlare::Notifications &notifications = framework.get_notifications_ref();

   event_emitter.emit_event(ALLEGRO_FLARE_EVENT_POST_ACHIEVEMENT_UNLOCKED_NOTIFICATION);
   framework.process_events_in_queue();

   EXPECT_EQ(1, notifications.size());
}


TEST(AllegroFlare_Frameworks_FullTest, initialize__will_initialize_the_audio_controller)
{
   AllegroFlare::Frameworks::Full framework;
   AllegroFlare::AudioController &audio_controller = framework.get_audio_controller_ref();
   ASSERT_EQ(false, audio_controller.get_initialized());

   framework.initialize();

   ASSERT_EQ(true, audio_controller.get_initialized());
}


TEST(AllegroFlare_Frameworks_FullTest, initialize__will_create_a_display_with_the_expected_dimentions)
{
   AllegroFlare::Frameworks::Full framework;

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


TEST(AllegroFlare_Frameworks_FullTest, DISABLED__emitting_an_ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT_will_cause_the_audio_to_play)
{
   AllegroFlare::Frameworks::Full framework;
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   framework.initialize();

   //event_emitter.emit_play_sound_effect_event("my-sound-identifier");

   //framework.run_loop();

   //sleep(3);
}


TEST(AllegroFlare_Frameworks_FullTest, DISABLED__INTERACTIVE__will_work_as_expected)
{
   AllegroFlare::Frameworks::Full framework;
   ScreenTestClass screen_test_class(&framework.get_event_emitter_ref());

   framework.initialize();
   framework.get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER); // NOTE: have to set path after init (for now)
   framework.get_bitmap_bin_ref().set_full_path(TEST_FIXTURE_BITMAP_FOLDER); // NOTE: have to set path after init (for now)

   framework.register_screen("screen_test_class", &screen_test_class);
   framework.activate_screen("screen_test_class");

   framework.run_loop();
}


