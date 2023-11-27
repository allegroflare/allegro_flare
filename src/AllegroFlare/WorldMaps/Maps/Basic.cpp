

#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>




namespace AllegroFlare
{
namespace WorldMaps
{
namespace Maps
{


Basic::Basic(std::string background_image_identifier, std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations)
   : AllegroFlare::WorldMaps::Maps::Base(AllegroFlare::WorldMaps::Maps::Basic::TYPE)
   , background_image_identifier(background_image_identifier)
   , locations(locations)
{
}


Basic::~Basic()
{
}


void Basic::set_background_image_identifier(std::string background_image_identifier)
{
   this->background_image_identifier = background_image_identifier;
}


void Basic::set_locations(std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations)
{
   this->locations = locations;
}


std::string Basic::get_background_image_identifier() const
{
   return background_image_identifier;
}


std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> Basic::get_locations() const
{
   return locations;
}


std::string Basic::location_id_at(float x, float y)
{
   for (auto &location : locations) if (location.second->collides(x, y)) return location.first;
   return "";
}


} // namespace Maps
} // namespace WorldMaps
} // namespace AllegroFlare


