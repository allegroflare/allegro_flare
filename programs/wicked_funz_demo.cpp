#include <AllegroFlare/Frameworks/Full.hpp>
#include <WickedDemos/FunzDemo.hpp>


int main(int argc, char **argv)
{
   FunzDemo::run();

   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   FunzDemo *funz_demo = new FunzDemo(&framework, framework.get_primary_display());
   funz_demo->initialize();

   framework.register_screen("funz_demo", funz_demo);
   framework.activate_screen("funz_demo");

	framework.run_loop();

   framework.unregister_screen(funz_demo);
   delete funz_demo;

	return 0;
}


