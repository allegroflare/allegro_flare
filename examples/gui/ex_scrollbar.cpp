


#include <allegro_flare/allegro_flare.h>





class Project : public FGUIScreen
{
public:
   FGUIText *position_text;
   FGUIScrollBar *scrollbar;
   Project(Display *display)
      : FGUIScreen(display)
      , position_text(NULL)
      , scrollbar(NULL)
   {
      this->draw_focused_outline = false;

      scrollbar = new FGUIScrollBar(this, 200, 200, 20, 200);

      position_text = new FGUIText(this, 250, display->height()/2, "(position)");
   }
   void on_timer() override
   {
      position_text->set_text(tostring(scrollbar->get_position()));
   }
};





int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display();
   Project *proj = new Project(display);
   Framework::run_loop();
   return 0;
}




