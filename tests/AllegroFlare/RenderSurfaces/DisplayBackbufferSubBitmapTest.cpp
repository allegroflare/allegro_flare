
#include <gtest/gtest.h>

#include <AllegroFlare/RenderSurfaces/DisplayBackbufferSubBitmap.hpp>


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferSubBitmapTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap display_backbuffer_sub_bitmap;
}


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferSubBitmapTest, TYPE__has_the_expected_value)
{
   AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap display_backbuffer_sub_bitmap;
   EXPECT_EQ("AllegroFlare/RenderSurfaces/DisplayBackbufferSubBitmap", display_backbuffer_sub_bitmap.get_type());
}


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferSubBitmapTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap display_backbuffer_sub_bitmap;
   EXPECT_EQ(AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::TYPE, display_backbuffer_sub_bitmap.get_type());
}


