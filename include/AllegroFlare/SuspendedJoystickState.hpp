#pragma once


#include <allegro5/allegro.h>
#include <cstdint>
#include <map>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   class SuspendedJoystickState
   {
   private:
      ALLEGRO_JOYSTICK* joystick;
      ALLEGRO_JOYSTICK_STATE initial_joystick_state;
      std::vector<int> initial_joystick_state_stick_and_axis_count;
      int initial_joystick_state_num_buttons;
      ALLEGRO_JOYSTICK_STATE subsequent_joystick_state;
      std::vector<int> subsequent_joystick_state_stick_and_axis_count;
      int subsequent_joystick_state_num_buttons;
      bool initial_joystick_state_is_captured;
      bool subsequent_joystick_state_is_captured;
      bool joystick_state_changes_are_calculated;
      std::vector<uint32_t> buttons_pressed;
      std::vector<uint32_t> buttons_released;
      std::map<std::pair<int, int>, std::pair<float, float>> sticks_moved;

   protected:


   public:
      SuspendedJoystickState();
      ~SuspendedJoystickState();

      ALLEGRO_JOYSTICK* get_joystick() const;
      bool get_initial_joystick_state_is_captured() const;
      bool get_subsequent_joystick_state_is_captured() const;
      bool get_joystick_state_changes_are_calculated() const;
      void set_joystick(ALLEGRO_JOYSTICK* joystick=nullptr);
      bool joystick_exists();
      void reset();
      std::vector<uint32_t> get_buttons_pressed_in_initial_joystick_state();
      std::vector<uint32_t> get_buttons_pressed_in_subsequent_joystick_state();
      std::map<std::pair<int, int>, std::pair<float, float>> get_sticks_moved_in_initial_joystick_state();
      std::map<std::pair<int, int>, std::pair<float, float>> get_sticks_moved_in_subsequent_joystick_state();
      std::vector<uint32_t> get_buttons_pressed();
      std::vector<uint32_t> get_buttons_released();
      std::map<std::pair<int, int>, std::pair<float, float>> get_sticks_moved();
      void capture_initial_joystick_state();
      void capture_subsequent_joystick_state();
      void calculate_joystick_state_changes();
   };
}



