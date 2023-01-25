

#include <gtest/gtest.h>

#include <AllegroFlare/Frameworks/Full.hpp>

#include <AllegroFlare/Elements/Notifications/AchievementUnlocked.hpp>
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
      if (ev->keyboard.keycode == ALLEGRO_KEY_N)
      {
         std::string achievement_name_to_emit = randomly_select_an_achievement_name();
         event_emitter->emit_post_unlocked_achievement_notification_event(achievement_name_to_emit);
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


class ScreenTestClass2 : public AllegroFlare::Screens::Base
{
private:
   AllegroFlare::BitmapBin *bitmap_bin;
   AllegroFlare::RenderSurfaces::Base *render_surface;
   //AllegroFlare::Shaders::Base *post_processing_shader;

public:
   ScreenTestClass2(
         AllegroFlare::BitmapBin *bitmap_bin,
         AllegroFlare::RenderSurfaces::Base *render_surface
         //AllegroFlare::Shaders::Base *post_processing_shader
      )
      : AllegroFlare::Screens::Base("ScreenTestClass2")
      , bitmap_bin(bitmap_bin)
      , render_surface(render_surface)
      //, post_processing_shader(post_processing_shader)
   {}
   virtual void on_activate() override {}
   virtual void primary_timer_func() override
   {
      ALLEGRO_BITMAP* bitmap = bitmap_bin->auto_get("toy-train-02.png");
      al_draw_bitmap(bitmap, 0, 0, 0);
   }
   virtual void key_down_func(ALLEGRO_EVENT *ev) override {}
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



TEST(AllegroFlare_Framewors_FullTest,
   //FOCUS__INTERACTIVE__in_an_AllegroFlare_Frameworks_Full_context__will_run_as_expected)
   DISABLED__INTERACTIVE__with_using_display_backbuffer_as_primary_render_surface_set_to_true__bitmap_surface_is_used)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.disable_using_display_backbuffer_as_primary_render_surface();
   framework.disable_fullscreen();
   framework.initialize();

   //AllegroFlare::RenderSurfaces::Base *primary_render_surface = framework.get_primary_render_surface();
   //std::cout << "DEBUG: current primary_render_surface type: " << primary_render_surface->get_type() << std::endl;
   //framework.get_bitmap_bin_ref().set_full_path(TEST_BASE_FOLDER "bitmaps/");

   ScreenTestClass2 screen(&framework.get_bitmap_bin_ref(), framework.get_primary_render_surface());
   framework.register_screen("screen", &screen);

   framework.activate_screen("screen");

   framework.run_loop();
   


   //primary_render_surface->set_as_target();
   ////AllegroFlare::Camera2D camera;
   ////camera.setup_dimentional_projection(primary_render_surface->obtain_surface());
   //al_clear_to_color(al_color_html("291d29"));


   //AllegroFlare::BitmapBin &bitmap_bin = framework.get_bitmap_bin_ref();
   //ALLEGRO_BITMAP* bitmap = bitmap_bin.auto_get("toy-train-02.png");

   //al_draw_bitmap(bitmap, 0, 0, 0);

   //al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
   ////#include <AllegroFlare/Shaders/PostProcessing/Blinds.hpp>

   //al_draw_bitmap(primary_render_surface->obtain_surface(), 0, 0, 0);
   //al_flip_display();
   //al_rest(1);


   ////al_draw_bitmap(
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
   framework.set_deployment_environment("test");
   framework.disable_fullscreen();
   framework.initialize();
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
   framework.set_deployment_environment("test");
   framework.disable_fullscreen();
   framework.initialize();
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


TEST(AllegroFlare_Framewors_FullTest, input_hints_text_opacity__has_the_expected_default_value)
{
   AllegroFlare::Frameworks::Full framework;
   EXPECT_EQ(0.4f, framework.get_input_hints_text_opacity());
}


TEST(AllegroFlare_Framewors_FullTest,
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


TEST(AllegroFlare_Framewors_FullTest,
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


TEST(AllegroFlare_Framewors_FullTest,
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


TEST(AllegroFlare_Frameworks_FullTest,
   DISABLED__emitting_an_ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT_will_cause_the_audio_to_play)
{
   AllegroFlare::Frameworks::Full framework;
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   framework.initialize(); // <-- TODO: consider running this test under "initialize_without_display()";

   //event_emitter.emit_play_sound_effect_event("my-sound-identifier");

   //framework.run_loop();

   //sleep(3);
}


TEST(AllegroFlare_Frameworks_FullTest,
   //FOCUS__INTERACTIVE__with_a_screen__will_work_as_expected)
   DISABLED__INTERACTIVE__will_work_as_expected)
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.set_deployment_environment("test");
   framework.initialize();

   ScreenTestClass screen_test_class(&framework.get_event_emitter_ref());

   framework.register_screen("screen_test_class", &screen_test_class);
   framework.activate_screen("screen_test_class");

   framework.run_loop();
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
   get_data_folder_path__when_in_test_mode__will_return_the_expected_path)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.initialize();

   EXPECT_EQ("./tests/fixtures/", framework.get_data_folder_path());
}


TEST(AllegroFlare_Frameworks_FullTest,
   get_data_folder_path__when_in_production_mode__will_return_the_expected_path)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("production");
   framework.initialize();

   EXPECT_EQ("./data/", framework.get_data_folder_path());
}


TEST(AllegroFlare_Frameworks_FullTest,
   get_data_folder_path__when_in_development_mode__will_return_the_expected_path)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("development");
   framework.initialize();

   EXPECT_EQ("./bin/programs/data/", framework.get_data_folder_path());
}


