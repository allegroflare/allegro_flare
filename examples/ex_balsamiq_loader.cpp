



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
      load_layout();
   }
   void load_layout()
   {
      if (balsamiq) delete balsamiq;

      balsamiq = new UIWidget(this, "BalsamiqLayoutRoot", new UISurfaceAreaBox(0, 0, 0, 0));
      BalsamiqLayoutLoader loader;
      loader.load_file(balsamiq, "data/layouts/layout2.json");
   }
   void on_message(UIWidget *sender, std::string message)
   {
      std::cout << "Click!" << std::endl;
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




