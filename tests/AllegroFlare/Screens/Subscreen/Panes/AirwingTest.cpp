
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/Subscreen/Panes/Airwing.hpp>


TEST(AllegroFlare_Screens_Subscreen_Panes_AirwingTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Subscreen::Panes::Airwing airwing;
}


TEST(AllegroFlare_Screens_Subscreen_Panes_AirwingTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Screens/Subscreen/Panes/Airwing",
     AllegroFlare::Screens::Subscreen::Panes::Airwing::TYPE
   );
}


TEST(AllegroFlare_Screens_Subscreen_Panes_AirwingTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::Subscreen::Panes::Airwing airwing;
   EXPECT_EQ(AllegroFlare::Screens::Subscreen::Panes::Airwing::TYPE, airwing.get_type());
}


