
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/AudioController.hpp>

#include <allegro5/allegro_acodec.h>

#define TEST_FIXTURE_FOLDER_NAME "/Users/markoates/Repos/allegro_flare/tests/test_fixtures/"

// for usleep on Windows
#include <unistd.h>


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


TEST(AllegroFlare_AudioControllerTest,
   DISABLED__initialized__without_allegro_acodec_addon_initialized__raises_an_exception)
   // this test works, but is disabled due to a leaky condition with Allegro that never causes al_codec_addon
   // to actually shutdown.
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

   std::string expected_cout_error_message = "[AudioController::find_music_track_sound_object_by_identifier] error: " \
                                             "unable to find element with identifier " \
                                             "\"music-track-identifier-that-does-not-exist\"\n";
   ASSERT_EQ(expected_cout_error_message, cout_message);

   al_uninstall_system();
}


TEST(AllegroFlare_AudioControllerTest,
   music_track_element_exists__when_a_music_track_identifier_is_present__returns_true)
{
   // TODO
}


TEST(AllegroFlare_AudioControllerTest,
   music_track_element_exists__when_a_music_track_identifier_is_not_present__returns_false)
{
   // TODO
}


TEST(AllegroFlare_AudioControllerTest,
   sound_effect_element_exists__when_a_sound_effect_identifier_is_present__returns_true)
{
   // TODO
}


TEST(AllegroFlare_AudioControllerTest,
   sound_effect_element_exists__when_a_sound_effect_identifier_is_not_present__returns_false)
{
   // TODO
}


TEST(AllegroFlare_AudioControllerTest, DISABLED__play_music_track_by_identifier__plays_the_audio_track)
{
   // test works, but a .ogg file is needed (the .wav file fixture is a bit large in size)

   al_init();
   al_install_audio();
   al_init_acodec_addon();

   AllegroFlare::SampleBin sample_bin;
   sample_bin.set_full_path(TEST_FIXTURE_FOLDER_NAME);
   std::string music_identifier = "music-1.wav";

   std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements;
   std::map<std::string, AllegroFlare::AudioRepositoryElement> music_track_elements = {
      { music_identifier, { music_identifier, false } },
   };
   AllegroFlare::AudioController audio_controller(&sample_bin, sound_effect_elements, music_track_elements);
   audio_controller.initialize();

   audio_controller.play_music_track_by_identifier(music_identifier);

   usleep(2000);

   audio_controller.destruct();

   sample_bin.clear();
   al_uninstall_system();
}


TEST(AllegroFlare_AudioControllerTest,
   DISABLED__set_and_load_sound_effect_elements__will_load_the_sound_effects_into_the_directory)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();

   AllegroFlare::SampleBin sample_bin;
   sample_bin.set_full_path(TEST_FIXTURE_FOLDER_NAME);
   AllegroFlare::AudioController audio_controller(&sample_bin);
   audio_controller.initialize();

   std::map<std::string, AllegroFlare::AudioRepositoryElement> sound_effect_elements = {
      { "pickup_health", { "pickup_health-01.ogg", false } },
   };

   audio_controller.set_and_load_sound_effect_elements(sound_effect_elements);

   // audio_controller.play_sound_effect_by_identifier("pickup_health"); // works, but disabled for annoyance
   // sleep(2);

   audio_controller.destruct();

   sample_bin.clear();
   al_uninstall_system();
}


