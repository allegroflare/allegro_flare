
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/AllegroFlare/DisplaySettingsInterfaces/DisplayMock.hpp>


TEST(AllegroFlare_Testing_AllegroFlare_DisplaySettingsInterfaces_DisplayMockTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Testing::AllegroFlare::DisplaySettingsInterfaces::DisplayMock display_mock;
}


TEST(AllegroFlare_Testing_AllegroFlare_DisplaySettingsInterfaces_DisplayMockTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Testing/AllegroFlare/DisplaySettingsInterfaces/DisplayMock",
     AllegroFlare::Testing::AllegroFlare::DisplaySettingsInterfaces::DisplayMock::TYPE
   );
}


TEST(AllegroFlare_Testing_AllegroFlare_DisplaySettingsInterfaces_DisplayMockTest,
   type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Testing::AllegroFlare::DisplaySettingsInterfaces::DisplayMock display_mock;
   EXPECT_EQ(
      AllegroFlare::Testing::AllegroFlare::DisplaySettingsInterfaces::DisplayMock::TYPE,
      display_mock.get_type()
   );
}


TEST(AllegroFlare_Testing_AllegroFlare_DisplaySettingsInterfaces_DisplayMockTest,
   is_fulscreen__will_return_true_by_default)
{
   AllegroFlare::Testing::AllegroFlare::DisplaySettingsInterfaces::DisplayMock display_mock;
   EXPECT_EQ(false, display_mock.is_fullscreen());
}


TEST(AllegroFlare_Testing_AllegroFlare_DisplaySettingsInterfaces_DisplayMockTest,
   activate_fulscreen__will_set_fullscreen_to_true)
{
   AllegroFlare::Testing::AllegroFlare::DisplaySettingsInterfaces::DisplayMock display_mock;
   display_mock.activate_fullscreen();
   EXPECT_EQ(true, display_mock.is_fullscreen());
}


TEST(AllegroFlare_Testing_AllegroFlare_DisplaySettingsInterfaces_DisplayMockTest,
   deactivate_fulscreen__when_in_fullscreen_mode__will_set_fullscreen_to_false)
{
   AllegroFlare::Testing::AllegroFlare::DisplaySettingsInterfaces::DisplayMock display_mock;
   display_mock.activate_fullscreen();
   ASSERT_EQ(true, display_mock.is_fullscreen());
   display_mock.deactivate_fullscreen();
   EXPECT_EQ(false, display_mock.is_fullscreen());
}


TEST(AllegroFlare_Testing_AllegroFlare_DisplaySettingsInterfaces_DisplayMockTest,
   toggle_fulscreen__will_toggle_is_fullscreen_between_true_and_false)
{
   AllegroFlare::Testing::AllegroFlare::DisplaySettingsInterfaces::DisplayMock display_mock;

   display_mock.toggle_fullscreen();
   ASSERT_EQ(true, display_mock.is_fullscreen());
   display_mock.toggle_fullscreen();
   EXPECT_EQ(false, display_mock.is_fullscreen());
   display_mock.toggle_fullscreen();
   EXPECT_EQ(true, display_mock.is_fullscreen());
}


