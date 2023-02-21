
#include <gtest/gtest.h>

#include <AllegroFlare/Path3D.hpp>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec3D.hpp>


TEST(AllegroFlare_Path3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Path3D path3d;
}


TEST(AllegroFlare_Path3DTest, add_points__will_append_the_points_to_the_path)
{
   using AllegroFlare::Path3D,
         AllegroFlare::Vec3D;

   std::vector<AllegroFlare::Vec3D> points = {
      AllegroFlare::Vec3D(0, 0,  0),
      AllegroFlare::Vec3D(20, 0, 10),
      AllegroFlare::Vec3D(0, 43, 30),
   };

   AllegroFlare::Path3D path3d;
   path3d.add_points(points);

   EXPECT_EQ(3, path3d.num_points());
   EXPECT_EQ(points, path3d.get_points());
}


TEST(AllegroFlare_Path3DTest, length__will_return_the_length_of_the_entire_path)
{
   std::vector<AllegroFlare::Vec3D> points = {
      AllegroFlare::Vec3D(0,   0, 0),
      AllegroFlare::Vec3D(100, 0, 0),
      AllegroFlare::Vec3D(100, 0, 100),
      AllegroFlare::Vec3D(100, 100, 100),
   };
   AllegroFlare::Path3D path3d;
   path3d.add_points(points);

   EXPECT_EQ(300, path3d.length());
}


TEST(AllegroFlare_Path3DTest, coordinate_at__will_return_the_coordinate_at_a_given_position_TEST_1)
{
   std::vector<AllegroFlare::Vec3D> points = {
      AllegroFlare::Vec3D(0,   0, 0),
      AllegroFlare::Vec3D(100, 0, 0),
      AllegroFlare::Vec3D(100, 0, 100),
      AllegroFlare::Vec3D(100, 100, 100),
   };
   AllegroFlare::Path3D path3d;
   path3d.add_points(points);

   EXPECT_EQ(AllegroFlare::Vec3D(50,  0,  0), path3d.coordinate_at(50));
   EXPECT_EQ(AllegroFlare::Vec3D(100, 0, 50), path3d.coordinate_at(150));
   EXPECT_EQ(AllegroFlare::Vec3D(100, 0, 50), path3d.coordinate_at(150));
}


TEST(AllegroFlare_Path3DTest, tangent_vector_at__will_return_the_tangent_vector_at_the_coordinate_not_smoothed)
{
   std::vector<AllegroFlare::Vec3D> points = {
      AllegroFlare::Vec3D(  0,   0,   0),
      AllegroFlare::Vec3D(100,   0,   0),
      AllegroFlare::Vec3D(100,   0, 100),
      AllegroFlare::Vec3D(100, 100, 100),
   };
   AllegroFlare::Path3D path3d;
   path3d.add_points(points);

   EXPECT_EQ(AllegroFlare::Vec3D(1.0, 0,   0), path3d.tangent_vector_at(50));
   EXPECT_EQ(AllegroFlare::Vec3D(0,   0, 1.0), path3d.tangent_vector_at(150));
   EXPECT_EQ(AllegroFlare::Vec3D(0, 1.0,   0), path3d.tangent_vector_at(250));
}


TEST(AllegroFlare_Path3DTest, tangent_vector_at__when_there_are_fewer_than_2_points__will_return_a_zero_length_vector)
{
   std::vector<AllegroFlare::Vec3D> points = {
      AllegroFlare::Vec3D(0, 0, 0),
   };
   AllegroFlare::Path3D path3d;
   path3d.add_points(points);

   EXPECT_EQ(AllegroFlare::Vec3D(0, 0, 0), path3d.tangent_vector_at(0));
}


