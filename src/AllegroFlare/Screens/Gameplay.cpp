

#include <AllegroFlare/Screens/Gameplay.hpp>

#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
namespace Screens
{


Gameplay::Gameplay(std::string property)
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::Gameplay::TYPE)
   , property(property)
{
}


Gameplay::~Gameplay()
{
}


std::string Gameplay::get_property() const
{
   return property;
}


void Gameplay::set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_finished_callback_func)
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Screens::Gameplay::set_on_finished_callback_func",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return;
}

void Gameplay::set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data)
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Screens::Gameplay::set_on_finished_callback_func",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return;
}

void Gameplay::load_level_by_identifier(std::string possible_type)
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Screens::Gameplay::set_on_finished_callback_func",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   //return (possible_type == get_property());
   return;
}

bool Gameplay::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace Screens
} // namespace AllegroFlare


