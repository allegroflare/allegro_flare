

#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/WorldMaps/Locations/Basic.hpp>
#include <AllegroFlare/WorldMaps/Locations/Player.hpp>
#include <iostream>


namespace AllegroFlare
{
namespace WorldMaps
{
namespace Maps
{


Basic::Basic(std::string background_image_identifier, std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations, float width, float height, std::string primary_point_of_interest_identifier)
   : AllegroFlare::WorldMaps::Maps::Base(AllegroFlare::WorldMaps::Maps::Basic::TYPE)
   , background_image_identifier(background_image_identifier)
   , locations(locations)
   , width(width)
   , height(height)
   , primary_point_of_interest_identifier(primary_point_of_interest_identifier)
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


void Basic::set_primary_point_of_interest_identifier(std::string primary_point_of_interest_identifier)
{
   this->primary_point_of_interest_identifier = primary_point_of_interest_identifier;
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


std::string Basic::get_primary_point_of_interest_identifier() const
{
   return primary_point_of_interest_identifier;
}


std::pair<float, float> Basic::infer_primary_point_of_interest_coordinates()
{
   if (primary_point_of_interest_is_set() && primary_point_of_interest_is_on_map())
   {
      AllegroFlare::WorldMaps::Locations::Base* location = locations[primary_point_of_interest_identifier];
      if (location->is_type(AllegroFlare::WorldMaps::Locations::Basic::TYPE))
      {
         AllegroFlare::WorldMaps::Locations::Basic *as =
            static_cast<AllegroFlare::WorldMaps::Locations::Basic*>(location);
         return { as->get_x(), as->get_y() };
      }
      else if (location->is_type(AllegroFlare::WorldMaps::Locations::Player::TYPE))
      {
         AllegroFlare::WorldMaps::Locations::Player *as =
            static_cast<AllegroFlare::WorldMaps::Locations::Player*>(location);
         return { as->get_x(), as->get_y() };
      }
      else
      {
         // TODO: Test this thrown error
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::WorldMaps::Maps::Basic::infer_primary_point_of_interest_coordinates",
            "Could not infer coordinates on type \"" + location->get_type() + "\"."
         );
      }
   }
   return { 0.0f, 0.0f };
}

std::pair<bool, std::pair<float, float>> Basic::infer_location_coordinates(std::string location_id)
{
   if (location_exists(location_id))
   {
      AllegroFlare::WorldMaps::Locations::Base* location = locations[location_id];
      if (location->is_type(AllegroFlare::WorldMaps::Locations::Basic::TYPE))
      {
         AllegroFlare::WorldMaps::Locations::Basic *as =
            static_cast<AllegroFlare::WorldMaps::Locations::Basic*>(location);
         return { true, { as->get_x(), as->get_y() }};
      }
      else if (location->is_type(AllegroFlare::WorldMaps::Locations::Player::TYPE))
      {
         AllegroFlare::WorldMaps::Locations::Player *as =
            static_cast<AllegroFlare::WorldMaps::Locations::Player*>(location);
         return { true, { as->get_x(), as->get_y() }};
      }
      else
      {
         // TODO: Test this thrown error
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::WorldMaps::Maps::Basic::infer_location_coordinates",
            "Could not infer coordinates on type \"" + location->get_type() + "\"."
         );
      }
   }
   return { false, { 0.0f, 0.0f }}; // Loction was not found
}

bool Basic::primary_point_of_interest_is_set()
{
   return (primary_point_of_interest_identifier != DEFAULT_PRIMARY_POINT_OF_INTEREST_IDENTIFIER);
}

bool Basic::primary_point_of_interest_is_on_map()
{
   return (locations.find(primary_point_of_interest_identifier) != locations.end());
}

bool Basic::location_exists(std::string location_id)
{
   // TODO: Test these
   return (locations.count(location_id) != 0);
}

AllegroFlare::WorldMaps::Locations::Base* Basic::find_location_by_id(std::string location_id)
{
   // TODO: Test these
   if (locations.count(location_id) == 0) return nullptr;
   return locations[location_id];
}

std::string Basic::location_id_at(float x, float y)
{
   for (auto &location : locations) if (location.second->collides(x, y)) return location.first;
   return "";
}


} // namespace Maps
} // namespace WorldMaps
} // namespace AllegroFlare


