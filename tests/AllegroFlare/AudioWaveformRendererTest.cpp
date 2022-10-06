
#include <gtest/gtest.h>

#include <AllegroFlare/AudioWaveformRenderer.hpp>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>


static std::string build_full_test_name()
{
   const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
   return test_info->test_suite_name() + std::string(" - ") + test_info->name();
}


#ifdef _WIN32
#define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/msys64/home/Mark/Repos/allegro_flare/tmp/test_snapshots/"
#else
#define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/Users/markoates/Repos/allegro_flare/tmp/test_snapshots/"
#endif


TEST(AllegroFlare_AudioWaveformRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AudioWaveformRenderer audio_waveform_renderer;
}


TEST(AllegroFlare_AudioWaveformRendererTest, draw_waveform__will_render_a_waveform_of_the_audio)
{
   al_init();
   al_install_audio();
   al_init_image_addon();
   al_init_acodec_addon();
   ALLEGRO_BITMAP *surface = al_create_bitmap(1920, 1080);
   std::string sample_filename = "/Users/markoates/Repos/allegro_flare/tests/test_fixtures/music_tracks/music-01.ogg";
   ALLEGRO_SAMPLE *sample = al_load_sample(sample_filename.c_str());
   ASSERT_NE(nullptr, sample);
   al_set_target_bitmap(surface);
   ASSERT_NE(nullptr, surface);

   AllegroFlare::AudioWaveformRenderer audio_waveform_renderer(sample);
   audio_waveform_renderer.draw_waveform(surface);

   std::string filename = TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER + build_full_test_name() + ".png";
   al_save_bitmap(filename.c_str(), surface);

   al_destroy_bitmap(surface);
   al_destroy_sample(sample);
   //al_shutdown_acodec_addon(); // <-- does not exist
   al_shutdown_image_addon();
   al_uninstall_audio();
   al_uninstall_system();
}


