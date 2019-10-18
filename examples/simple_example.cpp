//#include <allegro_flare/allegro_flare.h>
#include <AllegroFlare/Screen.hpp>

using namespace AllegroFlare;

class SimpleExample : public Screen
{
public:
    SimpleExample(Display *display) : Screen(display) {}
    void primary_timer_func() override
    {
        al_draw_filled_rectangle(300, 400, 200, 100, color::chartreuse);
    }
}

int main(int argc, char **argv)
{
    Framework::initialize(); // initialize all things AllegroFlare
    Display *display = Framework::create_display(800, 600); // creates a new Window
    SimpleExample *simple_example = new SimpleExample(display); // creates a new instance of your app
    Framework::run_loop(); // run the AllegroFlare framework
}
