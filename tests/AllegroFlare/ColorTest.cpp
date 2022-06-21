

#include <gtest/gtest.h>

#include <AllegroFlare/Testing/CustomComparison.hpp>


#include <AllegroFlare/Color.hpp>


TEST(AllegroFlare_ColorTest, Null__contains_the_expected_values)
{
   ALLEGRO_COLOR color = AllegroFlare::Color::Null;
   AllegroFlare::Color expected_color(0, 0, 0, 1);

   EXPECT_EQ(0, color.r);
   EXPECT_EQ(0, color.g);
   EXPECT_EQ(0, color.b);
   EXPECT_EQ(1, color.a);
}


TEST(AllegroFlare_ColorTest, will_construct_with_a_hex_value)
{
   AllegroFlare::Color color(0xff3399);
   AllegroFlare::Color expected_color(1.0, 0.2, 0.6, 1.0);

   EXPECT_EQ(color.r, 1.0f);
   EXPECT_EQ(color.g, 0.2f);
   EXPECT_EQ(color.b, 0.6f);
   EXPECT_EQ(color.a, 1.0f);
}


TEST(AllegroFlare_ColorTest, will_construct_with_a_hex_value_respecting_a_multiplied_alpha)
{
   AllegroFlare::Color color(0xff3399, 0.25);

   EXPECT_EQ(color.r, 0.25f); // ff is 1.0, so 1.0*0.25 = 0.25
   EXPECT_EQ(color.g, 0.05f); // 33 is 0.2, so 0.2*0.25 = 0.05
   EXPECT_EQ(color.b, 0.15f); // 99 is 0.6, so 0.6*0.25 = 0.15
   EXPECT_EQ(color.a, 0.25f); // alpha is 0.25
}


TEST(AllegroFlare_ColorTest, operator_equals__will_assign_values_of_an_ALLEGRO_COLOR)
{
   AllegroFlare::Color color = AllegroFlare::Color::Null;
   color = ALLEGRO_COLOR{0.4, 0.6, 0.125, 0.8};

   EXPECT_EQ(color.r, 0.4f);
   EXPECT_EQ(color.g, 0.6f);
   EXPECT_EQ(color.b, 0.125f);
   EXPECT_EQ(color.a, 0.8f);
}


TEST(AllegroFlare_ColorTest, to_al__will_return_the_color_as_an_ALLEGRO_COLOR)
{
   AllegroFlare::Color color(0.4, 0.6, 0.125, 0.8);
   ALLEGRO_COLOR al_color = color.to_al();

   EXPECT_EQ(al_color.r, 0.4f);
   EXPECT_EQ(al_color.g, 0.6f);
   EXPECT_EQ(al_color.b, 0.125f);
   EXPECT_EQ(al_color.a, 0.8f);
}



