
#include <gtest/gtest.h>

#include <AllegroFlare/Model3D.hpp>


TEST(AllegroFlare_Model3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Model3D model_3d;
}


TEST(AllegroFlare_Model3DTest, initialize__will_work_as_expected)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::Model3D model_3d;
   model_3d.initialize();

   al_destroy_display(display);
   al_uninstall_system();
}


