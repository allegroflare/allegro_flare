
#include <gtest/gtest.h>

#include <AllegroFlare/RenderSurfaces/Bitmap.hpp>


TEST(AllegroFlare_RenderSurfaces_BitmapTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RenderSurfaces::Bitmap bitmap;
}


TEST(AllegroFlare_RenderSurfaces_BitmapTest, TYPE__has_the_expected_value)
{
   AllegroFlare::RenderSurfaces::Bitmap bitmap;
   EXPECT_EQ("AllegroFlare/RenderSurfaces/Bitmap", bitmap.get_type());
}


TEST(AllegroFlare_RenderSurfaces_BitmapTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::RenderSurfaces::Bitmap bitmap;
   EXPECT_EQ(AllegroFlare::RenderSurfaces::Bitmap::TYPE, bitmap.get_type());
}


