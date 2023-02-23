
#include <gtest/gtest.h>

#include <AllegroFlare/Physics/AABB3D.hpp>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec3D.hpp>



TEST(AllegroFlare_Physics_AABB3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Physics::AABB3D aabb3d;
}


TEST(AllegroFlare_Physics_AABB3DTest,
   expand__will_reduce_the_min_coordinates_and_increase_the_max_coordinates_by_the_amount)
{
   AllegroFlare::Physics::AABB3D aabb3d(
      AllegroFlare::Vec3D(-2, -4, -7),
      AllegroFlare::Vec3D(6, 8, 12)
   );

   aabb3d.expand(2);

   EXPECT_EQ(AllegroFlare::Vec3D(-4, -6, -9), aabb3d.get_min());
   EXPECT_EQ(AllegroFlare::Vec3D(8, 10, 14), aabb3d.get_max());
}


TEST(AllegroFlare_Physics_AABB3DTest, collides__will_work_as_expected)
{
   // TODO: add tests for this case
}


