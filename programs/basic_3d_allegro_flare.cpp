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
   std::string model_obj_filename;
   std::string model_texture_filename;

public:
   Basic3D()
      : AllegroFlare::Screens::Base("Basic3D")
      , initialized(false)
      , camera()
      , model()
      , texture(nullptr)
      , model_placement()
      , model_obj_filename("/Users/markoates/Repos/allegro_flare/bin/data/models/heart_item-01.obj")
      , model_texture_filename("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/heart_item-02.png")
   {};

   void set_model_obj_filename(std::string model_obj_filename)
   {
      if (initialized) throw std::runtime_error("Error: cannot set_model_obj_filename after initialization");
      this->model_obj_filename = model_obj_filename;
   }

   void set_model_texture_filename(std::string model_texture_filename)
   {
      if (initialized) throw std::runtime_error("Error: cannot set_model_texture_filename after initialization");
      this->model_texture_filename = model_texture_filename;
   }

   void initialize()
   {
      model.initialize();
      AllegroFlare::Model3DObjLoader loader(&model, model_obj_filename.c_str(), 1.0);
      loader.load();
      texture = al_load_bitmap(model_texture_filename.c_str());
      if (!texture) throw std::runtime_error("Texture not found");
      model.set_texture(texture);

      initialized = true;
   }

   virtual void primary_timer_func() override
   {
      if (!initialized) throw std::runtime_error("must be initialized");

      ALLEGRO_BITMAP *render_surface = al_get_target_bitmap();

      // setup the projection
      camera.stepout = AllegroFlare::Vec3D(0, 0, 5); // camera's target is positioned at (0,0,0) but the camera will be 5 meters back
      camera.tilt = 0.4; // tilt the camera, looking down slightly at the target
      camera.setup_projection_on(render_surface);

      // position and render model
      model_placement.rotation.y += 0.00025;
      model_placement.start_transform();
      model.draw();
      model_placement.restore_transform();
   }
};


int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=1; i<argc; i++) args.push_back(argv[i]);

   // init AllegroFlare
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();

   Basic3D basic_3d;
   if (args.size() == 2)
   {
      basic_3d.set_model_obj_filename(args[0]);
      basic_3d.set_model_texture_filename(args[1]);
   }
   basic_3d.initialize();

   framework.register_and_activate_screen("basic_3d", &basic_3d);

   framework.run_loop();
   return 0;
}


