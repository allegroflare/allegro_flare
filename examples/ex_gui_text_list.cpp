



#include <allegro_flare/allegro_flare.h>




using namespace allegro_flare;



class Project : public UIScreen
{
public:
   Project(Display *display)
      : UIScreen(display)
   {
      UITextList *text_list = new UITextList(this, 500, 300, 300);
      text_list->add_item("Carrots");
      text_list->add_item("Veggies");
      text_list->add_item("Hamburgers");
      text_list->add_item("Pizza");
      text_list->add_item("Tortillias");
   }
};




int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display(1100, 700);
   Project *project = new Project(display);
   Framework::run_loop();
   return 0;
}




