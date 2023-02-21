
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec3D.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Vec3DTest,
   PrintTo__with_an_AllegroFlare_Vec3D__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::Vec3D vec = {0.1, 0.2};

   PrintTo(vec, &ss);

   std::string expected_output = "AllegroFlare::Vec3D(0.1, 0.2)";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Vec3DTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::Vec3D vec;
   AllegroFlare::Vec3D other_vec;

   EXPECT_EQ(vec, other_vec);
}


