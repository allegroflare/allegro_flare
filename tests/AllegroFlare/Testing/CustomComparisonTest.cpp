
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/CustomComparison.hpp>


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


TEST(AllegroFlare_Testing_CustomComparisonTest, equality_operator__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::Vec2D vec;
   AllegroFlare::Vec2D other_vec;

   EXPECT_EQ(vec, other_vec);
}


