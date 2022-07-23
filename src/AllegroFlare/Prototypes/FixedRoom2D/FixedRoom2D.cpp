

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


FixedRoom2D::FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , room_dictionary({})
   , entities({})
   , cursor({})
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


void FixedRoom2D::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
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
   cursor.set_font_bin(font_bin);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* created = entity_factory.create_chair_entity();
   entities.push_back(created);

   cursor.set_cursor_to_pointer();
   cursor.clear_info_text();

   initialized = true;
   return;
}

void FixedRoom2D::render()
{
   // draw the entities
   for (auto &entity : entities)
   {
      entity->render();
      entity->get_placement_ref().draw_box(AllegroFlare::Color::DodgerBlue, true);
   }

   // draw the cursor
   cursor.draw();

   return;
}

void FixedRoom2D::update()
{
   // update the entities
   for (auto &entity : entities)
   {
      entity->update();
   }

   // update the cursor
   cursor.update();

   return;
}

void FixedRoom2D::move_cursor(float distance_x, float distance_y)
{
   cursor.move(distance_x, distance_y);

   // update the state of the entities
   for (auto &entity : entities)
   {
      entity->update();
   }

   return;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


