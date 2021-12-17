
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


