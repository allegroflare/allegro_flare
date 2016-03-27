


#include <allegro_flare/allegro_flare.h>



class Project : public FGUIScreen
{
public:
   Project(Display *display)
      : FGUIScreen(display)
   {
      FGUITextList *text_list = new FGUITextList(this, 500, 300, 300);
         text_list->add_item("Carrots");
         text_list->add_item("Veggies");
         text_list->add_item("Hamburgers");
         text_list->add_item("Pizza");
         text_list->add_item("Tortillias");
   }
};



int main(int argc, char **argv)
{
   af::initialize();
   Display *display = af::create_display(1100, 700);
   Project *project = new Project(display);
   af::run_loop();
   return 0;
}



