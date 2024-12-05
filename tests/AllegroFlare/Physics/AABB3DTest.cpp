
#include <gtest/gtest.h>

#include <AllegroFlare/Physics/AABB3D.hpp>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec3D.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Camera3D.hpp>


class AllegroFlare_Physics_AABB3DTest : public ::testing::Test {};
class AllegroFlare_Physics_AABB3DTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Physics_AABB3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Physics::AABB3D aabb3d;
}


TEST_F(AllegroFlare_Physics_AABB3DTest,
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


TEST_F(AllegroFlare_Physics_AABB3DTest, collides__will_work_as_expected)
{
   // TODO: add tests for this case
}


TEST_F(AllegroFlare_Physics_AABB3DTest, draw__will_render_the_outline_of_the_bounding_box)
{
   // TODO: add tests for this case
}


TEST_F(AllegroFlare_Physics_AABB3DTest, collides_with_point__will_return_true_if_a_point_is_within_the_box)
{
   AllegroFlare::Physics::AABB3D aabb3d(
      AllegroFlare::Vec3D(-2, -4, -7),
      AllegroFlare::Vec3D(6, 8, 12)
   );

   EXPECT_EQ(true, aabb3d.collides_with_point(AllegroFlare::Vec3D(0, 0, 0)));

   EXPECT_EQ(true, aabb3d.collides_with_point(AllegroFlare::Vec3D(-1.999, 0, 0)));
   EXPECT_EQ(true, aabb3d.collides_with_point(AllegroFlare::Vec3D(0, -3.999, 0)));
   EXPECT_EQ(true, aabb3d.collides_with_point(AllegroFlare::Vec3D(0, 0, -6.999)));

   EXPECT_EQ(true, aabb3d.collides_with_point(AllegroFlare::Vec3D(5.999, 0, 0)));
   EXPECT_EQ(true, aabb3d.collides_with_point(AllegroFlare::Vec3D(0, 7.999, 0)));
   EXPECT_EQ(true, aabb3d.collides_with_point(AllegroFlare::Vec3D(0, 0, 11.999)));
}


TEST_F(AllegroFlare_Physics_AABB3DTest, collides_with_point__will_return_false_if_a_point_is_outside_the_box)
{
   AllegroFlare::Physics::AABB3D aabb3d(
      AllegroFlare::Vec3D(-2, -4, -7),
      AllegroFlare::Vec3D(6, 8, 12)
   );

   EXPECT_EQ(false, aabb3d.collides_with_point(AllegroFlare::Vec3D(-2.001, 0, 0)));
   EXPECT_EQ(false, aabb3d.collides_with_point(AllegroFlare::Vec3D(0, -4.001, 0)));
   EXPECT_EQ(false, aabb3d.collides_with_point(AllegroFlare::Vec3D(0, 0, -7.001)));

   EXPECT_EQ(false, aabb3d.collides_with_point(AllegroFlare::Vec3D(6.001, 0, 0)));
   EXPECT_EQ(false, aabb3d.collides_with_point(AllegroFlare::Vec3D(0, 8.001, 0)));
   EXPECT_EQ(false, aabb3d.collides_with_point(AllegroFlare::Vec3D(0, 0, 12.001)));
}


TEST_F(AllegroFlare_Physics_AABB3DTestWithAllegroRenderingFixture, CAPTURE__VISUAL__draw__will_render_as_expected)
{
   AllegroFlare::Camera3D camera;
   camera.stepout = { 0, 0, 8 };
   camera.tilt = 0.125;
   camera.spin = 0.25;

   AllegroFlare::Physics::AABB3D aabb3d(
      AllegroFlare::Vec3D(-1, -1, -1),
      AllegroFlare::Vec3D(1, 1, 1)
   );

   ALLEGRO_BITMAP* render_surface = al_get_target_bitmap();
   camera.setup_projection_on(render_surface);
   aabb3d.draw();
   al_flip_display();
   al_rest(2);
}


