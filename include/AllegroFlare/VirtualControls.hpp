#pragma once


#include <AllegroFlare/Vec2D.hpp>


namespace AllegroFlare
{
   class VirtualControls
   {
   private:
      static int BUTTON_UP;
      static int BUTTON_DOWN;
      static int BUTTON_LEFT;
      static int BUTTON_RIGHT;
      static int BUTTON_A;
      static int BUTTON_B;
      static int BUTTON_X;
      static int BUTTON_Y;
      static int BUTTON_START;
      static int BUTTON_RIGHT_BUMPER;
      static int BUTTON_LEFT_BUMPER;
      static int PRIMARY_STICK;
      static int SECONDARY_STICK;
      bool right_button_pressed;
      bool left_button_pressed;
      bool up_button_pressed;
      bool down_button_pressed;
      bool a_button_pressed;
      bool b_button_pressed;
      bool x_button_pressed;
      bool y_button_pressed;
      bool left_bumper_pressed;
      bool right_bumper_pressed;
      bool start_button_pressed;
      AllegroFlare::vec2d primary_stick_position;
      AllegroFlare::vec2d secondary_stick_position;

   public:
      VirtualControls();
      ~VirtualControls();

      void set_right_button_pressed(bool right_button_pressed);
      void set_left_button_pressed(bool left_button_pressed);
      void set_up_button_pressed(bool up_button_pressed);
      void set_down_button_pressed(bool down_button_pressed);
      void set_a_button_pressed(bool a_button_pressed);
      void set_b_button_pressed(bool b_button_pressed);
      void set_x_button_pressed(bool x_button_pressed);
      void set_y_button_pressed(bool y_button_pressed);
      void set_left_bumper_pressed(bool left_bumper_pressed);
      void set_right_bumper_pressed(bool right_bumper_pressed);
      void set_start_button_pressed(bool start_button_pressed);
      void set_primary_stick_position(AllegroFlare::vec2d primary_stick_position);
      void set_secondary_stick_position(AllegroFlare::vec2d secondary_stick_position);
      static int get_BUTTON_UP();
      static int get_BUTTON_DOWN();
      static int get_BUTTON_LEFT();
      static int get_BUTTON_RIGHT();
      static int get_BUTTON_A();
      static int get_BUTTON_B();
      static int get_BUTTON_X();
      static int get_BUTTON_Y();
      static int get_BUTTON_START();
      static int get_BUTTON_RIGHT_BUMPER();
      static int get_BUTTON_LEFT_BUMPER();
      static int get_PRIMARY_STICK();
      static int get_SECONDARY_STICK();
      bool get_right_button_pressed() const;
      bool get_left_button_pressed() const;
      bool get_up_button_pressed() const;
      bool get_down_button_pressed() const;
      bool get_a_button_pressed() const;
      bool get_b_button_pressed() const;
      bool get_x_button_pressed() const;
      bool get_y_button_pressed() const;
      bool get_left_bumper_pressed() const;
      bool get_right_bumper_pressed() const;
      bool get_start_button_pressed() const;
      AllegroFlare::vec2d get_primary_stick_position() const;
      AllegroFlare::vec2d get_secondary_stick_position() const;
      void clear();
   };
}



