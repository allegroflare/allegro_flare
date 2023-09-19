
#include <gtest/gtest.h>

#include <AllegroFlare/Camera2D.hpp>


TEST(AllegroFlare_Camera2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Camera2D camera2d;
}


TEST(AllegroFlare_Camera2DTest, setup_dimensional_projection__will_create_a_depth_projection_on_the_bitmap)
{
   // TODO: elaborate on this
   al_init();

   ALLEGRO_BITMAP *target_bitmap = al_create_bitmap(800, 600);
   AllegroFlare::Camera2D camera2d;
   camera2d.setup_dimensional_projection(target_bitmap);

   al_uninstall_system();
}


