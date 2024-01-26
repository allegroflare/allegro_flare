#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <AllegroFlare/Model3DObjLoader.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <cmath>
#include <iostream>


int main(int argc, char **argv)
{
   // init allegro
   al_init();
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 16, ALLEGRO_REQUIRE);
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   al_init_image_addon();

   // load resources and create our objects
   AllegroFlare::Camera3D camera;
   AllegroFlare::Model3D model;
   AllegroFlare::Model3DObjLoader loader(&model, "/Users/markoates/Repos/allegro_flare/bin/data/models/heart_item-01.obj", 1.0);
   loader.load();
   ALLEGRO_BITMAP *texture = al_load_bitmap("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/heart_item-02.png");
   model.set_texture(texture);
   model.initialize();

   // create some placement properties
   AllegroFlare::Placement3D model_placement;

   // render
   for (int i=0; i<120; i++)
   {
      // clear the display
      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.12, 1.0f});
      al_clear_depth_buffer(1);

      // setup the projection
      camera.stepout = AllegroFlare::Vec3D(0, 0, 5); // camera's target is positioned at (0,0,0) but the camera will be 5 meters back
      camera.tilt = 0.4; // tilt the camera, looking down slightly at the target
      camera.setup_projection_on(al_get_backbuffer(display));

      // position and render model
      model_placement.rotation.y += 0.005;
      model_placement.start_transform();
      model.draw();
      model_placement.restore_transform();

      // flip the display
      al_flip_display();
   }

   return 0;
}
