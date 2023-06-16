
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
   placement.rotation.y = 0.0f;
   AllegroFlare::Vec3D expected_strafe_vector = { 1.0, 0.0, 0.0 };
   AllegroFlare::Vec3D actual_strafe_vector = placement.build_strafe_vector_xz();
   EXPECT_EQ(expected_strafe_vector, actual_strafe_vector);
}


