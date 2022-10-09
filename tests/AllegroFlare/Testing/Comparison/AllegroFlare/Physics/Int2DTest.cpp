
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/Int2D.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Physics_Int2DTest,
   PrintTo__with_an_AllegroFlare_Int2D__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::Physics::Int2D vec = {1, 2};

   PrintTo(vec, &ss);

   std::string expected_output = "Physics::Int2(1, 2)";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Physics_Int2DTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::Physics::Int2D vec;
   AllegroFlare::Physics::Int2D other_vec;

   EXPECT_EQ(vec, other_vec);
}


