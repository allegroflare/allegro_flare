



#include <allegro_flare/allegro_flare.h>




class Project : public UIScreen
{
public:
   UIButton *launch_button;

   Project(Display *display)
      : UIScreen(display)
      , launch_button(NULL)
   {
      draw_focused_outline = false;

      launch_button = new UIButton(this, 300, 200, 200, 100, "launch a window!");

      new UIFramedWindow(this, 200, 200, 300, 200);
      new UIFramedWindow(this, 280, 300, 100, 80);
      new UIFramedWindow(this, 570, 280, 400, 320);
   }
   void primary_timer_func() override
   {
      UIScreen::primary_timer_func();
      //UIFamilyGut
      /*
      for (unsigned i=0; i<family.children.size(); i++)
      {
         if (family.children[i]->delete_me == true)
            delete family.children[i--];
      }
      */
   }
   void on_message(UIWidget *sender, std::string message) override
   {
      if (sender == launch_button)
      {
         UIFramedWindow *window = new UIFramedWindow(this,
               random_int(-100, -100), random_int(-100, 100),
               random_int(200, 400), random_int(150, 300));
         window->place.position += vec2d(this->place.size.x/2, this->place.size.y/2);
      }
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




