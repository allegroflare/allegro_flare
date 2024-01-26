#include <allegro5/allegro.h>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/GraphicsPipelines/Basic3D/Scene.hpp>


class Basic3DScene : public AllegroFlare::Screens::Base
{
public:
   AllegroFlare::BitmapBin *bitmap_bin;
   AllegroFlare::ModelBin *model_bin;
   AllegroFlare::GraphicsPipelines::Basic3D::Scene scene;
   AllegroFlare::Camera3D *camera;

private:
   bool initialized;

public:
   Basic3DScene()
      : AllegroFlare::Screens::Base("Basic3DScene")
      , bitmap_bin(nullptr)
      , model_bin(nullptr)
      , scene()
      , camera(nullptr)
      , initialized(false)
   {};

   void initialize()
   {
      // Setup
      scene.set_bitmap_bin(bitmap_bin);
      scene.set_model_bin(model_bin);
      scene.initialize();
      camera = &scene.get_camera_ref();

      initialized = true;
   }

   void add_entity(std::string obj, std::string tex)
   {
      scene.add_entity(obj, tex);
   }

   virtual void primary_timer_func() override
   {
      // Update
      camera->spin += 0.01;

      // Render
      scene.render();
   }
};


int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=1; i<argc; i++) args.push_back(argv[i]);

   // init AllegroFlare
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();
   framework.get_bitmap_bin_ref().set_full_path("/");
   framework.get_model_bin_ref().set_full_path("/");

   Basic3DScene basic_3d;
   std::string obj = "foo.obj";
   std::string tex = "foo.png";
   if (args.size() == 2)
   {
      obj = args[0];
      tex = args[1];
   }
   basic_3d.bitmap_bin = &framework.get_bitmap_bin_ref();
   basic_3d.model_bin = &framework.get_model_bin_ref();
   basic_3d.initialize();
   basic_3d.add_entity(obj, tex);

   framework.register_and_activate_screen("basic_3d_scene", &basic_3d);

   framework.run_loop();
   return 0;
}


