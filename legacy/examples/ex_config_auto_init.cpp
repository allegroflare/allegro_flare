

#include <allegro_flare/allegro_flare.h>


using namespace allegro_flare;


class Project : public Screen
{
public:
   Project() : Screen()
   {}
   void primary_timer_func() override
   {
      TextObject("Display auto-created")
         .font(Framework::font("DroidSans.ttf 30"))
         .color(AllegroFlare::color::black)
         .position(display->center(), display->middle()-50)
         .align(0.5, 1.0)
         .draw();

      TextObject(get_screen_dimentions_str())
         .font(Framework::font("DroidSans.ttf 80"))
         .color(AllegroFlare::color::black)
         .position(display->center(), display->middle()-40)
         .align(0.5, 0.0)
         .draw();
   }
   std::string get_screen_dimentions_str()
   {
      int width = al_get_display_width(display->al_display);
      int height = al_get_display_height(display->al_display);
      std::stringstream ss;
      ss << width << " x " << height;
      return ss.str();
   }
};


int main(int c, char **v)
{
   Project project = Project();
   Framework::run_loop();
   return 0;
}


