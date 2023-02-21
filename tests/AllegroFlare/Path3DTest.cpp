
#include <gtest/gtest.h>

#include <AllegroFlare/Path3D.hpp>


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


