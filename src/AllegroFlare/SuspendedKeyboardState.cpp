

#include <AllegroFlare/SuspendedKeyboardState.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


SuspendedKeyboardState::SuspendedKeyboardState()
   : initial_keyboard_state()
   , subsequent_keyboard_state()
   , initial_keyboard_state_is_captured(false)
   , subsequent_keyboard_state_is_captured(false)
   , keyboard_state_changes_are_calculated(false)
   , keys_pressed({})
   , keys_released({})
{
}


SuspendedKeyboardState::~SuspendedKeyboardState()
{
}


bool SuspendedKeyboardState::get_initial_keyboard_state_is_captured() const
{
   return initial_keyboard_state_is_captured;
}


bool SuspendedKeyboardState::get_subsequent_keyboard_state_is_captured() const
{
   return subsequent_keyboard_state_is_captured;
}


bool SuspendedKeyboardState::get_keyboard_state_changes_are_calculated() const
{
   return keyboard_state_changes_are_calculated;
}


void SuspendedKeyboardState::reset()
{
   initial_keyboard_state = ALLEGRO_KEYBOARD_STATE{};
   subsequent_keyboard_state = ALLEGRO_KEYBOARD_STATE{};
   initial_keyboard_state_is_captured = false;
   subsequent_keyboard_state_is_captured = false;
   keyboard_state_changes_are_calculated = false;
   keys_pressed.clear();
   keys_released.clear();
}

std::vector<uint32_t> SuspendedKeyboardState::get_keys_pressed()
{
   if (!(keyboard_state_changes_are_calculated))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::get_keys_pressed]: error: guard \"keyboard_state_changes_are_calculated\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::get_keys_pressed: error: guard \"keyboard_state_changes_are_calculated\" not met");
   }
   return keys_pressed;
}

std::vector<uint32_t> SuspendedKeyboardState::get_keys_released()
{
   if (!(keyboard_state_changes_are_calculated))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::get_keys_released]: error: guard \"keyboard_state_changes_are_calculated\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::get_keys_released: error: guard \"keyboard_state_changes_are_calculated\" not met");
   }
   return keys_released;
}

std::vector<uint32_t> SuspendedKeyboardState::get_keys_pressed_in_initial_keyboard_state()
{
   if (!(initial_keyboard_state_is_captured))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::get_keys_pressed_in_initial_keyboard_state]: error: guard \"initial_keyboard_state_is_captured\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::get_keys_pressed_in_initial_keyboard_state: error: guard \"initial_keyboard_state_is_captured\" not met");
   }
   std::vector<uint32_t> keys;
   uint32_t key_min = 0;
   for (int al_keycode=key_min; al_keycode<ALLEGRO_KEY_MAX; al_keycode++)
   {
      if (al_key_down(&initial_keyboard_state, al_keycode)) keys.push_back(al_keycode);
   }
   return keys;
}

std::vector<uint32_t> SuspendedKeyboardState::get_keys_pressed_in_subsequent_keyboard_state()
{
   if (!(subsequent_keyboard_state_is_captured))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::get_keys_pressed_in_subsequent_keyboard_state]: error: guard \"subsequent_keyboard_state_is_captured\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::get_keys_pressed_in_subsequent_keyboard_state: error: guard \"subsequent_keyboard_state_is_captured\" not met");
   }
   std::vector<uint32_t> keys;
   uint32_t key_min = 0;
   for (int al_keycode=key_min; al_keycode<ALLEGRO_KEY_MAX; al_keycode++)
   {
      if (al_key_down(&subsequent_keyboard_state, al_keycode)) keys.push_back(al_keycode);
   }
   return keys;
}

void SuspendedKeyboardState::capture_initial_keyboard_state()
{
   if (!((!initial_keyboard_state_is_captured)))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::capture_initial_keyboard_state]: error: guard \"(!initial_keyboard_state_is_captured)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::capture_initial_keyboard_state: error: guard \"(!initial_keyboard_state_is_captured)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::capture_initial_keyboard_state]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::capture_initial_keyboard_state: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_keyboard_installed()))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::capture_initial_keyboard_state]: error: guard \"al_is_keyboard_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::capture_initial_keyboard_state: error: guard \"al_is_keyboard_installed()\" not met");
   }
   al_get_keyboard_state(&initial_keyboard_state);
   initial_keyboard_state_is_captured = true;
   return;
}

void SuspendedKeyboardState::capture_subsequent_keyboard_state()
{
   if (!((!subsequent_keyboard_state_is_captured)))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::capture_subsequent_keyboard_state]: error: guard \"(!subsequent_keyboard_state_is_captured)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::capture_subsequent_keyboard_state: error: guard \"(!subsequent_keyboard_state_is_captured)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::capture_subsequent_keyboard_state]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::capture_subsequent_keyboard_state: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_keyboard_installed()))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::capture_subsequent_keyboard_state]: error: guard \"al_is_keyboard_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::capture_subsequent_keyboard_state: error: guard \"al_is_keyboard_installed()\" not met");
   }
   al_get_keyboard_state(&subsequent_keyboard_state);
   subsequent_keyboard_state_is_captured = true;
   return;
}

void SuspendedKeyboardState::calculate_keyboard_state_changes()
{
   if (!((!keyboard_state_changes_are_calculated)))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::calculate_keyboard_state_changes]: error: guard \"(!keyboard_state_changes_are_calculated)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::calculate_keyboard_state_changes: error: guard \"(!keyboard_state_changes_are_calculated)\" not met");
   }
   if (!(initial_keyboard_state_is_captured))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::calculate_keyboard_state_changes]: error: guard \"initial_keyboard_state_is_captured\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::calculate_keyboard_state_changes: error: guard \"initial_keyboard_state_is_captured\" not met");
   }
   if (!(subsequent_keyboard_state_is_captured))
   {
      std::stringstream error_message;
      error_message << "[SuspendedKeyboardState::calculate_keyboard_state_changes]: error: guard \"subsequent_keyboard_state_is_captured\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SuspendedKeyboardState::calculate_keyboard_state_changes: error: guard \"subsequent_keyboard_state_is_captured\" not met");
   }
   uint32_t key_min = 0;
   for (int al_keycode=key_min; al_keycode<ALLEGRO_KEY_MAX; al_keycode++)
   {
      if (al_key_down(&initial_keyboard_state, al_keycode) == al_key_down(&subsequent_keyboard_state, al_keycode))
      {
         // No change in key state
         continue;
      }

      // There was a change, store it
      if (al_key_down(&subsequent_keyboard_state, al_keycode)) keys_pressed.push_back(al_keycode);
      else keys_released.push_back(al_keycode);
   }
   keyboard_state_changes_are_calculated = true;
   return;
}


} // namespace AllegroFlare


