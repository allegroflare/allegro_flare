

#include <AllegroFlare/Prototypes/FixedRoom2D/ConfigurationFactory.hpp>

#include <AllegroFlare/Prototypes/FixedRoom2D/EntityFactory.hpp>
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


ConfigurationFactory::ConfigurationFactory()
{
}


ConfigurationFactory::~ConfigurationFactory()
{
}


AllegroFlare::Prototypes::FixedRoom2D::Configuration ConfigurationFactory::build_original_gametest_default(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::ConfigurationFactory::build_original_gametest_default]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::ConfigurationFactory::build_original_gametest_default]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::ConfigurationFactory::build_original_gametest_default]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::ConfigurationFactory::build_original_gametest_default]: error: guard \"font_bin\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::ConfigurationFactory::build_original_gametest_default]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::ConfigurationFactory::build_original_gametest_default]: error: guard \"event_emitter\" not met");
   }
   if (!(entity_collection_helper))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::ConfigurationFactory::build_original_gametest_default]: error: guard \"entity_collection_helper\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::ConfigurationFactory::build_original_gametest_default]: error: guard \"entity_collection_helper\" not met");
   }
   AllegroFlare::Prototypes::FixedRoom2D::Configuration result;

   AllegroFlare::InventoryIndex &inventory_index = result.get_inventory_index_ref();
   AllegroFlare::Inventory &af_inventory = result.get_af_inventory_ref();
   AllegroFlare::Inventory &flags = result.get_flags_ref();
   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> &entity_dictionary =
      result.get_entity_dictionary_ref();
   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*> &room_dictionary =
      result.get_room_dictionary_ref();
   std::map<std::string, std::string> &entity_room_associations =
      result.get_entity_room_associations_ref();
   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script> &script_dictionary =
      result.get_script_dictionary_ref();
   std::string &starting_room_identifier = result.get_starting_room_identifier_ref();



   AllegroFlare::Prototypes::FixedRoom2D::EntityFactory entity_factory(bitmap_bin);
   AllegroFlare::Prototypes::FixedRoom2D::RoomFactory room_factory(
      bitmap_bin, font_bin, event_emitter, entity_collection_helper
   );

   inventory_index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();

   af_inventory.add_item(1);
   af_inventory.add_item(4);
   af_inventory.add_item(3);

   room_dictionary = {
      { "front_hall", room_factory.create_room() },
      { "study", room_factory.create_room() },
   };

   entity_dictionary = {
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

   entity_room_associations = {
      { "door1", "front_hall" },
      { "door2", "study" },
      { "chair", "front_hall" },
      { "table", "front_hall" },
      { "keys", "front_hall" },
   };

   script_dictionary = {
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

   starting_room_identifier = "front_hall";
    
   //enter_room("front_hall");
   //enter_room("study");

   return result;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


