



#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/simple_notification_screen.h>

//using namespace UIGlobal;




#define FOR(container) for (unsigned i=0; i<container.size(); i++)




class JoystickExample : public UIScreen
{
private:
   SimpleNotificationScreen *notification_screen;
   ALLEGRO_FONT *font;

   UITextInput *text_input;
   UIButton *submit_button;

//   bool joystick_navigation;
//   bool keyboard_navigation;

   //bool hide_mouse_cursor_on_widget_jump; // has some buggy behavior
   //bool joy_as_mouse;
   //float joy_vertical_pos;
   //float joy_horizontal_pos;

   //int last_focused_ancestor;

public:
   JoystickExample(Display *display)
      : UIScreen(display)
      , notification_screen(NULL)
      , font(Framework::font("DroidSerif.ttf 20"))
      //, last_focused_ancestor(0)
      //, joy_as_mouse(false)
      //, joy_vertical_pos(0)
      //, joy_horizontal_pos(0)
      //, hide_mouse_cursor_on_widget_jump(false)
      , text_input(NULL)
      , submit_button(NULL)
   {
      //UIScreen::draw_focused_outline = false;
      notification_screen = new SimpleNotificationScreen(display, Framework::font("DroidSerif.ttf 16"));

      float button_x = 800/2;
      float button_y = 200;
      float button_spacing = 60;
      int cur = 0;
      new UIButton(this, button_x, button_y+button_spacing*cur++, 170, 50, "Button1");
      new UIButton(this, button_x, button_y+button_spacing*cur++, 170, 50, "Button2");
      new UIButton(this, button_x, button_y+button_spacing*cur++, 170, 50, "Button3");
      new UIButton(this, button_x, button_y+button_spacing*cur++, 170, 50, "Button4");
      new UIButton(this, button_x, button_y+button_spacing*cur++, 170, 50, "Button5");


      text_input = new UITextInput(this, 400, 500, 300, 45, "This is a text input");
      submit_button = new UIButton(this, 400+170+30, 500, 80, 50, "send");


      new UITextArea(this, 800, 320, 200, 300, "This is a textarea");

      new UIScaledText(this, 60, 100, "Widget Selection Example");

      new UIText(this, 20, display->height()-70-30, "Use the mouse OR joystick to move the mouse cursor.");
      new UIText(this, 20, display->height()-40-30, "Press the joystick SHOULDER BUTTONS or keyboard's TAB to jump to the next UI widget.");
      new UIText(this, 20, display->height()-40, "(you can also hot-swap the joystick)");

      //std::cout << "count_complete_lineage: " << get_num_ancestors() << std::endl;
   }
   //void on_draw() override
   //{
   //   UIScreen::on_draw();
//
//      if (joy_as_mouse) al_draw_filled_circle(10, 10, 3, color::yellow);
//   }
   void notification(std::string notification)
   {
      notification_screen->spawn_notification(notification);
   }
   void on_message(UIWidget *sender, std::string message) override
   {
      if (sender == submit_button)
      {
         notification_screen->spawn_notification(text_input->get_text());
      }
   }


   //void joy_config_func() override
   //{
   //   UIScreen::joy_config_func();
   //
   //   std::cout << "joy config change" << std::endl;
   //   notification_screen->spawn_notification("joystick configuration change");
   //}

   //void mouse_axes_func() override
   //{
   //   UIScreen::mouse_axes_func();

      //if (hide_mouse_cursor_on_widget_jump)
      //{
      //   al_show_mouse_cursor(display->display);
      //}
   //}
   //void _joy_down_func()
   //{
   //   UIScreen::joy_down_func();

      //std::cout << "joy button " << Framework::current_event->joystick.button << std::endl;

      //if (Framework::current_event->joystick.button ==  5) jump_focus_to_next_widget(); // XBOX Controller shoulder trigger button
      //if (Framework::current_event->joystick.button ==  4) jump_focus_to_previous_widget(); // XBOX Controller shoulder trigger button
/*
      if (Framework::current_event->joystick.button ==  0)
      {
         // does only 1 button
         FOR (children.children)
         {
            if (children.children[i]->is_mouse_over())
            {
               children.children[i]->set_as_focused();
               if (children.children[i]->attr.matches("UI_WIDGET_TYPE", "UIButton"))
               {
                  UIButton *button = static_cast<UIButton *>(children.children[i]);
                  button->on_click();
               }
            }
         }
      }
*/

      /*
      // hmm... doesn't seem to work:

      ALLEGRO_EVENT ev;
      ev.type = ALLEGRO_EVENT_KEY_DOWN;
      ev.any.timestamp = al_get_time();
      ev.any.type = ALLEGRO_EVENT_KEY_DOWN;
      ev.any.source = &Framework::_user_event_src_for_faking_events;
      ev.keyboard.type = ALLEGRO_EVENT_KEY_DOWN;
      ev.keyboard.keycode = ALLEGRO_KEY_ESCAPE;
      ev.keyboard.display = al_get_current_display();
      al_emit_user_event(&Framework::_user_event_src_for_faking_events , &ev , NULL);
      */
   //}
   //void joy_axis_func() override
   //{
   //   UIScreen::joy_axis_func();

      //use_joystick_as_mouse = true;
      //if (Framework::current_event->joystick.axis == 0) joy_horizontal_pos = Framework::current_event->joystick.pos;
      //if (Framework::current_event->joystick.axis == 1) joy_vertical_pos = Framework::current_event->joystick.pos;


      //if (hide_mouse_cursor_on_widget_jump) al_show_mouse_cursor(display->display);
   //}
   /*
   void key_char_func() override
   {
      UIScreen::key_char_func();
   }
   void key_down_func() override
   {
      UIScreen::key_down_func();
   }
   */
};




int main(int argc, char *argv[])
{
   Framework::initialize();

   //Display *display = Framework::create_display(1920, 1080, true);
   Display *display = Framework::create_display(1000, 700);
   JoystickExample *joystick_ex = new JoystickExample(display);

   Framework::run_loop();

   return 0;
}




