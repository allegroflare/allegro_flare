
#include <gtest/gtest.h>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/Sound.hpp>
#include <AllegroFlare/SampleBin.hpp>


TEST(AllegroFlare_SoundTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Sound sound;
}


TEST(AllegroFlare_SoundTest, initialize__will_not_blow_up)
{
   al_init();
   al_install_audio();

   AllegroFlare::Sound sound;
   sound.initialize();

   al_uninstall_system();
}


