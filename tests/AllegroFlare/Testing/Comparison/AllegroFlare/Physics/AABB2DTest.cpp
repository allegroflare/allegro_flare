
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/AABB2D.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Physics_AABB2DTest,
   PrintTo__with_an_AllegroFlare_AABB2D__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::Physics::AABB2D object(0.1, 0.2, 0.25, 0.5, 0.8, 1.0);

   PrintTo(object, &ss);

   std::string expected_output =
      "AllegroFlare::Physics::AABB2D(x: 0.1, y: 0.2, w: 0.25, h: 0.5, velocity_x: 0.8, velocity_y: 1)";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Physics_AABB2DTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::Physics::AABB2D object(0.1, 0.2, 0.25, 0.5, 0.8, 1.0);
   AllegroFlare::Physics::AABB2D other_object(0.1, 0.2, 0.25, 0.5, 0.8, 1.0);

   EXPECT_EQ(object, other_object);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Physics_AABB2DTest,
   inequality_operator__works_with_google_test_EXPECT_statement)
{
   // TODO: Test each member
   AllegroFlare::Physics::AABB2D object(0.1, 0.2, 0.25, 0.5, 0.8, 1.0);
   AllegroFlare::Physics::AABB2D other_object(0.0, 0.2, 0.25, 0.5, 0.8, 1.0);

   EXPECT_NE(object, other_object);
}


