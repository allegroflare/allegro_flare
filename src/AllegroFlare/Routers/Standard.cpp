

#include <AllegroFlare/Routers/Standard.hpp>




namespace AllegroFlare
{
namespace Routers
{


Standard::Standard(std::string property)
   : AllegroFlare::Routers::Base(AllegroFlare::Routers::Standard::TYPE)
   , property(property)
{
}


Standard::~Standard()
{
}


std::string Standard::get_property() const
{
   return property;
}


bool Standard::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace Routers
} // namespace AllegroFlare


