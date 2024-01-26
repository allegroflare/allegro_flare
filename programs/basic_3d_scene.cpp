#include <allegro5/allegro.h>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/GraphicsPipelines/Basic3D/Scene.hpp>
//#include <allegro5/allegro_image.h>
//#include <AllegroFlare/Model3DObjLoader.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>
//#include <AllegroFlare/Screens/Base.hpp>
//#include <AllegroFlare/Model3D.hpp>
//#include <AllegroFlare/Camera3D.hpp>
//#include <AllegroFlare/Placement3D.hpp>
//#include <cmath>
//#include <iostream>
//#include <cmath>


class Basic3DScene : public AllegroFlare::Screens::Base
{
public:
   AllegroFlare::BitmapBin *bitmap_bin;
   AllegroFlare::ModelBin  *model_bin;

private:
   AllegroFlare::GraphicsPipelines::Basic3D::Scene scene;
   bool initialized;

public:
   Basic3DScene()
      : AllegroFlare::Screens::Base("Basic3DScene")
      , bitmap_bin(nullptr)
      , model_bin(nullptr)
      , scene()
      , initialized(false)
   {};

   void initialize()
   {
      scene.set_bitmap_bin(bitmap_bin);
      scene.set_model_bin(model_bin);
      scene.initialize();
      initialized = true;
   }

   virtual void primary_timer_func() override
   {
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

   Basic3DScene basic_3d;
   if (args.size() == 2)
   {
      //basic_3d.set_model_obj_filename(args[0]);
      //basic_3d.set_model_texture_filename(args[1]);
   }
   basic_3d.bitmap_bin = &framework.get_bitmap_bin_ref();
   basic_3d.model_bin = &framework.get_model_bin_ref();
   basic_3d.initialize();

   framework.register_and_activate_screen("basic_3d_scene", &basic_3d);

   framework.run_loop();
   return 0;
}



