
#include <gtest/gtest.h>

#include <AllegroFlare/AudioProcessing/AudioMixer.hpp>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <AllegroFlare/SampleBin.hpp>


#define TEST_FIXTURES_PATH "./tests/fixtures/"


TEST(AllegroFlare_AudioProcessing_AudioMixerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AudioProcessing::AudioMixer audio_mixer;
}


TEST(AllegroFlare_AudioProcessing_AudioMixerTest, initialize__will_not_blow_up)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();
   al_reserve_samples(32); // used to implicitly create the default mixer and default voice

   AllegroFlare::SampleBin sample_bin;
   sample_bin.set_full_path(TEST_FIXTURES_PATH "samples/");

   ALLEGRO_SAMPLE *sample = sample_bin.auto_get("music_tracks/test-bips-short-130bpm-01.ogg");
   ASSERT_NE(nullptr, sample);
   ALLEGRO_SAMPLE_INSTANCE *sample_instance = al_create_sample_instance(sample);
   ASSERT_NE(nullptr, sample_instance);

   AllegroFlare::AudioProcessing::AudioMixer audio_mixer;
   audio_mixer.initialize();

   al_attach_sample_instance_to_mixer(sample_instance, audio_mixer.get_mixer());
   al_play_sample_instance(sample_instance);

   al_rest(2);

   // TODO: audit this destruction sequence
   al_stop_sample_instance(sample_instance);
   al_detach_sample_instance(sample_instance);
   al_destroy_sample_instance(sample_instance);
   sample_bin.clear();
   al_uninstall_audio();
   // al_shutdown_acodec_addon(); // <- does not exist
   al_uninstall_system();
}


