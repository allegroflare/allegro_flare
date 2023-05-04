#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <AllegroFlare/Model3DObjLoader.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <cmath>
#include <iostream>
//#include <cmath>


class Basic3D : public AllegroFlare::Screens::Base
{
private:
   bool initialized;
   AllegroFlare::Camera3D camera;
   AllegroFlare::Model3D model;
   ALLEGRO_BITMAP *texture;
   AllegroFlare::Placement3D model_placement;

public:
   Basic3D()
      : AllegroFlare::Screens::Base("Basic3D")
      , initialized(false)
      , camera()
      , model()
      , texture(nullptr)
      , model_placement()
   {};

   void initialize()
   {
      model.initialize();
      AllegroFlare::Model3DObjLoader loader(&model, "/Users/markoates/Repos/allegro_flare/bin/data/models/heart_item-01.obj", 1.0);
      loader.load();
      texture = al_load_bitmap("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/heart_item-02.png");
      model.set_texture(texture);

      initialized = true;
   }

   virtual void primary_timer_func() override
   {
      if (!initialized) throw std::runtime_error("must be initialized");

      // setup the projection
      camera.stepout = AllegroFlare::Vec3D(0, 0, 5); // camera's target is positioned at (0,0,0) but the camera will be 5 meters back
      camera.tilt = 0.4; // tilt the camera, looking down slightly at the target
      camera.setup_projection_on(al_get_backbuffer(al_get_current_display()));

      // position and render model
      model_placement.rotation.y += 0.005;
      model_placement.start_transform();
      model.draw();
      model_placement.restore_transform();
   }
};


int main(int argc, char **argv)
{
   // init AllegroFlare
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();

   Basic3D basic_3d;
   basic_3d.initialize();

   framework.register_and_activate_screen("basic_3d", &basic_3d);

   framework.run_loop();
   return 0;
}


