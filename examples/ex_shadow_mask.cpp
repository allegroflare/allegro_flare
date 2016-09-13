



#include <allegro_flare/allegro_flare.h>




class ExShadowMask : public Screen
{
public:
   ShadowMask shadow_mask;
   vec2d mouse;

   ExShadowMask(Display *display)
      : Screen(display)
      , shadow_mask(display->width(), display->height(), Framework::bitmap("light_gradient.jpg"))
      , mouse(200, 200)
   {}
   void primary_timer_func() override
   {
      shadow_mask.clear_points();
      shadow_mask.add_point(mouse.x, mouse.y);
      shadow_mask.add_point(600, 300);
      shadow_mask.add_point(200, 500);

      al_draw_rectangle(200, 200, 340, 280, color::red, 6.0);
      shadow_mask.draw();
   }
   void mouse_axes_func() override
   {
      mouse.x = Framework::current_event->mouse.x;
      mouse.y = Framework::current_event->mouse.y;
   }
};




int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display();
   ExShadowMask *proj = new ExShadowMask(display);
   Framework::run_loop();
   return 0;
}




