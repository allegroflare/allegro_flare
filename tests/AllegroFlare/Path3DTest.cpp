
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
      Vec3D(0, 0,  0),
      Vec3D(20, 0, 10),
      Vec3D(0, 43, 30),
   };

   Path3D path3d;
   path3d.add_points(points);

   EXPECT_EQ(3, path3d.num_points());
   EXPECT_EQ(points, path3d.get_points());
}


