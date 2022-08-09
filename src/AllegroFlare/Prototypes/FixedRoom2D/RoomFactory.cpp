

#include <AllegroFlare/Prototypes/FixedRoom2D/RoomFactory.hpp>
#include <stdexcept>
#include <sstream>


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


AllegroFlare::BitmapBin* RoomFactory::get_bitmap_bin()
{
   return bitmap_bin;
}


AllegroFlare::FontBin* RoomFactory::get_font_bin()
{
   return font_bin;
}


AllegroFlare::EventEmitter* RoomFactory::get_event_emitter()
{
   return event_emitter;
}


AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* RoomFactory::get_entity_collection_helper()
{
   return entity_collection_helper;
}


AllegroFlare::Prototypes::FixedRoom2D::Room* RoomFactory::create_room(float width, float height)
{
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "RoomFactory" << "::" << "create_room" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "RoomFactory" << "::" << "create_room" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "RoomFactory" << "::" << "create_room" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(entity_collection_helper))
      {
         std::stringstream error_message;
         error_message << "RoomFactory" << "::" << "create_room" << ": error: " << "guard \"entity_collection_helper\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Prototypes::FixedRoom2D::Room* result =
      new AllegroFlare::Prototypes::FixedRoom2D::Room(font_bin, event_emitter, entity_collection_helper);
   result->initialize();

   return result;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


