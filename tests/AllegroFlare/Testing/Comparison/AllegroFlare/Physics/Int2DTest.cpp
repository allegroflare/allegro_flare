
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
   equality_operator__works_with_google_test_EXPECT_EQ_statement)
{
   AllegroFlare::Physics::Int2D vec;
   AllegroFlare::Physics::Int2D other_vec;

   EXPECT_EQ(vec, other_vec);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Physics_Int2DTest,
   inequality_operator__works_with_google_test_EXPECT_NE_statement)
{
   AllegroFlare::Physics::Int2D vec(3, 4);
   AllegroFlare::Physics::Int2D other_vec(5, 6);

   EXPECT_NE(vec, other_vec);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Physics_Int2DTest,
   inequality_operator__works_with_several_test_conditions)
{
   EXPECT_NE(AllegroFlare::Physics::Int2D(3, 4), AllegroFlare::Physics::Int2D(3, 5));
   EXPECT_NE(AllegroFlare::Physics::Int2D(3, 9), AllegroFlare::Physics::Int2D(4, 9));
}


