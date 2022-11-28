
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/CubeShooter/Screen.hpp>


TEST(AllegroFlare_Prototypes_CubeShooter_ScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::CubeShooter::Screen screen;
}


TEST(AllegroFlare_Prototypes_CubeShooter_ScreenTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Prototypes::CubeShooter::Screen screen;
   EXPECT_EQ("CubeShooter/Screen", screen.get_type());
}


TEST(AllegroFlare_Prototypes_CubeShooter_ScreenTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Prototypes::CubeShooter::Screen screen;
   EXPECT_EQ(AllegroFlare::Prototypes::CubeShooter::Screen::TYPE, screen.get_type());
}



//#include <CubeShooter/Runner.hpp>

//TEST(AllegroFlare_Prototypes_CubeShooter_ScreenTest, INTERACTIVE__run__returns_the_expected_response)
//{
   //AllegroFlare::Prototypes::CubeShooter::Runner runner;
   //runner.RUN("test");
//}


