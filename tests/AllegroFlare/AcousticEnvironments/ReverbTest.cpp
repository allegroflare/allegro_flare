
#include <gtest/gtest.h>

#include <AllegroFlare/AcousticEnvironments/Reverb.hpp>


TEST(AllegroFlare_AcousticEnvironments_ReverbTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AcousticEnvironments::Reverb reverb;
}


TEST(AllegroFlare_AcousticEnvironments_ReverbTest, TYPE__has_the_expected_value)
{
   AllegroFlare::AcousticEnvironments::Reverb reverb;
   EXPECT_EQ("AcousticEnvironments/Reverb", reverb.get_type());
}


TEST(AllegroFlare_AcousticEnvironments_ReverbTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::AcousticEnvironments::Reverb reverb;
   EXPECT_EQ(AllegroFlare::AcousticEnvironments::Reverb::TYPE, reverb.get_type());
}


TEST(AllegroFlare_AcousticEnvironments_ReverbTest, initialize__will_not_blow_up)
{
   al_init();
   al_install_audio();
   al_reserve_samples(32); // used to implicitly create the default mixer and default voice

   AllegroFlare::AcousticEnvironments::Reverb reverb;
   reverb.initialize();

   al_rest(1);

   al_uninstall_audio();
   al_uninstall_system();
}


