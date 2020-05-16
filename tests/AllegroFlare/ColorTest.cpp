

#include <gtest/gtest.h>

#include <AllegroFlare/Color.hpp>


TEST(AllegroFlare_ColorTest, null_color__contains_the_expected_values)
{
   ALLEGRO_COLOR color = AllegroFlare::color::null_color;
   EXPECT_EQ(0, color.r);
   EXPECT_EQ(0, color.g);
   EXPECT_EQ(0, color.b);
   EXPECT_EQ(1.0, color.a);
}



