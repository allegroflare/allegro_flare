

#include <AllegroFlare/Elements/JoystickAxisWatcher.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


JoystickAxisWatcher::JoystickAxisWatcher()
   : axis_x(0)
   , axis_y(0)
   , min_stick_break_threshold(DEFAULT_MIN_STICK_BREAK_THRESHOLD)
   , on_move_cursor_up({})
   , on_move_cursor_down({})
{
}


JoystickAxisWatcher::~JoystickAxisWatcher()
{
}


void JoystickAxisWatcher::set_on_move_cursor_up(std::function<void()> on_move_cursor_up)
{
   this->on_move_cursor_up = on_move_cursor_up;
}


void JoystickAxisWatcher::set_on_move_cursor_down(std::function<void()> on_move_cursor_down)
{
   this->on_move_cursor_down = on_move_cursor_down;
}


void JoystickAxisWatcher::joy_axis_func(ALLEGRO_EVENT* ev)
{
   if (!(ev))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::JoystickAxisWatcher::joy_axis_func]: error: guard \"ev\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::JoystickAxisWatcher::joy_axis_func]: error: guard \"ev\" not met");
   }
   if (!((ev->type == ALLEGRO_EVENT_JOYSTICK_AXIS)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::JoystickAxisWatcher::joy_axis_func]: error: guard \"(ev->type == ALLEGRO_EVENT_JOYSTICK_AXIS)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::JoystickAxisWatcher::joy_axis_func]: error: guard \"(ev->type == ALLEGRO_EVENT_JOYSTICK_AXIS)\" not met");
   }
   //static float axis_x = 0;
   //static float axis_y = 0;

   int stick = ev->joystick.stick;
   int axis = ev->joystick.axis;
   float pos = ev->joystick.pos;

   //float min_stick_break_threshold = 0.4;

   switch (stick)
   {
      case 0: { // The primary joystick, on the left
        if (axis == 0) // horizontal axis
        {
           //if (axis_x < min_stick_break_threshold && pos >= min_stick_break_threshold) 
               //level_select_element.move_cursor_right();
           //if (axis_x > -min_stick_break_threshold && pos <= -min_stick_break_threshold) 
               //level_select_element.move_cursor_left();
           axis_x = pos;
        }
        else if (axis == 1) // vertical axis
        {
           if (axis_y < min_stick_break_threshold && pos >= min_stick_break_threshold)
           {
              //move_cursor_down();
              if (on_move_cursor_down) on_move_cursor_down();
               //level_select_element.move_cursor_down();
           }
           if (axis_y > -min_stick_break_threshold && pos <= -min_stick_break_threshold)
           {
              //move_cursor_up();
              if (on_move_cursor_up) on_move_cursor_up();
              //level_select_element.move_cursor_up();
           }

           axis_y = pos;
        }
      } break;

      case 1: { // The secondary joystick, on the right
      } break;

      case 2: { // The hat, on the left
      } break;
   }

   return;
}


} // namespace Elements
} // namespace AllegroFlare


