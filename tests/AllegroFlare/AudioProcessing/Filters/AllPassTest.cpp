
#include <gtest/gtest.h>

#include <AllegroFlare/AudioProcessing/Filters/AllPass.hpp>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <AllegroFlare/SampleBin.hpp>


#define TEST_FIXTURES_PATH "./tests/fixtures/"


TEST(AllegroFlare_AudioProcessing_Filters_AllPassTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AudioProcessing::Filters::AllPass all_pass;
}


TEST(AllegroFlare_AudioProcessing_Filters_AllPassTest, initialize__will_not_blow_up)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();
   al_reserve_samples(32); // used to implicitly create the default mixer and default voice

   AllegroFlare::SampleBin sample_bin;
   sample_bin.set_full_path(TEST_FIXTURES_PATH "samples/");

   ALLEGRO_SAMPLE *sample = sample_bin.auto_get("music_tracks/music-01.ogg");
   ASSERT_NE(nullptr, sample);
   ALLEGRO_SAMPLE_INSTANCE *sample_instance = al_create_sample_instance(sample);
   ASSERT_NE(nullptr, sample_instance);


   AllegroFlare::AudioProcessing::Filters::AllPass all_pass;
   all_pass.initialize();
   all_pass.set_offset_sec(0.0042);
   all_pass.set_wet(1.0f);
   all_pass.set_dry(1.0f);

   al_attach_sample_instance_to_mixer(sample_instance, all_pass.get_al_mixer());
   al_play_sample_instance(sample_instance);

   al_rest(3);

   // TODO: audit this destruction sequence
   al_stop_sample_instance(sample_instance);
   al_detach_sample_instance(sample_instance);
   al_destroy_sample_instance(sample_instance);
   sample_bin.clear();
   al_uninstall_audio();
   // al_shutdown_acodec_addon(); // <- does not exist
   al_uninstall_system();
}


