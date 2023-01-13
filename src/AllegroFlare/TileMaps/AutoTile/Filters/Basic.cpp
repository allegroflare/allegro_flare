

#include <AllegroFlare/TileMaps/AutoTile/Filters/Basic.hpp>




namespace AllegroFlare
{
namespace TileMaps
{
namespace AutoTile
{
namespace Filters
{


Basic::Basic(std::string property)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::Basic::TYPE)
   , property(property)
{
}


Basic::~Basic()
{
}


std::string Basic::get_property() const
{
   return property;
}


bool Basic::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


