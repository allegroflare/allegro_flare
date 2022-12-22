
#include <gtest/gtest.h>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/Sound.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <allegro5/allegro_acodec.h>


TEST(AllegroFlare_SoundTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Sound sound;
}


TEST(AllegroFlare_SoundTest, DISABLED__initialize__will_not_blow_up)
{
   al_init();
   al_install_audio();

   AllegroFlare::Sound sound;
   sound.initialize();

   al_uninstall_system();
}


TEST(AllegroFlare_SoundTest, AUDIBLE__play__will_play_the_sound)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();
   al_reserve_samples(32); // used to implicitly create the default mixer and default voice

   ALLEGRO_SAMPLE *sample = al_load_sample("./tests/test_fixtures/music_tracks/music-01.ogg");
   ASSERT_NE(nullptr, sample);

   AllegroFlare::Sound sound(sample);
   sound.initialize();
   sound.play();

   al_rest(2);

   al_destroy_sample(sample);
   al_uninstall_audio();
   al_uninstall_system();
}


