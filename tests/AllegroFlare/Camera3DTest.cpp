
#include <gtest/gtest.h>

#include <AllegroFlare/Camera3D.hpp>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec2D.hpp>


TEST(AllegroFlare_Camera3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Camera3D camera3d;
}


TEST(AllegroFlare_Camera3DTest, get_projected_coordinates__will_return_2d_pixel_coordinates)
{
   al_init();
   AllegroFlare::Camera3D camera3d;
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   //ALLEGRO_BITMAP *surface = al_create_bitmap(1920, 1080);
   ALLEGRO_BITMAP *surface = al_get_backbuffer(display);

   //camera3d.position = AllegroFlare::Vec3D(10, -10, 6);
   //camera3d.stepout = AllegroFlare::Vec3D(0, 1, 10);

   camera3d.position = AllegroFlare::Vec3D(0, 0, 0);
   camera3d.stepout = AllegroFlare::Vec3D(0, 0, 10);

   AllegroFlare::Vec2D expected_projected_coordinates = AllegroFlare::Vec2D(0, 0);
   AllegroFlare::Vec2D actual_projected_coordinates = camera3d.get_projected_coordinates(surface, 1, 0, 0);

   EXPECT_EQ(expected_projected_coordinates, actual_projected_coordinates);

   al_flip_display();
   //al_rest(1);

   //al_destroy_bitmap(surface);
   al_destroy_display(display);

   al_uninstall_system();
}


