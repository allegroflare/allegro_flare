
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/FlatColor.hpp>


TEST(AllegroFlare_Shaders_FlatColorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::FlatColor flat_color;
}


TEST(AllegroFlare_Shaders_FlatColorTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Shaders/FlatColor",
     AllegroFlare::Shaders::FlatColor::TYPE
   );
}


TEST(AllegroFlare_Shaders_FlatColorTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::FlatColor flat_color;
   EXPECT_EQ(AllegroFlare::Shaders::FlatColor::TYPE, flat_color.get_type());
}


