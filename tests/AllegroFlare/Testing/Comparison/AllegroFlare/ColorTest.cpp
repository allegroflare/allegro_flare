
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Color.hpp>


TEST(AllegroFlare_Testing_CustomComparisonTest, PrintTo__with_an_AllegroFlare_Color__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::Color color(0.1, 0.2, 0.4, 0.8);

   PrintTo(color, &ss);

   std::string expected_output = "AllegroFlare::Color(0.1, 0.2, 0.4, 0.8)";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


