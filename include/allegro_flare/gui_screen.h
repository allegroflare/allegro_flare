#ifndef __UI_WIDGET_SCREEN_HEADER
#define __UI_WIDGET_SCREEN_HEADER




#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <allegro_flare/widget.h>
#include <AllegroFlare/Motion.hpp>
#include <allegro_flare/screen.h>




class UIScreen : public Screen, public UIWidget
{
public:
   bool draw_focused_outline;
   ALLEGRO_COLOR focused_outline_color;
   bool use_joystick_as_mouse;
   // here are some ideas:
   // bool esc_key_unfocuses_all_widgets
   // bool use_joystick_as_mouse_cursor
   // bool allow_tab_to_traverse_widgets

   UIScreen(Display *display);

   // for the builder
   void primary_timer_func();
   using UIWidget::mouse_axes_func;
   void mouse_axes_func();
   void mouse_down_func();
   void mouse_up_func();
   void key_down_func();
   void key_up_func();
   void key_char_func();
   void joy_up_func();
   void joy_down_func();
   void joy_axis_func();

   // for the people
   virtual void on_draw();
   virtual void on_draw_after_children();
};




#endif
