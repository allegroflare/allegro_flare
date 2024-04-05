

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
   , gameplay_suspended(false)
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


bool Gameplay::get_gameplay_suspended() const
{
   return gameplay_suspended;
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

void Gameplay::gameplay_suspend_func()
{
   // Function that is called immediately after the gameplay is suspended.
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Screens::Gameplay::gameplay_suspend_func",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return;
}

void Gameplay::gameplay_resume_func()
{
   // Function that is called immediately after the gameplay is resumed.
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Screens::Gameplay::gameplay_suspend_func",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return;
}

void Gameplay::suspend_gameplay()
{
   if (gameplay_suspended) return;
   gameplay_suspended = true;
   gameplay_suspend_func();
   return;
}

void Gameplay::resume_suspended_gameplay()
{
   if (!gameplay_suspended) return;
   gameplay_suspended = false;
   gameplay_resume_func();
   return;
}

void Gameplay::toggle_suspend_gameplay()
{
   gameplay_suspended = !gameplay_suspended;
   if (gameplay_suspended) gameplay_suspend_func();
   else gameplay_resume_func();
   return;
}

void Gameplay::call_on_finished_callback_func()
{
   // TODO: Test this callback call
   if (on_finished_callback_func) on_finished_callback_func(this, on_finished_callback_func_user_data);
   return;
}

void Gameplay::load_level_by_identifier(std::string possible_type)
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Screens::Gameplay::load_level_by_identifier",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return;
}


} // namespace Screens
} // namespace AllegroFlare


