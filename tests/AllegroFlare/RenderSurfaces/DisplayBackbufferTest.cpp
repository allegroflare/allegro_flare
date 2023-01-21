
#include <gtest/gtest.h>

#include <AllegroFlare/RenderSurfaces/DisplayBackbuffer.hpp>


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RenderSurfaces::DisplayBackbuffer display_backbuffer;
}


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferTest, TYPE__has_the_expected_value)
{
   AllegroFlare::RenderSurfaces::DisplayBackbuffer display_backbuffer;
   EXPECT_EQ("AllegroFlare/RenderSurfaces/DisplayBackbuffer", display_backbuffer.get_type());
}


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::RenderSurfaces::DisplayBackbuffer display_backbuffer;
   EXPECT_EQ(AllegroFlare::RenderSurfaces::DisplayBackbuffer::TYPE, display_backbuffer.get_type());
}


