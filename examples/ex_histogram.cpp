



#include <allegro_flare/allegro_flare.h>




using namespace allegro_flare;
using namespace AllegroFlare;



class MyProject : public Screen
{
public:
   MyProject(Display *display) : Screen(display) {}

   void primary_timer_func() override
   {
      al_draw_bitmap(Framework::bitmap("pun_dog.jpg"), 125, 150, 0);

      al_draw_filled_rectangle(750-10-25, 200-10, 1200+10-25, 200+300+10, color::gray);	
      draw_histogram(Framework::bitmap("pun_dog.jpg"), 750-25, 200, 450, 300, color::white);
   }
};




int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display();
   MyProject *proj = new MyProject(display);
   Framework::run_loop();
   return 0;
}




