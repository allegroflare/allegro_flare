
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/AudioController.hpp>


TEST(AllegroFlare_AudioControllerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AudioController audio_controller;
}


TEST(AllegroFlare_AudioControllerTest, play_sound_effect_by_identifier__without_initialization__raises_an_exception)
{
   AllegroFlare::AudioController audio_controller;
   std::string expected_error_message =
      "AudioController::play_sound_effect_by_identifier: error: guard \"initialized\" not met";

   ASSERT_THROW_WITH_MESSAGE(
      audio_controller.play_sound_effect_by_identifier(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_AudioControllerTest, play_music_track_by_identifier__without_initialization__raises_an_exception)
{
   AllegroFlare::AudioController audio_controller;
   std::string expected_error_message =
      "AudioController::play_music_track_by_identifier: error: guard \"initialized\" not met";

   ASSERT_THROW_WITH_MESSAGE(
      audio_controller.play_music_track_by_identifier(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_AudioControllerTest, initialize__without_a_sample_bin__raises_an_exception)
{
   AllegroFlare::AudioController audio_controller;
   std::string expected_error_message =
      "AudioController::initialize: error: guard \"sample_bin\" not met";

   ASSERT_THROW_WITH_MESSAGE(audio_controller.initialize(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_AudioControllerTest, initialize__works__and_sets_initialized_to_true)
{
   AllegroFlare::SampleBin sample_bin;
   AllegroFlare::AudioController audio_controller(&sample_bin);

   audio_controller.initialize();

   ASSERT_EQ(true, audio_controller.get_initialized());
}


TEST(AllegroFlare_AudioControllerTest,
   play_music_track_by_identifier__when_a_music_track_identifier_is_not_present__outputs_a_message)
{
   al_init();
   al_install_audio();

   AllegroFlare::SampleBin sample_bin;
   AllegroFlare::AudioController audio_controller(&sample_bin);
   audio_controller.initialize();

   testing::internal::CaptureStdout();
   audio_controller.play_music_track_by_identifier("music-track-identifier-that-does-not-exist");
   std::string cout_message = testing::internal::GetCapturedStdout();

   std::string expected_cout_error_message = "[AudioController::find_music_track_by_identifier] error: " \
                                             "unable to find element with identifier " \
                                             "\"music-track-identifier-that-does-not-exist\"";
   ASSERT_EQ(expected_cout_error_message, cout_message);

   al_uninstall_system();
}


