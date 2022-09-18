#include <AllegroFlare/Frameworks/Full.hpp>
#include <WickedDemos/FunzDemo.hpp>


int main(int argc, char **argv)
{
   FunzDemo::run();

   //std::vector<std::string> args;
   //// parse the args into args
   //std::string demo_to_pick = "funz";
   //for (int i=0; i<argc; i++) args.push_back(argv[i]);
   //if (args.size() >= 2) demo_to_pick = args[1];

   //AllegroFlare::ScreenManager screens;
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   //AllegroFlare::Display *display = framework.create_display(1920/3*4, 1080/3*4, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);

   //AllegroFlare::Screen *project = nullptr;

   //std::cout << "*** Starting " << demo_to_pick << " demo ***" << std::endl;


   //if (demo_to_pick == "funz")
   //{
   FunzDemo *funz_demo = new FunzDemo(&framework, framework.get_primary_display());
   funz_demo->initialize();

   framework.register_screen("funz_demo", funz_demo);
   framework.activate_screen("funz_demo");


   //}
   //else if (demo_to_pick == "original")
   //{
      ////OriginalDemo *demo = new OriginalDemo(display);
      ////demo->initialize();
      ////project = demo;
   //}
   //else
   //{
      ////OriginalDemo *demo = new OriginalDemo(display);
      ////demo->initialize();
      ////project = demo;
   //}

	framework.run_loop();

   framework.unregister_screen(funz_demo);
   delete funz_demo;

	return 0;
}


