
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

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

   ALLEGRO_SAMPLE *sample = al_load_sample("./tests/fixtures/samples/music_tracks/music-01.ogg");
   ASSERT_NE(nullptr, sample);

   AllegroFlare::Sound sound(sample);
   sound.initialize();
   sound.play();

   al_rest(2);

   al_destroy_sample(sample);
   al_uninstall_audio();
   al_uninstall_system();
}


TEST(AllegroFlare_SoundTest, initialize__without_al_reserve_samples_called__will_throw_an_error)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();
   //al_reserve_samples(32); // used to implicitly create the default mixer and default voice

   ALLEGRO_SAMPLE *sample = al_load_sample("./tests/fixtures/samples/music_tracks/music-01.ogg");
   ASSERT_NE(nullptr, sample);

   AllegroFlare::Sound sound(sample);
   EXPECT_THROW_WITH_MESSAGE(sound.initialize(), std::runtime_error, "[AllegroFlare::Sound::initialize]: error: "
      "Was not able to successfully obtain a mixer. AllegroFlare/Sound is currently implemented to rely on the "
      "presence of Allegro's auto-created mixer (a result of a call to al_reserve_samples()). AllegroFlare/Sound "
      "obtains this mixer via al_get_default_mixer(), but it is not present.");

   //sound.play();

   //al_rest(2);

   //al_destroy_sample(sample);
   al_uninstall_audio();
   al_uninstall_system();
}


