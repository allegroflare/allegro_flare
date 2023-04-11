
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


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferSubBitmapTest, initialize__will_not_blow_up)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap display_backbuffer_sub_bitmap(display);
   display_backbuffer_sub_bitmap.initialize();

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferSubBitmapTest, get_width__will_return_the_width_of_the_surface)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap display_backbuffer_sub_bitmap(display);
   display_backbuffer_sub_bitmap.initialize();
   EXPECT_EQ(1920, display_backbuffer_sub_bitmap.get_width());

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferSubBitmapTest, get_height__will_return_the_height_of_the_surface)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap display_backbuffer_sub_bitmap(display);
   display_backbuffer_sub_bitmap.initialize();
   EXPECT_EQ(1080, display_backbuffer_sub_bitmap.get_height());

   al_destroy_display(display);
   al_uninstall_system();
}


