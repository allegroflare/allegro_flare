

#include <AllegroFlare/SuspendedJoystickState.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


SuspendedJoystickState::SuspendedJoystickState()
   : joystick(nullptr)
   , initial_joystick_state()
   , initial_joystick_state_stick_and_axis_count({})
   , initial_joystick_state_num_buttons(0)
   , subsequent_joystick_state()
   , subsequent_joystick_state_stick_and_axis_count({})
   , subsequent_joystick_state_num_buttons(0)
   , initial_joystick_state_is_captured(false)
   , subsequent_joystick_state_is_captured(false)
   , joystick_state_changes_are_calculated(false)
   , buttons_pressed({})
   , buttons_released({})
   , sticks_moved({})
{
}


SuspendedJoystickState::~SuspendedJoystickState()
{
}


ALLEGRO_JOYSTICK* SuspendedJoystickState::get_joystick() const
{
   return joystick;
}


bool SuspendedJoystickState::get_initial_joystick_state_is_captured() const
{
   return initial_joystick_state_is_captured;
}


bool SuspendedJoystickState::get_subsequent_joystick_state_is_captured() const
{
   return subsequent_joystick_state_is_captured;
}


bool SuspendedJoystickState::get_joystick_state_changes_are_calculated() const
{
   return joystick_state_changes_are_calculated;
}


void SuspendedJoystickState::set_joystick(ALLEGRO_JOYSTICK* joystick)
{
   if (!((!initial_joystick_state_is_captured)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::set_joystick]: error: guard \"(!initial_joystick_state_is_captured)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::set_joystick]: error: guard \"(!initial_joystick_state_is_captured)\" not met");
   }
   if (!((!subsequent_joystick_state_is_captured)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::set_joystick]: error: guard \"(!subsequent_joystick_state_is_captured)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::set_joystick]: error: guard \"(!subsequent_joystick_state_is_captured)\" not met");
   }
   this->joystick = joystick;
   return;
}

bool SuspendedJoystickState::joystick_exists()
{
   return joystick != nullptr;
}

void SuspendedJoystickState::reset()
{
   initial_joystick_state = ALLEGRO_JOYSTICK_STATE{};
   subsequent_joystick_state = ALLEGRO_JOYSTICK_STATE{};
   initial_joystick_state_is_captured = false;
   subsequent_joystick_state_is_captured = false;
   joystick_state_changes_are_calculated = false;
   buttons_pressed.clear();
   buttons_released.clear();
   sticks_moved.clear();
   return;
}

std::vector<uint32_t> SuspendedJoystickState::get_buttons_pressed_in_initial_joystick_state()
{
   if (!(initial_joystick_state_is_captured))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::get_buttons_pressed_in_initial_joystick_state]: error: guard \"initial_joystick_state_is_captured\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::get_buttons_pressed_in_initial_joystick_state]: error: guard \"initial_joystick_state_is_captured\" not met");
   }
   std::vector<uint32_t> buttons;
   int num_buttons = initial_joystick_state_num_buttons;
   for (int button_num=0; button_num<num_buttons; button_num++)
   {
      if (initial_joystick_state.button[button_num]) buttons.push_back(button_num);
   }
   return buttons;
}

std::vector<uint32_t> SuspendedJoystickState::get_buttons_pressed_in_subsequent_joystick_state()
{
   if (!(subsequent_joystick_state_is_captured))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::get_buttons_pressed_in_subsequent_joystick_state]: error: guard \"subsequent_joystick_state_is_captured\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::get_buttons_pressed_in_subsequent_joystick_state]: error: guard \"subsequent_joystick_state_is_captured\" not met");
   }
   std::vector<uint32_t> buttons;
   int num_buttons = subsequent_joystick_state_num_buttons;
   for (int button_num=0; button_num<num_buttons; button_num++)
   {
      if (subsequent_joystick_state.button[button_num]) buttons.push_back(button_num);
   }
   return buttons;
}

std::map<std::pair<int, int>, std::pair<float, float>> SuspendedJoystickState::get_sticks_moved_in_initial_joystick_state()
{
   if (!(initial_joystick_state_is_captured))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::get_sticks_moved_in_initial_joystick_state]: error: guard \"initial_joystick_state_is_captured\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::get_sticks_moved_in_initial_joystick_state]: error: guard \"initial_joystick_state_is_captured\" not met");
   }
   // Calculate the change in axes
   std::map<std::pair<int, int>, std::pair<float, float>> sticks;
   int num_sticks = initial_joystick_state_stick_and_axis_count.size();
   for (int stick_num=0; stick_num<num_sticks; stick_num++)
   {
      int num_axes = initial_joystick_state_stick_and_axis_count[stick_num];
      for (int axis_num=0; axis_num<num_axes; axis_num++)
      {
         if (initial_joystick_state.stick[stick_num].axis[axis_num] == 0.0f)
         {
            // No position
            // TODO: Consider if this should be reported anyway
            continue;
         }

         sticks[std::make_pair(stick_num, axis_num)] =
            { 0.0, initial_joystick_state.stick[stick_num].axis[axis_num] };
      }
   }
   return sticks;
}

std::map<std::pair<int, int>, std::pair<float, float>> SuspendedJoystickState::get_sticks_moved_in_subsequent_joystick_state()
{
   if (!(subsequent_joystick_state_is_captured))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::get_sticks_moved_in_subsequent_joystick_state]: error: guard \"subsequent_joystick_state_is_captured\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::get_sticks_moved_in_subsequent_joystick_state]: error: guard \"subsequent_joystick_state_is_captured\" not met");
   }
   // Calculate the change in axes
   std::map<std::pair<int, int>, std::pair<float, float>> sticks;
   int num_sticks = subsequent_joystick_state_stick_and_axis_count.size();
   for (int stick_num=0; stick_num<num_sticks; stick_num++)
   {
      int num_axes = subsequent_joystick_state_stick_and_axis_count[stick_num];
      for (int axis_num=0; axis_num<num_axes; axis_num++)
      {
         if (subsequent_joystick_state.stick[stick_num].axis[axis_num] == 0.0f)
         {
            // No position
            // TODO: Consider if this should be reported anyway
            continue;
         }

         sticks[std::make_pair(stick_num, axis_num)] =
            { 0.0, subsequent_joystick_state.stick[stick_num].axis[axis_num] };
      }
   }
   return sticks;
}

std::vector<uint32_t> SuspendedJoystickState::get_buttons_pressed()
{
   if (!(joystick_state_changes_are_calculated))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::get_buttons_pressed]: error: guard \"joystick_state_changes_are_calculated\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::get_buttons_pressed]: error: guard \"joystick_state_changes_are_calculated\" not met");
   }
   return buttons_pressed;
}

std::vector<uint32_t> SuspendedJoystickState::get_buttons_released()
{
   if (!(joystick_state_changes_are_calculated))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::get_buttons_released]: error: guard \"joystick_state_changes_are_calculated\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::get_buttons_released]: error: guard \"joystick_state_changes_are_calculated\" not met");
   }
   return buttons_released;
}

std::map<std::pair<int, int>, std::pair<float, float>> SuspendedJoystickState::get_sticks_moved()
{
   if (!(joystick_state_changes_are_calculated))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::get_sticks_moved]: error: guard \"joystick_state_changes_are_calculated\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::get_sticks_moved]: error: guard \"joystick_state_changes_are_calculated\" not met");
   }
   return sticks_moved;
}

void SuspendedJoystickState::capture_initial_joystick_state()
{
   if (!((!initial_joystick_state_is_captured)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::capture_initial_joystick_state]: error: guard \"(!initial_joystick_state_is_captured)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::capture_initial_joystick_state]: error: guard \"(!initial_joystick_state_is_captured)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::capture_initial_joystick_state]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::capture_initial_joystick_state]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_joystick_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::capture_initial_joystick_state]: error: guard \"al_is_joystick_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::capture_initial_joystick_state]: error: guard \"al_is_joystick_installed()\" not met");
   }
   if (!(joystick))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::capture_initial_joystick_state]: error: guard \"joystick\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::capture_initial_joystick_state]: error: guard \"joystick\" not met");
   }
   if (!al_get_joystick_active(joystick))
   {
      // TODO: Consider what behavior should be here (joystick was disconnected just before this method was called)
      return;
   }

   al_get_joystick_state(joystick, &initial_joystick_state);
   int num_sticks = al_get_joystick_num_sticks(joystick);
   initial_joystick_state_stick_and_axis_count.resize(num_sticks);
   for (int i=0; i<num_sticks; i++)
   {
      int num_axis = al_get_joystick_num_axes(joystick, i);
      initial_joystick_state_stick_and_axis_count[i] = num_axis;
   }
   initial_joystick_state_num_buttons = al_get_joystick_num_buttons(joystick);
   initial_joystick_state_is_captured = true;
   return;
}

void SuspendedJoystickState::capture_subsequent_joystick_state()
{
   if (!((!subsequent_joystick_state_is_captured)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::capture_subsequent_joystick_state]: error: guard \"(!subsequent_joystick_state_is_captured)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::capture_subsequent_joystick_state]: error: guard \"(!subsequent_joystick_state_is_captured)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::capture_subsequent_joystick_state]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::capture_subsequent_joystick_state]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_joystick_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::capture_subsequent_joystick_state]: error: guard \"al_is_joystick_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::capture_subsequent_joystick_state]: error: guard \"al_is_joystick_installed()\" not met");
   }
   if (!(joystick))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::capture_subsequent_joystick_state]: error: guard \"joystick\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::capture_subsequent_joystick_state]: error: guard \"joystick\" not met");
   }
   if (!al_get_joystick_active(joystick))
   {
      // TODO: Consider what behavior should be here (joystick was disconnected just before this method was called)
      return;
   }

   al_get_joystick_state(joystick, &subsequent_joystick_state);
   int num_sticks = al_get_joystick_num_sticks(joystick);
   subsequent_joystick_state_stick_and_axis_count.resize(num_sticks);
   for (int i=0; i<num_sticks; i++)
   {
      int num_axis = al_get_joystick_num_axes(joystick, i);
      subsequent_joystick_state_stick_and_axis_count[i] = num_axis;
   }
   subsequent_joystick_state_num_buttons = al_get_joystick_num_buttons(joystick);
   subsequent_joystick_state_is_captured = true;
   return;
}

void SuspendedJoystickState::calculate_joystick_state_changes()
{
   if (!((!joystick_state_changes_are_calculated)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::calculate_joystick_state_changes]: error: guard \"(!joystick_state_changes_are_calculated)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::calculate_joystick_state_changes]: error: guard \"(!joystick_state_changes_are_calculated)\" not met");
   }
   if (!(initial_joystick_state_is_captured))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::calculate_joystick_state_changes]: error: guard \"initial_joystick_state_is_captured\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::calculate_joystick_state_changes]: error: guard \"initial_joystick_state_is_captured\" not met");
   }
   if (!(subsequent_joystick_state_is_captured))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SuspendedJoystickState::calculate_joystick_state_changes]: error: guard \"subsequent_joystick_state_is_captured\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SuspendedJoystickState::calculate_joystick_state_changes]: error: guard \"subsequent_joystick_state_is_captured\" not met");
   }
   if (initial_joystick_state_stick_and_axis_count != subsequent_joystick_state_stick_and_axis_count)
   {
      // TODO: Consider what behavior should be here (joystick stick count or num axes changed, unexpected state)
      return;
   }
   else if (initial_joystick_state_num_buttons != subsequent_joystick_state_num_buttons)
   {
      // TODO: Consider what behavior should be here (joystick num buttons changed, unexpected state)
      return;
   }

   // Calculate the change in button presses
   int num_buttons = initial_joystick_state_num_buttons;
   for (int button_num=0; button_num<num_buttons; button_num++)
   {
      if (initial_joystick_state.button[button_num] == subsequent_joystick_state.button[button_num])
      {
         // No change
         continue;
      }

      bool button_is_pressed = subsequent_joystick_state.button[button_num];
      if (button_is_pressed) buttons_pressed.push_back(button_num);
      else buttons_released.push_back(button_num);
   }

   // Calculate the change in axes
   int num_sticks = initial_joystick_state_stick_and_axis_count.size();
   for (int stick_num=0; stick_num<num_sticks; stick_num++)
   {
      int num_axes = initial_joystick_state_stick_and_axis_count[stick_num];
      for (int axis_num=0; axis_num<num_axes; axis_num++)
      {
         if (initial_joystick_state.stick[stick_num].axis[axis_num]
            == subsequent_joystick_state.stick[stick_num].axis[axis_num])
         {
            // No change
            continue;
         }

         float stick_delta = subsequent_joystick_state.stick[stick_num].axis[axis_num]
                           - initial_joystick_state.stick[stick_num].axis[axis_num];
         sticks_moved[std::make_pair(stick_num, axis_num)] =
            { stick_delta, subsequent_joystick_state.stick[stick_num].axis[axis_num] };
      }
   }

   joystick_state_changes_are_calculated = true;
   return;
}


} // namespace AllegroFlare


