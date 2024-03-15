

#include <AllegroFlare/Screens/Subscreen/Panes/Airwing.hpp>




namespace AllegroFlare
{
namespace Screens
{
namespace Subscreen
{
namespace Panes
{


Airwing::Airwing(std::string property)
   : AllegroFlare::Screens::Subscreen::Panes::Base(AllegroFlare::Screens::Subscreen::Panes::Airwing::TYPE)
   , property(property)
{
}


Airwing::~Airwing()
{
}


std::string Airwing::get_property() const
{
   return property;
}


bool Airwing::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace Panes
} // namespace Subscreen
} // namespace Screens
} // namespace AllegroFlare


