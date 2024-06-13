

#include <AllegroFlare/Prototypes/FixedRoom2D/RoomFactory.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


RoomFactory::RoomFactory(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , entity_collection_helper(entity_collection_helper)
{
}


RoomFactory::~RoomFactory()
{
}


void RoomFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void RoomFactory::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void RoomFactory::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void RoomFactory::set_entity_collection_helper(AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper)
{
   this->entity_collection_helper = entity_collection_helper;
}


AllegroFlare::BitmapBin* RoomFactory::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* RoomFactory::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::EventEmitter* RoomFactory::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* RoomFactory::get_entity_collection_helper() const
{
   return entity_collection_helper;
}


AllegroFlare::Prototypes::FixedRoom2D::Room* RoomFactory::create_room(float width, float height)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::RoomFactory::create_room]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::RoomFactory::create_room]: error: guard \"font_bin\" not met");
   }
   AllegroFlare::Prototypes::FixedRoom2D::Room* result = new AllegroFlare::Prototypes::FixedRoom2D::Room();

   //AllegroFlare::Prototypes::FixedRoom2D::Cursor &cursor = result->get_cursor_ref();

   // TODO: Remove these direct calls to the room's cursor once a global cursor is available
   //cursor.set_font_bin(font_bin);
   //cursor.set_cursor_to_pointer();
   //cursor.clear_info_text();

   return result;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


