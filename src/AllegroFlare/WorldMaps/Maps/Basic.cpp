

#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>




namespace AllegroFlare
{
namespace WorldMaps
{
namespace Maps
{


Basic::Basic(std::string background_image_identifier, std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations, float width, float height)
   : AllegroFlare::WorldMaps::Maps::Base(AllegroFlare::WorldMaps::Maps::Basic::TYPE)
   , background_image_identifier(background_image_identifier)
   , locations(locations)
   , width(width)
   , height(height)
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


void Basic::set_width(float width)
{
   this->width = width;
}


void Basic::set_height(float height)
{
   this->height = height;
}


std::string Basic::get_background_image_identifier() const
{
   return background_image_identifier;
}


std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> Basic::get_locations() const
{
   return locations;
}


float Basic::get_width() const
{
   return width;
}


float Basic::get_height() const
{
   return height;
}


std::string Basic::location_id_at(float x, float y)
{
   for (auto &location : locations) if (location.second->collides(x, y)) return location.first;
   return "";
}


} // namespace Maps
} // namespace WorldMaps
} // namespace AllegroFlare


