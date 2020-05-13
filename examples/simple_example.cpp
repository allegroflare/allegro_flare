#include <allegro5/allegro.h>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Screen.hpp>
#include <AllegroFlare/Framework.hpp>

using namespace AllegroFlare;

class SimpleExample : public Screen
{
public:
    SimpleExample(Framework &framework, Screens &screens, Display *display) : Screen(display) {}
    void primary_timer_func() override
    {
        al_draw_filled_rectangle(300, 400, 200, 100, color::chartreuse);
    }
};

int main(int argc, char **argv)
{
   Screens screens;
   Framework framework(screens);
   framework.initialize();
   Display *display = framework.create_display(800, 600);

   SimpleExample simple_example(framework, screens, display);

   framework.run_loop();
}
