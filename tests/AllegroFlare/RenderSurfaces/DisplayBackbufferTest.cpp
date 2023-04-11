
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


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferTest, initialize__will_not_blow_up)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::RenderSurfaces::DisplayBackbuffer display_backbuffer(display);
   display_backbuffer.initialize();

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferTest, get_width__will_return_the_width_of_the_surface)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::RenderSurfaces::DisplayBackbuffer display_backbuffer(display);
   display_backbuffer.initialize();
   EXPECT_EQ(1920, display_backbuffer.get_width());

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_RenderSurfaces_DisplayBackbufferTest, get_height__will_return_the_height_of_the_surface)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::RenderSurfaces::DisplayBackbuffer display_backbuffer(display);
   display_backbuffer.initialize();
   EXPECT_EQ(1080, display_backbuffer.get_height());

   al_destroy_display(display);
   al_uninstall_system();
}


