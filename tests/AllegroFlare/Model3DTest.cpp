
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


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest, draw__will_draw_the_object)
{
   std::string MODEL_TEST_DATA_FILENAME = "/Users/markoates/Repos/allegro_flare/bin/data/models/coin_ring-01.obj";
   AllegroFlare::Camera3D camera;
   AllegroFlare::Model3D model_3d;
   model_3d.initialize();
   model_3d.load_obj_file(MODEL_TEST_DATA_FILENAME.c_str());

   camera.stepout = {0, 0, 4}; // step back from the origin
   camera.tilt = 0.35;           // look down slightly

   int loops=60;
   for (int i=0; i<loops; i++)
   {
      // update
      camera.spin += 0.01;

      // draw
      al_clear_depth_buffer(1);
      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.12, 1.0});
      camera.setup_projection_on(get_display_backbuffer());
      model_3d.draw();
      al_flip_display();
   }
}


