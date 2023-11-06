

#include <AllegroFlare/Screens/Gameplay.hpp>




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


bool Gameplay::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace Screens
} // namespace AllegroFlare


