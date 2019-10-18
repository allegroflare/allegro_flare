



#include <allegro_flare/allegro_flare.h>




using namespace allegro_flare;
using namespace AllegroFlare;



class ExVersionProject : public Screen
{
public:
   ExVersionProject() : Screen()
   {}
   void primary_timer_func() override
   {
      std::string allegro_version = std::string("Allegro ") + Framework::get_allegro_version();
      std::string allegro_flare_version = std::string("AllegroFlare ") + Framework::get_version();

      BitmapObject(Framework::bitmap("allegro_flare_logo-04.png"))
         .position(display->center(), display->middle()-30)
         .align(0.5, 1.0)
         .scale(1.4)
         .draw();

      TextObject(allegro_flare_version)
         .font(Framework::font("DroidSans.ttf 80"))
         .color(color::black)
         .position(display->center(), display->middle()+70)
         .align(0.5, 1.0)
         .draw();

      TextObject(allegro_version)
         .font(Framework::font("DroidSans.ttf 30"))
         .color(color::black)
         .position(display->center(), display->middle()+70)
         .align(0.5, 0.0)
         .draw();
   }
};




int main(int c, char **v)
{
   ExVersionProject project = ExVersionProject();
   Framework::run_loop();
   return 0;
}




