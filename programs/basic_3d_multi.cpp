#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <AllegroFlare/MultitextureModel3DObjLoader.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/MultitextureModel3D.hpp>
#include <AllegroFlare/Shaders/Multitexture.hpp>
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
   AllegroFlare::MultitextureModel3D model;
   ALLEGRO_BITMAP *texture_a;
   ALLEGRO_BITMAP *texture_b;
   AllegroFlare::Placement3D model_placement;
   std::string base_model_obj_filename;
   std::string uv2_model_obj_filename;
   std::string model_texture_filename;
   std::string light_texture_filename;
   AllegroFlare::Shaders::Multitexture shader;

public:
   Basic3D()
      : AllegroFlare::Screens::Base("Basic3D")
      , initialized(false)
      , camera()
      , model()
      , texture_a(nullptr)
      , texture_b(nullptr)
      , model_placement()
      , base_model_obj_filename("/Users/markoates/Repos/allegro_flare/tests/fixtures/models/simple_scene-01.obj")
      , uv2_model_obj_filename("/Users/markoates/Repos/allegro_flare/tests/fixtures/models/simple_scene-01-ao-01.obj")
      , model_texture_filename("/Users/markoates/Repos/allegro_flare/tests/fixtures/bitmaps/simple_scene-01-1024.jpg")
      , light_texture_filename("/Users/markoates/Repos/allegro_flare/tests/fixtures/bitmaps/simple_scene-01-ao-01.jpg")
      , shader()
   {};

   void set_base_model_obj_filename(std::string base_model_obj_filename)
   {
      if (initialized) throw std::runtime_error("Error: cannot set_model_obj_filename after initialization");
      this->base_model_obj_filename = base_model_obj_filename;
   }

   void set_uv2_model_obj_filename(std::string uv2_model_obj_filename)
   {
      if (initialized) throw std::runtime_error("Error: cannot set_uv2_obj_filename after initialization");
      this->uv2_model_obj_filename = uv2_model_obj_filename;
   }

   void set_model_texture_filename(std::string model_texture_filename)
   {
      if (initialized) throw std::runtime_error("Error: cannot set_model_texture_filename after initialization");
      this->model_texture_filename = model_texture_filename;
   }

   void set_light_texture_filename(std::string light_texture_filename)
   {
      if (initialized) throw std::runtime_error("Error: cannot set_light_texture_filename after initialization");
      this->light_texture_filename = light_texture_filename;
   }

   void initialize()
   {
      model.initialize();
      AllegroFlare::MultitextureModel3DObjLoader loader(&model, base_model_obj_filename.c_str(), uv2_model_obj_filename.c_str(), 1.0);
      loader.load();
      texture_a = al_load_bitmap(model_texture_filename.c_str());
      texture_b = al_load_bitmap(light_texture_filename.c_str());
      if (!texture_a) throw std::runtime_error("Texture (texture_a) not found");
      if (!texture_b) throw std::runtime_error("Texture (texture_b) not found");
      model.set_texture(texture_a);

      shader.initialize();

      initialized = true;
   }

   virtual void primary_timer_func() override
   {
      if (!initialized) throw std::runtime_error("must be initialized");

      // setup the projection
      camera.stepout = AllegroFlare::Vec3D(0, 0, 5); // camera's target is positioned at (0,0,0) but the camera will be 5 meters back
      camera.tilt = 0.4; // tilt the camera, looking down slightly at the target
      camera.setup_projection_on(al_get_backbuffer(al_get_current_display()));

      shader.activate();

      shader.set_texture_a(texture_a);
      shader.set_texture_b(texture_b);

      // position and render model
      model_placement.rotation.y += 0.001;
      model_placement.start_transform();
      model.draw();
      model_placement.restore_transform();

      shader.deactivate();
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
   if (args.size() == 3)
   {
      basic_3d.set_base_model_obj_filename(args[0]);
      basic_3d.set_uv2_model_obj_filename(args[1]);
      basic_3d.set_model_texture_filename(args[2]);
   }
   basic_3d.initialize();

   framework.register_and_activate_screen("basic_3d", &basic_3d);

   framework.run_loop();
   return 0;
}


