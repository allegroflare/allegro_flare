
#include <gtest/gtest.h>

#include <AllegroFlare/AudioProcessing/Delay.hpp>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


TEST(AllegroFlare_AudioProcessing_DelayTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AudioProcessing::Delay delay;
}


/*
TEST(AllegroFlare_AudioProcessing_DelayTest, TYPE__has_the_expected_value)
{
   AllegroFlare::AudioProcessing::Delay delay;
   EXPECT_EQ("AudioProcessing/Delay", delay.get_type());
}


TEST(AllegroFlare_AudioProcessing_DelayTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::AudioProcessing::Delay delay;
   EXPECT_EQ(AllegroFlare::AudioProcessing::Delay::TYPE, delay.get_type());
}
*/


/*
TEST(AllegroFlare_AudioProcessing_DelayTest, initialize__will_not_blow_up)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();
   al_reserve_samples(32); // used to implicitly create the default mixer and default voice

   std::string sample_filename =
      "/Users/markoates/Repos/allegro_flare/tests/test_fixtures/music_tracks/test-bips-short-01.ogg";
   ALLEGRO_SAMPLE *sample = al_load_sample(sample_filename.c_str());
   ASSERT_NE(nullptr, sample);
   ALLEGRO_SAMPLE_INSTANCE *sample_instance = al_create_sample_instance(sample);
   ASSERT_NE(nullptr, sample_instance);


   AllegroFlare::AudioProcessing::Delay delay_environment;
   delay_environment.initialize();

   al_attach_sample_instance_to_mixer(sample_instance, delay_environment.get_delay_mixer());
   //al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());

   al_play_sample_instance(sample_instance);
   //al_play_sample(sample, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);


   al_rest(2);

   al_uninstall_audio();
   // al_shugdown_acodec_addon(); // <- does not exist
   al_uninstall_system();
}
*/


