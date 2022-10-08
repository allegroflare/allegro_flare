
#include <gtest/gtest.h>

#include <AllegroFlare/AudioProcessing/AudioMixer.hpp>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


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

   std::string sample_filename =
      "/Users/markoates/Repos/allegro_flare/tests/test_fixtures/music_tracks/test-bips-short-130bpm-01.ogg";
   ALLEGRO_SAMPLE *sample = al_load_sample(sample_filename.c_str());
   ASSERT_NE(nullptr, sample);
   ALLEGRO_SAMPLE_INSTANCE *sample_instance = al_create_sample_instance(sample);
   ASSERT_NE(nullptr, sample_instance);

   AllegroFlare::AudioProcessing::AudioMixer audio_mixer;
   audio_mixer.initialize();

   al_attach_sample_instance_to_mixer(sample_instance, audio_mixer.get_mixer());
   al_play_sample_instance(sample_instance);

   al_rest(2);

   al_uninstall_audio();
   // al_shugdown_acodec_addon(); // <- does not exist
   al_uninstall_system();
}


