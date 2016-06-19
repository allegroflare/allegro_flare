



#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/gui/layout_loaders/balsamiq_layout_loader.h>




class Project : public UIScreen
{
public:
   UIWidget *balsamiq;
   Project(Display *display)
      : UIScreen(display)
      , balsamiq(nullptr)
   {
      BalsamiqLayoutLoader loader;
      loader.load_file(this, "data/tests/layouts/balsamiq_layout.json");
   }
};




int main(int a, char **c)
{
   Framework::initialize();
   Display *display = Framework::create_display(800, 600);
   Project p = Project(display);
   Framework::run_loop();
   return 0;
}




