
#include <gtest/gtest.h>

#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Camera3D.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Model3DTest : public ::testing::Test {};
class AllegroFlare_Model3DWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};



TEST_F(AllegroFlare_Model3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Model3D model_3d;
}


TEST_F(AllegroFlare_Model3DTest, initialize__will_work_as_expected)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::Model3D model_3d;
   model_3d.initialize();

   al_destroy_display(display);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Model3DTest, draw__will_draw_the_object)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Camera3D camera;
   AllegroFlare::Model3D model_3d;
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   model_3d.initialize();

   al_destroy_display(display);
   al_uninstall_system();
}


