


#include <allegro_flare/allegro_flare.h>



/*{


framed_window_ex.cpp
====================

simple example program of how a framed window might be implemented


}*/





class Project : public FGUIScreen
{
public:
   FGUIButton *launch_button;

   Project(Display *display)
      : FGUIScreen(display)
      , launch_button(NULL)
   {
      draw_focused_outline = false;

      launch_button = new FGUIButton(this, 300, 200, 200, 100, "launch a window!");

      new FGUIFramedWindow(this, 200, 200, 300, 200);
      new FGUIFramedWindow(this, 280, 300, 100, 80);
      new FGUIFramedWindow(this, 570, 280, 400, 320);
   }
   void primary_timer_func() override
   {
      FGUIScreen::primary_timer_func();
      for (unsigned i=0; i<family.children.size(); i++)
      {
         if (family.children[i]->delete_me == true)
            delete family.children[i--];
      }
   }
   void on_message(FGUIWidget *sender, std::string message) override
   {
      if (sender == launch_button)
      {
         FGUIFramedWindow *window = new FGUIFramedWindow(this,
               random_int(-100, -100), random_int(-100, 100),
               random_int(200, 400), random_int(150, 300));
         window->place.position += vec2d(this->place.size.x/2, this->place.size.y/2);
      }
   }

};




int main(int argc, char **argv)
{
   af::initialize();
   Display *display = af::create_display();
   Project *proj = new Project(display);
   af::run_loop();
   return 0;
}




