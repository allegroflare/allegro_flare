#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <cstdint>


namespace AllegroFlare
{
   class VirtualControls
   {
   public:
      static constexpr uint32_t BUTTON_UP = 1;
      static constexpr uint32_t BUTTON_DOWN = 2;
      static constexpr uint32_t BUTTON_LEFT = 3;
      static constexpr uint32_t BUTTON_RIGHT = 4;
      static constexpr uint32_t BUTTON_A = 5;
      static constexpr uint32_t BUTTON_B = 6;
      static constexpr uint32_t BUTTON_X = 7;
      static constexpr uint32_t BUTTON_Y = 8;
      static constexpr uint32_t BUTTON_START = 9;
      static constexpr uint32_t BUTTON_RIGHT_BUMPER = 10;
      static constexpr uint32_t BUTTON_LEFT_BUMPER = 11;
      static constexpr uint32_t PRIMARY_STICK = 0;
      static constexpr uint32_t SECONDARY_STICK = 1;

   private:
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

   protected:


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



