
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/AABB2D.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Physics_AABB2DTest,
   PrintTo__with_an_AllegroFlare_AABB2D__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::Physics::AABB2D object = {0.1, 0.2};

   PrintTo(object, &ss);

   std::string expected_output =
      "AllegroFlare::Physics::AABB2D(x: 0.1, y: 0.2, w: 0, h: 0, velocity_x: 0, velocity_y: 0)";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Physics_AABB2DTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::Physics::AABB2D object;
   AllegroFlare::Physics::AABB2D other_object;

   EXPECT_EQ(object, other_object);
}


