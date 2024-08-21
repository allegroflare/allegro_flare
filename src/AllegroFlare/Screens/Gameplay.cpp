

#include <AllegroFlare/Screens/Gameplay.hpp>

#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
namespace Screens
{


Gameplay::Gameplay()
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::Gameplay::TYPE)
   , on_finished_callback_func()
   , on_finished_callback_func_user_data(nullptr)
   , player_input_controller(nullptr)
   , gameplay_suspended(false)
   , suspended_keyboard_state({})
{
}


Gameplay::~Gameplay()
{
}


void Gameplay::set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_finished_callback_func)
{
   this->on_finished_callback_func = on_finished_callback_func;
}


void Gameplay::set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data)
{
   this->on_finished_callback_func_user_data = on_finished_callback_func_user_data;
}


std::function<void(AllegroFlare::Screens::Gameplay*, void*)> Gameplay::get_on_finished_callback_func() const
{
   return on_finished_callback_func;
}


void* Gameplay::get_on_finished_callback_func_user_data() const
{
   return on_finished_callback_func_user_data;
}


AllegroFlare::PlayerInputControllers::Base* Gameplay::get_player_input_controller() const
{
   return player_input_controller;
}


bool Gameplay::get_gameplay_suspended() const
{
   return gameplay_suspended;
}


AllegroFlare::SuspendedKeyboardState Gameplay::get_suspended_keyboard_state() const
{
   return suspended_keyboard_state;
}


AllegroFlare::SuspendedKeyboardState &Gameplay::get_suspended_keyboard_state_ref()
{
   return suspended_keyboard_state;
}


void Gameplay::set_player_input_controller(AllegroFlare::PlayerInputControllers::Base* player_input_controller)
{
   if (player_input_controller)
   {
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Screens::Gameplay::set_player_input_controller",
         "deactivating current player_input_controller"
      );
      player_input_controller->on_deactivate();
   }
   this->player_input_controller = player_input_controller;
   AllegroFlare::Logger::info_from(
      "AllegroFlare::Screens::Gameplay::set_player_input_controller",
      "activating new player_input_controller"
   );
   this->player_input_controller->on_activate();
   return;
}

void Gameplay::dialog_system_switch_in_func()
{
   // Function that is called on ALLEGRO_FLARE_DIALOG_SWITCHED_IN
   // TODO: Consider disabling automatic suspend and unsuspend with an option on this class
   suspend_gameplay();
   return;
}

void Gameplay::dialog_system_switch_out_func()
{
   // Function that is called on ALLEGRO_FLARE_DIALOG_SWITCHED_OUT
   // TODO: Consider disabling automatic suspend and unsuspend with an option on this class
   resume_suspended_gameplay();
   return;
}

void Gameplay::suspend_gameplay()
{
   if (gameplay_suspended) return; // TODO: Should this throw? (it caused an issue in a Routers/Standard test)
   suspended_keyboard_state.capture_initial_keyboard_state(); // TODO: Add guard if state cannot be captured
   gameplay_suspended = true;
   gameplay_suspend_func();

   // Suspend the player input controls
   if (player_input_controller) player_input_controller->gameplay_suspend_func();

   return;
}

void Gameplay::resume_suspended_gameplay()
{
   if (!gameplay_suspended) return; // TODO: Should this throw? (it caused an issue in a Routers/Standard test)
   gameplay_suspended = false;
   suspended_keyboard_state.capture_subsequent_keyboard_state(); // TODO: Add guard if state cannot be captured
   suspended_keyboard_state.calculate_keyboard_state_changes(); // TODO: Add guard if state cannot be captured
   gameplay_resume_func();
   suspended_keyboard_state.reset();

   // Resume the player input controls
   if (player_input_controller) player_input_controller->gameplay_resume_func();

   return;
}

void Gameplay::toggle_suspend_gameplay()
{
   gameplay_suspended = !gameplay_suspended;
   if (gameplay_suspended) gameplay_suspend_func();
   else gameplay_resume_func();
   return;
}

void Gameplay::gameplay_suspend_func()
{
   // Function that is called immediately after the gameplay is suspended.
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Screens::Gameplay::gameplay_suspend_func",
      "Not implemented in the base class. This method must be implemented in the derived class. Take into account "
         "the AllegroFlare/Screens/Gameplay class has a suspend_gameplay func"
   );
   return;
}

void Gameplay::gameplay_resume_func()
{
   // Function that is called immediately after the gameplay is resumed.
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Screens::Gameplay::gameplay_suspend_func",
      "Not implemented in the base class. This method must be implemented in the derived class. Take into account "
         "the AllegroFlare/Screens/Gameplay class has a resume_gameplay func"
   );
   return;
}

void Gameplay::call_on_finished_callback_func()
{
   // TODO: Test this callback call
   if (on_finished_callback_func) on_finished_callback_func(this, on_finished_callback_func_user_data);
   return;
}

bool Gameplay::load_level_by_identifier(std::string possible_type)
{
   AllegroFlare::Logger::warn_from(
      "AllegroFlare::Screens::Gameplay::load_level_by_identifier",
      "Nothing to do here, returning false (false indicates that no level was loaded as a result of this method "
         "call. Consider removing this method and have loading occur outside of this screen class."
   );
   return false; // NOTE: false indicates that no level was loaded as a result of this method call
}

void Gameplay::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (player_input_controller)
   {
      player_input_controller->virtual_control_button_down_func(
         player,
         virtual_controller,
         virtual_controller_button_num,
         is_repeat
      );
   }
   return;
}

void Gameplay::joy_axis_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->joy_axis_func(ev);
   return;
}

void Gameplay::mouse_down_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->mouse_down_func(ev);
   return;
}

void Gameplay::mouse_axes_func(ALLEGRO_EVENT* ev)
{
   if (player_input_controller) player_input_controller->mouse_axes_func(ev);
   return;
}


} // namespace Screens
} // namespace AllegroFlare


