

//#include <allegro_flare/allegro_flare.h>
//#include <allegro5/allegro_opengl.h>

//#include <allegro_flare/cubemap.h>

// NOTE:
// this is a great article providing tips on improving shadow mapping appearance and processing
// https://docs.microsoft.com/en-us/windows/win32/dxtecharts/common-techniques-to-improve-shadow-depth-maps

//using namespace allegro_flare;
//using namespace AllegroFlare;


//#include <Wicked/Camera3.hpp>
#include <Wicked/ShadowCastingLight.hpp>
#include <Wicked/Light.hpp>
#include <Wicked/StandardCompoundShader.hpp>
#include <Wicked/Entity.hpp>
#include <Wicked/SceneRenderer.hpp>

#include <WickedDemos/EntityFactory.hpp>
//#include <WickedDemos/OriginalDemo.hpp>
#include <WickedDemos/FunzDemo.hpp>



int main(int argc, char **argv)
{
   std::vector<std::string> args;
   // parse the args into args
   std::string demo_to_pick = "funz";
   for (int i=0; i<argc; i++) args.push_back(argv[i]);
   if (args.size() >= 2) demo_to_pick = args[1];

   AllegroFlare::ScreenManager screens;
   AllegroFlare::Framework framework(&screens);
   framework.initialize();
   AllegroFlare::Display *display = framework.create_display(1920/3*4, 1080/3*4, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);

   AllegroFlare::Screen *project = nullptr;

   std::cout << "*** Starting " << demo_to_pick << " demo ***" << std::endl;


   if (demo_to_pick == "funz")
   {
      FunzDemo *demo = new FunzDemo(&framework, display);
      demo->initialize();
      screens.add(demo);

      project = demo;
   }
   else if (demo_to_pick == "original")
   {
      //OriginalDemo *demo = new OriginalDemo(display);
      //demo->initialize();
      //project = demo;
   }
   else
   {
      //OriginalDemo *demo = new OriginalDemo(display);
      //demo->initialize();
      //project = demo;
   }

	framework.run_loop();
   screens.remove(project);

   delete project;
	return 0;
}



