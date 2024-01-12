
#include <gtest/gtest.h>

#include <AllegroFlare/DisplaySettingsInterfaces/Live.hpp>


TEST(AllegroFlare_DisplaySettingsInterfaces_LiveTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DisplaySettingsInterfaces::Live live;
}


TEST(AllegroFlare_DisplaySettingsInterfaces_LiveTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DisplaySettingsInterfaces/Live",
     AllegroFlare::DisplaySettingsInterfaces::Live::TYPE
   );
}


TEST(AllegroFlare_DisplaySettingsInterfaces_LiveTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DisplaySettingsInterfaces::Live live;
   EXPECT_EQ(AllegroFlare::DisplaySettingsInterfaces::Live::TYPE, live.get_type());
}


