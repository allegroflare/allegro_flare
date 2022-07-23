

#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityFactory.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Color.hpp>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


FixedRoom2D::FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin)
   : bitmap_bin(bitmap_bin)
   , room_dictionary({})
   , entities({})
   , cursor_x(1920/2)
   , cursor_y(1080/2)
   , initialized(false)
{
}


FixedRoom2D::~FixedRoom2D()
{
}


void FixedRoom2D::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void FixedRoom2D::set_room_dictionary(AllegroFlare::Prototypes::FixedRoom2D::RoomDictionary room_dictionary)
{
   this->room_dictionary = room_dictionary;
}


AllegroFlare::Prototypes::FixedRoom2D::RoomDictionary FixedRoom2D::get_room_dictionary()
{
   return room_dictionary;
}


void FixedRoom2D::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "FixedRoom2D" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "FixedRoom2D" << "::" << "initialize" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Prototypes::FixedRoom2D::EntityFactory entity_factory(bitmap_bin);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* created = entity_factory.create_chair_entity();
   entities.push_back(created);

   initialized = true;
   return;
}

void FixedRoom2D::render()
{
   for (auto &entity : entities)
   {
      entity->render();
      entity->get_placement_ref().draw_box(AllegroFlare::Color::DodgerBlue, true);
   }
   return;
}

void FixedRoom2D::update()
{
   for (auto &entity : entities)
   {
      entity->update();
   }
   return;
}

void FixedRoom2D::draw_cursor()
{
   return;
}

void FixedRoom2D::move_cursor_x(float distance)
{
   cursor_x += distance;
   return;
}

void FixedRoom2D::move_cursor_y(float distance)
{
   cursor_y += distance;
   return;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


