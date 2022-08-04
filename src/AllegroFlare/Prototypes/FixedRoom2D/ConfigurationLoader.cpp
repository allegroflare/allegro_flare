

#include <AllegroFlare/Prototypes/FixedRoom2D/ConfigurationLoader.hpp>
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


ConfigurationLoader::ConfigurationLoader(AllegroFlare::InventoryIndex* destination_inventory_index, AllegroFlare::Inventory* destination_af_inventory, AllegroFlare::Inventory* destination_flags, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* destination_entity_dictionary, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* destination_room_dictionary, std::map<std::string, std::string>* destination_entity_room_associations, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* destination_script_dictionary)
   : destination_inventory_index(destination_inventory_index)
   , destination_af_inventory(destination_af_inventory)
   , destination_flags(destination_flags)
   , destination_entity_dictionary(destination_entity_dictionary)
   , destination_room_dictionary(destination_room_dictionary)
   , destination_entity_room_associations(destination_entity_room_associations)
   , destination_script_dictionary(destination_script_dictionary)
   , starting_in_room_identifier("[unset-starting_in_room_identifier]")
{
}


ConfigurationLoader::~ConfigurationLoader()
{
}


void ConfigurationLoader::set_destination_inventory_index(AllegroFlare::InventoryIndex* destination_inventory_index)
{
   this->destination_inventory_index = destination_inventory_index;
}


void ConfigurationLoader::set_destination_af_inventory(AllegroFlare::Inventory* destination_af_inventory)
{
   this->destination_af_inventory = destination_af_inventory;
}


void ConfigurationLoader::set_destination_flags(AllegroFlare::Inventory* destination_flags)
{
   this->destination_flags = destination_flags;
}


void ConfigurationLoader::set_destination_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* destination_entity_dictionary)
{
   this->destination_entity_dictionary = destination_entity_dictionary;
}


void ConfigurationLoader::set_destination_room_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* destination_room_dictionary)
{
   this->destination_room_dictionary = destination_room_dictionary;
}


void ConfigurationLoader::set_destination_entity_room_associations(std::map<std::string, std::string>* destination_entity_room_associations)
{
   this->destination_entity_room_associations = destination_entity_room_associations;
}


void ConfigurationLoader::set_destination_script_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* destination_script_dictionary)
{
   this->destination_script_dictionary = destination_script_dictionary;
}


AllegroFlare::InventoryIndex* ConfigurationLoader::get_destination_inventory_index()
{
   return destination_inventory_index;
}


AllegroFlare::Inventory* ConfigurationLoader::get_destination_af_inventory()
{
   return destination_af_inventory;
}


AllegroFlare::Inventory* ConfigurationLoader::get_destination_flags()
{
   return destination_flags;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* ConfigurationLoader::get_destination_entity_dictionary()
{
   return destination_entity_dictionary;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* ConfigurationLoader::get_destination_room_dictionary()
{
   return destination_room_dictionary;
}


std::map<std::string, std::string>* ConfigurationLoader::get_destination_entity_room_associations()
{
   return destination_entity_room_associations;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* ConfigurationLoader::get_destination_script_dictionary()
{
   return destination_script_dictionary;
}


std::string ConfigurationLoader::get_starting_in_room_identifier()
{
   return starting_in_room_identifier;
}


bool ConfigurationLoader::load_original_gametest_default(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper)
{
   if (!(destination_inventory_index))
      {
         std::stringstream error_message;
         error_message << "ConfigurationLoader" << "::" << "load_original_gametest_default" << ": error: " << "guard \"destination_inventory_index\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(destination_af_inventory))
      {
         std::stringstream error_message;
         error_message << "ConfigurationLoader" << "::" << "load_original_gametest_default" << ": error: " << "guard \"destination_af_inventory\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(destination_flags))
      {
         std::stringstream error_message;
         error_message << "ConfigurationLoader" << "::" << "load_original_gametest_default" << ": error: " << "guard \"destination_flags\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(destination_entity_dictionary))
      {
         std::stringstream error_message;
         error_message << "ConfigurationLoader" << "::" << "load_original_gametest_default" << ": error: " << "guard \"destination_entity_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(destination_room_dictionary))
      {
         std::stringstream error_message;
         error_message << "ConfigurationLoader" << "::" << "load_original_gametest_default" << ": error: " << "guard \"destination_room_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(destination_entity_room_associations))
      {
         std::stringstream error_message;
         error_message << "ConfigurationLoader" << "::" << "load_original_gametest_default" << ": error: " << "guard \"destination_entity_room_associations\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(destination_script_dictionary))
      {
         std::stringstream error_message;
         error_message << "ConfigurationLoader" << "::" << "load_original_gametest_default" << ": error: " << "guard \"destination_script_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "ConfigurationLoader" << "::" << "load_original_gametest_default" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "ConfigurationLoader" << "::" << "load_original_gametest_default" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "ConfigurationLoader" << "::" << "load_original_gametest_default" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(entity_collection_helper))
      {
         std::stringstream error_message;
         error_message << "ConfigurationLoader" << "::" << "load_original_gametest_default" << ": error: " << "guard \"entity_collection_helper\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Prototypes::FixedRoom2D::EntityFactory entity_factory(bitmap_bin);
   AllegroFlare::Prototypes::FixedRoom2D::RoomFactory room_factory(
      bitmap_bin, font_bin, event_emitter, entity_collection_helper
   );

   *destination_inventory_index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();

   destination_af_inventory->add_item(1);
   destination_af_inventory->add_item(4);
   destination_af_inventory->add_item(3);

   *destination_room_dictionary = {
      { "front_hall", room_factory.create_room() },
      { "study", room_factory.create_room() },
   };

   *destination_entity_dictionary = {
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

   *destination_entity_room_associations = {
      { "door1", "front_hall" },
      { "door2", "study" },
      { "chair", "front_hall" },
      { "table", "front_hall" },
      { "keys", "front_hall" },
   };

   *destination_script_dictionary = {
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
            "DIALOG: Hmm. Interesting, there's a key on this table."
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


