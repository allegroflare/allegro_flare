

#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/Frameworks/Full.hpp>

#include <AllegroFlare/EventNames.hpp>


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


TEST(AllegroFlare_Frameworks_FullTest, DISABLED__emitting_an_ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT_will_cause_the_audio_to_play)
{
   AllegroFlare::Frameworks::Full framework;
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();

   framework.initialize();

   //event_emitter.emit_play_sound_effect_event("my-sound-identifier");

   //framework.run_loop();

   sleep(3);
}


