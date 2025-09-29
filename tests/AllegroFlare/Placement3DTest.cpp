
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


TEST(AllegroFlare_Placement3DTest,
   build_transform__with_different_rotation_orders__will_produce_the_correct_transformations)
{
   AllegroFlare::Placement3D placement;
   placement.rotation = {0.25f, 0.25f, 0.25f}; // 90 degrees on each axis
   AllegroFlare::Vec3D point_to_transform = {1.0f, 0.0f, 0.0f};

   std::vector<std::tuple<AllegroFlare::Placement3D::RotationOrder, AllegroFlare::Vec3D>> test_data = {
      { AllegroFlare::Placement3D::RotationOrder::XYZ, AllegroFlare::Vec3D(0, 0, -1) },
      { AllegroFlare::Placement3D::RotationOrder::XZY, AllegroFlare::Vec3D(0, 1, 0) },
      { AllegroFlare::Placement3D::RotationOrder::YXZ, AllegroFlare::Vec3D(-1, 0, 0) },
      { AllegroFlare::Placement3D::RotationOrder::YZX, AllegroFlare::Vec3D(0, 1, 0) },
      { AllegroFlare::Placement3D::RotationOrder::ZXY, AllegroFlare::Vec3D(1, 0, 0) },
      { AllegroFlare::Placement3D::RotationOrder::ZYX, AllegroFlare::Vec3D(0, 0, 1) },
   };

   float float_eq_threshold = 0.00001f;
   for (auto &test_case : test_data)
   {
      placement.rotation_order = std::get<0>(test_case);
      AllegroFlare::Vec3D expected_point = std::get<1>(test_case);
      
      ALLEGRO_TRANSFORM transform;
      placement.build_transform(&transform);

      AllegroFlare::Vec3D actual_point = point_to_transform;
      al_transform_coordinates_3d(&transform, &actual_point.x, &actual_point.y, &actual_point.z);

      EXPECT_NEAR(expected_point.x, actual_point.x, float_eq_threshold);
      EXPECT_NEAR(expected_point.y, actual_point.y, float_eq_threshold);
      EXPECT_NEAR(expected_point.z, actual_point.z, float_eq_threshold);
   }
}



