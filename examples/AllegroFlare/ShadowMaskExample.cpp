



#include <AllegroFlare/Vec2D.hpp>




class ShadowMaskExample : public Screen
{
public:
   AllegroFlare::ShadowMask shadow_mask;
   AllegroFlare::Vec2 mouse;

   ShadowMaskExample(Display *display)
      : AllegroFlare::Screen(display)
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
   ExShadowMask *proj = new ShadowMaskExample(display);
   Framework::run_loop();
   return 0;
}





