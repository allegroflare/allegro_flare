



#include <allegro_flare/gui_screen.h>

#include <allegro_flare/box.h>
#include <allegro_flare/allegro_flare.h>




namespace allegro_flare
{
   UIScreen::UIScreen(Display *display)
      : Screen(display)
      , UIWidget(NULL, "UIScreen", new UISurfaceAreaBox(0, 0, display->width(), display->height()))
      , draw_focused_outline(true)
      , focused_outline_color(color::dodgerblue)
      , use_joystick_as_mouse(true)
   {
      surface_area->placement.align.x = 0;
      surface_area->placement.align.y = 0;
   }




   void UIScreen::primary_timer_func()
   {
      if (use_joystick_as_mouse)
      {
         if (Framework::joystick)
         {
            float sensitivity = 8.0;

            ALLEGRO_MOUSE_STATE mouse_state;
            al_get_mouse_state(&mouse_state);

            ALLEGRO_JOYSTICK_STATE joystick_state;
            al_get_joystick_state(Framework::joystick, &joystick_state);

            // TODO:
            // right now the joystick axis to use for the mouse emulation is static,
            // this should be fixed so that an axis might be chosen by the user
            // and/or multiple joysticks could also be used
            if (joystick_state.stick[0].axis[0] != 0.0 || joystick_state.stick[0].axis[1] != 0.0)
            {
               al_set_mouse_xy(display->al_display,
                     mouse_state.x + joystick_state.stick[0].axis[0]*sensitivity,
                     mouse_state.y + joystick_state.stick[0].axis[1]*sensitivity);
            }
         }
      }

      // call the parent's usual functions

      UIWidget::primary_timer_func();
      UIWidget::draw_func();

      on_draw_after_children();
   }




   void UIScreen::mouse_axes_func()
   {
      if (Framework::current_event->mouse.display != display->al_display) return;

      float mx = Framework::current_event->mouse.x;
      float my = Framework::current_event->mouse.y;
      float mdx = Framework::current_event->mouse.dx;
      float mdy = Framework::current_event->mouse.dy;

      UIWidget::mouse_axes_func(mx, my, mdx, mdy);
   }




   void UIScreen::mouse_down_func()
   {
      if (Framework::current_event->mouse.display != display->al_display) return;
      UIWidget::mouse_down_func();
   }




   void UIScreen::mouse_up_func()
   {
      if (Framework::current_event->mouse.display != display->al_display) return;
      UIWidget::mouse_up_func();
   }




   void UIScreen::key_down_func()
   {
      if (Framework::current_event->keyboard.display != display->al_display) return;


      // these next two conditionals are for keyboard/joystick navigation of widgets

      /*
         if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_TAB)
         {
         if (Framework::key_shift) jump_focus_to_ancestor_by_delta(true);// jump_focus_to_previous_direct_descendent();
         else jump_focus_to_ancestor_by_delta(); //jump_focus_to_next_direct_descendent();
         }
         if (Framework::current_event->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
         {
         children.unfocus_all();
         al_show_mouse_cursor(display->display); // restore visibility of the cursor here
         }
         */

      UIWidget::key_down_func();
   }




   void UIScreen::key_up_func()
   {
      if (Framework::current_event->keyboard.display != display->al_display) return;
      UIWidget::key_up_func();
   }




   void UIScreen::key_char_func()
   {
      if (Framework::current_event->keyboard.display != display->al_display) return;

      UIWidget::key_char_func();
   }




   void UIScreen::joy_down_func()
   {
      /*
      // for joystick / keyboard navigation of widgets
      if (Framework::current_event->joystick.button ==  5) jump_focus_to_ancestor_by_delta(); // XBOX Controller right shoulder trigger button
      if (Framework::current_event->joystick.button ==  4) jump_focus_to_ancestor_by_delta(true); // XBOX Controller left shoulder trigger button
      */

      UIWidget::joy_down_func();
   }




   void UIScreen::joy_up_func()
   {
      //   if (Framework::current_event->keyboard.display != display->display) return;
      UIWidget::joy_up_func();
   }




   void UIScreen::joy_axis_func()
   {
      // this stuff is now polled on the timer
      // use_joystick_as_mouse = true;
      // if (Framework::current_event->joystick.axis == 0) joy_horizontal_pos = Framework::current_event->joystick.pos;
      // if (Framework::current_event->joystick.axis == 1) joy_vertical_pos = Framework::current_event->joystick.pos;

      UIWidget::joy_axis_func();
   }




   void UIScreen::on_draw() {}




   void UIScreen::on_draw_after_children() {}
}



