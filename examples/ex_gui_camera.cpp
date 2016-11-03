



#include <allegro_flare/allegro_flare.h>




class ExGUICamera : public UIScreen
{
public:
   UICamera *camera;
   UIButton *reset_camera_button;
   UIButton *button1, *button2, *button3, *button4;
   UIButton *zoom_in_button, *zoom_out_button;
   ExGUICamera(Display *display)
      : UIScreen(display)
      , camera(new UICamera(this, 0, 0, 1, 1))
      , reset_camera_button(new UIButton(this, 300, 200, 120, 50, "reset camera"))
      , button1(new UIButton(camera, 200, 100, 120, 50, "UP"))
      , button2(new UIButton(camera, 800, 800, 120, 50, "DOWN"))
      , button3(new UIButton(camera, 600, 300, 120, 50, "LEFT"))
      , button4(new UIButton(camera, 500, 500, 120, 50, "RIGHT"))
      , zoom_in_button(new UIButton(camera, 400, 500, 120, 50, "ZOOM +"))
      , zoom_out_button(new UIButton(camera, 900, 500, 120, 50, "ZOOM -"))
   {}
   void on_message(UIWidget *sender, std::string message) override
   {
      if (sender == reset_camera_button)
      {
         camera->place.position = vec2d(0, 0);
         camera->place.scale = vec2d(1, 1);
      }
      else if (sender == button1) camera->place.position.y -= 10;
      else if (sender == button2) camera->place.position.y += 10;
      else if (sender == button3) camera->place.position.x -= 10;
      else if (sender == button4) camera->place.position.x += 10;
      else if (sender == zoom_in_button) camera->place.scale *= 1.1;
      else if (sender == zoom_out_button) camera->place.scale *= 0.9;
   }
};




int main(int, char**)
{
   Framework::initialize();
   Display *display = Framework::create_display(1600, 900);
   ExGUICamera ex_gui_camera = ExGUICamera(display);
   Framework::run_loop();
   return 0;
}




