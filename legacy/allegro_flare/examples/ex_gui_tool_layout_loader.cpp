



#include <allegro_flare/allegro_flare.h>

#include <allegro_flare/gui_tool_layout_loader.h>
#include <AllegroFlare/UsefulPHP.hpp>




using namespace allegro_flare;
using namespace AllegroFlare;



class ExGUIToolLayoutLoader : public UIScreen
{
public:
   ExGUIToolLayoutLoader(Display *display)
      : UIScreen(display)
   {
      std::string contents = php::file_get_contents("data/layouts/gui_tool_layout1.json");
      GUIToolLayoutLoader layout_loader(this, contents);
      layout_loader.load_file();
   }
};




int main(int, char**)
{
   Framework::initialize();
   Display *display = Framework::create_display(1600, 900);
   ExGUIToolLayoutLoader ex_gui_camera = ExGUIToolLayoutLoader(display);
   Framework::run_loop();
   return 0;
}




