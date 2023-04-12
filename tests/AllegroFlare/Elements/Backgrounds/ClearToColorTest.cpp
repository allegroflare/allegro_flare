
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Backgrounds/ClearToColor.hpp>


TEST(AllegroFlare_Elements_Backgrounds_ClearToColorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::ClearToColor clear_to_color;
}


TEST(AllegroFlare_Elements_Backgrounds_ClearToColorTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Elements::Backgrounds::ClearToColor clear_to_color;
   EXPECT_EQ("AllegroFlare/Elements/Backgrounds/ClearToColor", clear_to_color.get_type());
}


TEST(AllegroFlare_Elements_Backgrounds_ClearToColorTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::ClearToColor clear_to_color;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::ClearToColor::TYPE, clear_to_color.get_type());
}


