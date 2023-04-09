
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Backgrounds/ScreenCapture.hpp>


TEST(AllegroFlare_Elements_Backgrounds_ScreenCaptureTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::ScreenCapture screen_capture;
}


TEST(AllegroFlare_Elements_Backgrounds_ScreenCaptureTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Elements::Backgrounds::ScreenCapture screen_capture;
   EXPECT_EQ("AllegroFlare/Elements/Backgrounds/ScreenCapture", screen_capture.get_type());
}


TEST(AllegroFlare_Elements_Backgrounds_ScreenCaptureTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::ScreenCapture screen_capture;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::ScreenCapture::TYPE, screen_capture.get_type());
}


