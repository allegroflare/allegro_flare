#include <gtest/gtest.h>
#include <AllegroFlare/Vec3D.hpp>


TEST(AllegroFlare_Vec3DTest, cross_product__will_return_expected_values)
{
   // Tests provided by ChatGPT

   using AllegroFlare::Vec3D;
   Vec3D a, b, expected_result;

   a = Vec3D(2.0, 3.0, 4.0);
   b = Vec3D(5.0, 6.0, 7.0);
   expected_result = Vec3D(-3.0, 6.0, -3.0);
   EXPECT_EQ(expected_result, a.cross_product(b));

   a = Vec3D(-3.0, 4.0, -5.0);
   b = Vec3D(4.0, 5.0, 6.0);
   expected_result = Vec3D(49.0, -2.0, -31.0);
   EXPECT_EQ(expected_result, a.cross_product(b));

   // Test 1: cross product of i and j should be k
   ASSERT_EQ(Vec3D(0, 0, 1), Vec3D(1, 0, 0).cross_product(Vec3D(0, 1, 0)));

   // Test 2: cross product of j and k should be i
   ASSERT_EQ(Vec3D(1, 0, 0), Vec3D(0, 1, 0).cross_product(Vec3D(0, 0, 1)));

   // Test 3: cross product of k and i should be j
   ASSERT_EQ(Vec3D(0, 1, 0), Vec3D(0, 0, 1).cross_product(Vec3D(1, 0, 0)));

   // Test 4: cross product of two parallel vectors should be zero
   ASSERT_EQ(Vec3D(0, 0, 0), Vec3D(1, 2, 3).cross_product(Vec3D(2, 4, 6)));
}


