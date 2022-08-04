#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/InventoryIndex.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Room.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>
#include <map>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class ConfigurationLoader
         {
         private:
            AllegroFlare::InventoryIndex* destination_inventory_index;
            AllegroFlare::Inventory* destination_af_inventory;
            AllegroFlare::Inventory* destination_flags;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* destination_entity_dictionary;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* destination_room_dictionary;
            std::map<std::string, std::string>* destination_entity_room_associations;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* destination_script_dictionary;
            std::string starting_in_room_identifier;

         public:
            ConfigurationLoader(AllegroFlare::InventoryIndex* destination_inventory_index=nullptr, AllegroFlare::Inventory* destination_af_inventory=nullptr, AllegroFlare::Inventory* destination_flags=nullptr, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* destination_entity_dictionary=nullptr, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* destination_room_dictionary=nullptr, std::map<std::string, std::string>* destination_entity_room_associations=nullptr, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* destination_script_dictionary=nullptr);
            ~ConfigurationLoader();

            void set_destination_inventory_index(AllegroFlare::InventoryIndex* destination_inventory_index);
            void set_destination_af_inventory(AllegroFlare::Inventory* destination_af_inventory);
            void set_destination_flags(AllegroFlare::Inventory* destination_flags);
            void set_destination_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* destination_entity_dictionary);
            void set_destination_room_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* destination_room_dictionary);
            void set_destination_entity_room_associations(std::map<std::string, std::string>* destination_entity_room_associations);
            void set_destination_script_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* destination_script_dictionary);
            AllegroFlare::InventoryIndex* get_destination_inventory_index();
            AllegroFlare::Inventory* get_destination_af_inventory();
            AllegroFlare::Inventory* get_destination_flags();
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* get_destination_entity_dictionary();
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* get_destination_room_dictionary();
            std::map<std::string, std::string>* get_destination_entity_room_associations();
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* get_destination_script_dictionary();
            std::string get_starting_in_room_identifier();
            bool load_original_gametest_default(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper* entity_collection_helper=nullptr);
         };
      }
   }
}



