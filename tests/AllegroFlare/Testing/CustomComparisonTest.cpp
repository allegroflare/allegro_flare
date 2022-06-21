
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/CustomComparison.hpp>


TEST(AllegroFlare_Testing_CustomComparisonTest, PrintTo__with_an_ALLEGRO_COLOR__will_output_as_expected)
{
   std::stringstream ss;
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.3, 0.4, 0.5};

   PrintTo(color, &ss);

   std::string expected_output = "ALLEGRO_COLOR{0.2, 0.3, 0.4, 0.5}";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_CustomComparisonTest, PrintTo__with_an_AllegroFlare_Vec2D__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::Vec2D vec = {0.1, 0.2};

   PrintTo(vec, &ss);

   std::string expected_output = "AllegroFlare::Vec2D(0.1, 0.2)";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_CustomComparisonTest, PrintTo__with_an_AllegroFlare_Color__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::Color color(0.1, 0.2, 0.4, 0.8);

   PrintTo(color, &ss);

   std::string expected_output = "AllegroFlare::Color(0.1, 0.2, 0.4, 0.8)";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


