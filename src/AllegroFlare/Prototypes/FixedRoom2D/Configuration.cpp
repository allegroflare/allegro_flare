

#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityFactory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/RoomFactory.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Configuration::Configuration(AllegroFlare::InventoryIndex* inventory_index, AllegroFlare::Inventory* af_inventory, AllegroFlare::Inventory* flags, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* room_dictionary, std::map<std::string, std::string>* entity_room_associations, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary)
   : inventory_index(inventory_index)
   , af_inventory(af_inventory)
   , flags(flags)
   , entity_dictionary(entity_dictionary)
   , room_dictionary(room_dictionary)
   , entity_room_associations(entity_room_associations)
   , script_dictionary(script_dictionary)
   , starting_in_room_identifier("[unset-starting_in_room_identifier]")
{
}


Configuration::~Configuration()
{
}


void Configuration::set_inventory_index(AllegroFlare::InventoryIndex* inventory_index)
{
   this->inventory_index = inventory_index;
}


void Configuration::set_af_inventory(AllegroFlare::Inventory* af_inventory)
{
   this->af_inventory = af_inventory;
}


void Configuration::set_flags(AllegroFlare::Inventory* flags)
{
   this->flags = flags;
}


void Configuration::set_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary)
{
   this->entity_dictionary = entity_dictionary;
}


void Configuration::set_room_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* room_dictionary)
{
   this->room_dictionary = room_dictionary;
}


void Configuration::set_entity_room_associations(std::map<std::string, std::string>* entity_room_associations)
{
   this->entity_room_associations = entity_room_associations;
}


void Configuration::set_script_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary)
{
   this->script_dictionary = script_dictionary;
}


AllegroFlare::InventoryIndex* Configuration::get_inventory_index()
{
   return inventory_index;
}


AllegroFlare::Inventory* Configuration::get_af_inventory()
{
   return af_inventory;
}


AllegroFlare::Inventory* Configuration::get_flags()
{
   return flags;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* Configuration::get_entity_dictionary()
{
   return entity_dictionary;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* Configuration::get_room_dictionary()
{
   return room_dictionary;
}


std::map<std::string, std::string>* Configuration::get_entity_room_associations()
{
   return entity_room_associations;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* Configuration::get_script_dictionary()
{
   return script_dictionary;
}


std::string Configuration::get_starting_in_room_identifier()
{
   return starting_in_room_identifier;
}


bool Configuration::load_original_gametest_default(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper)
{
   if (!(inventory_index))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"inventory_index\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(af_inventory))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"af_inventory\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(flags))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"flags\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(entity_dictionary))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"entity_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(room_dictionary))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"room_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(entity_room_associations))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"entity_room_associations\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(script_dictionary))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"script_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(entity_collection_helper))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"entity_collection_helper\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Prototypes::FixedRoom2D::EntityFactory entity_factory(bitmap_bin);
   AllegroFlare::Prototypes::FixedRoom2D::RoomFactory room_factory(
      bitmap_bin, font_bin, event_emitter, entity_collection_helper
   );

   *inventory_index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();

   af_inventory->add_item(1);
   af_inventory->add_item(4);
   af_inventory->add_item(3);

   *room_dictionary = {
      { "front_hall", room_factory.create_room() },
      { "study", room_factory.create_room() },
   };

   *entity_dictionary = {
      { "door1", entity_factory.create_entity(
            "download-door-png-transparent-image-and-clipart-3.png", 1400, 800, 0.85, "Door 1", "observe_door1") },
      { "door2", entity_factory.create_entity(
            "download-door-png-transparent-image-and-clipart-3.png", 500, 800, 0.85, "Door 2", "observe_door2") },
      { "chair", entity_factory.create_entity(
            "wooden-chair-png-transparent-image-pngpix-0.png", 700, 800, 0.168, "Chair", "signal_hello") },
      { "table", entity_factory.create_entity(
            "download-wooden-table-png-image-png-image-pngimg-3.png", 900, 800, 0.4, "table", "observe_table") },
      { "keys", entity_factory.create_entity(
            "key-keychain-house-keys-door-photo-pixabay-25.png", 940, 590, 0.05, "keys", "collect_keys") },
   };

   *entity_room_associations = {
      { "door1", "front_hall" },
      { "door2", "study" },
      { "chair", "front_hall" },
      { "table", "front_hall" },
      { "keys", "front_hall" },
   };

   *script_dictionary = {
      { "observe_door1", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: Just a regular door. | I'm going to step through it.",
            "ENTER_ROOM: study",
      })},
      { "observe_door2", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: A regular door. | I'll to in.",
            "ENTER_ROOM: front_hall",
      })},
      { "signal_hello", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "SIGNAL: Hello!"})
      },
      { "spawn_dialog", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: This was a scripted dialog!"
      })},
      { "collect_keys", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "COLLECT: keys"
      })},
      { "observe_table", AllegroFlare::Prototypes::FixedRoom2D::Script({
            "DIALOG: Hmm. Nothing interesting on this table."
      })},
   };

   starting_in_room_identifier = "front_hall";
    
   //enter_room("front_hall");
   //enter_room("study");

   return true;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


