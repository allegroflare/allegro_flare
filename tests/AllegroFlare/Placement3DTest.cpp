
#include <gtest/gtest.h>


#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec3D.hpp>


TEST(AllegroFlare_Placement3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Placement3D placement;
}


TEST(AllegroFlare_Placement3DTest, build_strafe_vector_xz__will_return_a_strafe_vector_using_y_rotation_only)
{
   AllegroFlare::Placement3D placement;

   // TODO: Add non-right angles as test data
   std::vector<std::pair<float, AllegroFlare::Vec3D>> test_datas = {
      { 0.0f, { 1.0f, 0.0f, 0.0f } },
      { 0.25f, { 0.0f, 0.0f, 1.0f } },
      { 0.5f, { -1.0f, 0.0f, 0.0f } },
      { 0.75f, { 0.0f, 0.0f, -1.0f } },
   };

   float float_eq_threshold = 0.00001f;
   for (auto &test_data : test_datas)
   {
      placement.rotation.y = test_data.first;
      AllegroFlare::Vec3D expected_strafe_vector = test_data.second;
      AllegroFlare::Vec3D actual_strafe_vector = placement.build_strafe_vector_xz();

      // NOTE: See if there is a better way to use EXPECT_FLOAT_EQ or EXPECT_NEAR with a custom type
      EXPECT_NEAR(expected_strafe_vector.x, actual_strafe_vector.x, float_eq_threshold);
      EXPECT_NEAR(expected_strafe_vector.y, actual_strafe_vector.y, float_eq_threshold);
      EXPECT_NEAR(expected_strafe_vector.z, actual_strafe_vector.z, float_eq_threshold);
   }
}


