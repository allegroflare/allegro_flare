

#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>




namespace AllegroFlare
{
namespace WorldMaps
{
namespace Maps
{


Basic::Basic(std::vector<AllegroFlare::WorldMaps::Locations::Base*> locations)
   : AllegroFlare::WorldMaps::Maps::Base(AllegroFlare::WorldMaps::Maps::Basic::TYPE)
   , locations(locations)
{
}


Basic::~Basic()
{
}


void Basic::set_locations(std::vector<AllegroFlare::WorldMaps::Locations::Base*> locations)
{
   this->locations = locations;
}


std::vector<AllegroFlare::WorldMaps::Locations::Base*> Basic::get_locations() const
{
   return locations;
}


std::string Basic::location_id_at(float x, float y)
{
   return "";
}


} // namespace Maps
} // namespace WorldMaps
} // namespace AllegroFlare


