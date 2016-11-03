



#include <allegro_flare/allegro_flare.h>




class ExGUICamera : public UIScreen
{
public:
   UICamera *camera;
   UIButton *button1, *button2, *button3, *button4;
   ExGUICamera(Display *display)
      : UIScreen(display)
      , camera(new UICamera(this, 0, 0, 1, 1))
      , button1(new UIButton(camera, 200, 100, 120, 50, "button1"))
      , button2(new UIButton(camera, 800, 800, 120, 50, "button2"))
      , button3(new UIButton(camera, 600, 300, 120, 50, "button3"))
      , button4(new UIButton(camera, 500, 500, 120, 50, "button4"))
   {}
};




int main(int, char**)
{
   Framework::initialize();
   Display *display = Framework::create_display(1600, 900);
   ExGUICamera ex_gui_camera = ExGUICamera(display);
   Framework::run_loop();
   return 0;
}




