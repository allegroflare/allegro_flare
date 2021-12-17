
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/AudioController.hpp>

#include <allegro5/allegro_acodec.h>

#define TEST_FIXTURE_FOLDER_NAME "/Users/markoates/Repos/allegro_flare/test_fixtures/"



TEST(AllegroFlare_AudioControllerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AudioController audio_controller;
}


TEST(AllegroFlare_AudioControllerTest, initialized__without_allegro_initialized__raises_an_exception)
{
   AllegroFlare::AudioController audio_controller;
   std::string expected_error_message =
      "AudioController::initialize: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(audio_controller.initialize(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_AudioControllerTest, initialized__without_allegro_audio_initialized__raises_an_exception)
{
   al_init();

   AllegroFlare::AudioController audio_controller;
   std::string expected_error_message =
      "AudioController::initialize: error: guard \"al_is_audio_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(audio_controller.initialize(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}


TEST(AllegroFlare_AudioControllerTest, initialized__without_allegro_acodec_addon_initialized__raises_an_exception)
{
   al_init();
   al_install_audio();

   AllegroFlare::AudioController audio_controller;
   std::string expected_error_message =
      "AudioController::initialize: error: guard \"al_is_acodec_addon_initialized()\" not met";
   ASSERT_THROW_WITH_MESSAGE(audio_controller.initialize(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}


TEST(AllegroFlare_AudioControllerTest, play_sound_effect_by_identifier__without_initialization__raises_an_exception)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();

   AllegroFlare::AudioController audio_controller;
   std::string expected_error_message =
      "AudioController::play_sound_effect_by_identifier: error: guard \"initialized\" not met";

   ASSERT_THROW_WITH_MESSAGE(
      audio_controller.play_sound_effect_by_identifier(),
      std::runtime_error,
      expected_error_message
   );

   al_uninstall_system();
}


TEST(AllegroFlare_AudioControllerTest, play_music_track_by_identifier__without_initialization__raises_an_exception)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();

   AllegroFlare::AudioController audio_controller;
   std::string expected_error_message =
      "AudioController::play_music_track_by_identifier: error: guard \"initialized\" not met";

   ASSERT_THROW_WITH_MESSAGE(
      audio_controller.play_music_track_by_identifier(),
      std::runtime_error,
      expected_error_message
   );

   al_uninstall_system();
}


TEST(AllegroFlare_AudioControllerTest, initialize__without_a_sample_bin__raises_an_exception)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();

   AllegroFlare::AudioController audio_controller;
   std::string expected_error_message =
      "AudioController::initialize: error: guard \"sample_bin\" not met";

   ASSERT_THROW_WITH_MESSAGE(audio_controller.initialize(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}


TEST(AllegroFlare_AudioControllerTest, initialize__works__and_sets_initialized_to_true)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();

   AllegroFlare::SampleBin sample_bin;
   AllegroFlare::AudioController audio_controller(&sample_bin);

   audio_controller.initialize();

   ASSERT_EQ(true, audio_controller.get_initialized());

   al_uninstall_system();
}


TEST(AllegroFlare_AudioControllerTest,
   play_music_track_by_identifier__when_a_music_track_identifier_is_not_present__outputs_a_message)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();

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


TEST(AllegroFlare_AudioControllerTest, DISABLED__play_music_track_by_identifier__plays_the_audio_track)
{
   // test is incomplete
   al_init();
   al_install_audio();
   al_init_acodec_addon();

   AllegroFlare::SampleBin sample_bin;
   sample_bin.set_full_path(TEST_FIXTURE_FOLDER_NAME);
   std::string music_identifier = "music-1.wav";
   std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements;
   std::map<std::string, AllegroFlare::AudioRepositoryElement> music_track_elements = {
      { music_identifier, music_identifier },
   };
   AllegroFlare::AudioController audio_controller(&sample_bin, sound_effect_elements, music_track_elements);
   audio_controller.initialize();

   //audio_controller.play_music_track_by_identifier();

   al_uninstall_system();
}


