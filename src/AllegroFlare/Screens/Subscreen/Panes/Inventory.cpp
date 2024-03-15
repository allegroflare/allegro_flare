

#include <AllegroFlare/Screens/Subscreen/Panes/Inventory.hpp>




namespace AllegroFlare
{
namespace Screens
{
namespace Subscreen
{
namespace Panes
{


Inventory::Inventory(std::string property)
   : AllegroFlare::Screens::Subscreen::Panes::Base(AllegroFlare::Screens::Subscreen::Panes::Inventory::TYPE)
   , property(property)
{
}


Inventory::~Inventory()
{
}


std::string Inventory::get_property() const
{
   return property;
}


bool Inventory::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace Panes
} // namespace Subscreen
} // namespace Screens
} // namespace AllegroFlare


