#pragma once


#include <allegro5/allegro.h>
#include <functional>


namespace AllegroFlare
{
   namespace Elements
   {
      class JoystickAxisWatcher
      {
      public:
         static constexpr float DEFAULT_MIN_STICK_BREAK_THRESHOLD = 0.4f;

      private:
         float axis_x;
         float axis_y;
         float min_stick_break_threshold;
         std::function<void()> on_move_cursor_up;
         std::function<void()> on_move_cursor_down;

      protected:


      public:
         JoystickAxisWatcher();
         ~JoystickAxisWatcher();

         void set_on_move_cursor_up(std::function<void()> on_move_cursor_up);
         void set_on_move_cursor_down(std::function<void()> on_move_cursor_down);
         void joy_axis_func(ALLEGRO_EVENT* ev=nullptr);
      };
   }
}



