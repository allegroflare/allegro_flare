#pragma once


#include <allegro5/allegro.h>
#include <cstdint>
#include <vector>


namespace AllegroFlare
{
   class SuspendedKeyboardState
   {
   private:
      ALLEGRO_KEYBOARD_STATE initial_keyboard_state;
      ALLEGRO_KEYBOARD_STATE subsequent_keyboard_state;
      bool initial_keyboard_state_is_captured;
      bool subsequent_keyboard_state_is_captured;
      bool keyboard_state_changes_are_calculated;
      std::vector<uint32_t> keys_pressed;
      std::vector<uint32_t> keys_released;

   protected:


   public:
      SuspendedKeyboardState();
      ~SuspendedKeyboardState();

      bool get_initial_keyboard_state_is_captured() const;
      bool get_subsequent_keyboard_state_is_captured() const;
      bool get_keyboard_state_changes_are_calculated() const;
      void reset();
      std::vector<uint32_t> get_keys_pressed();
      std::vector<uint32_t> get_keys_released();
      std::vector<uint32_t> get_keys_pressed_in_initial_keyboard_state();
      std::vector<uint32_t> get_keys_pressed_in_subsequent_keyboard_state();
      void capture_initial_keyboard_state();
      void capture_subsequent_keyboard_state();
      void calculate_keyboard_state_changes();
   };
}



