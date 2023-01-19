
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/CubeMap.hpp>


TEST(AllegroFlare_Shaders_CubeMapTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::CubeMap cube_map;
}


TEST(AllegroFlare_Shaders_CubeMapTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Shaders::CubeMap cube_map;
   EXPECT_EQ("AllegroFlare/Shaders/CubeMap", cube_map.get_type());
}


TEST(AllegroFlare_Shaders_CubeMapTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::CubeMap cube_map;
   EXPECT_EQ(AllegroFlare::Shaders::CubeMap::TYPE, cube_map.get_type());
}


