

#include <AllegroFlare/Prototypes/FixedRoom2D/RoomFactory.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


RoomFactory::RoomFactory(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , entity_dictionary(entity_dictionary)
{
}


RoomFactory::~RoomFactory()
{
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
   if (!(entity_dictionary))
      {
         std::stringstream error_message;
         error_message << "RoomFactory" << "::" << "create_room" << ": error: " << "guard \"entity_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Prototypes::FixedRoom2D::Room* result =
      new AllegroFlare::Prototypes::FixedRoom2D::Room(font_bin, event_emitter);

   result->set_entity_dictionary(entity_dictionary);
   result->initialize();

   return result;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


