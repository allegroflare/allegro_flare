#pragma once


#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/InventoryIndex.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
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
         class Configuration
         {
         private:
            AllegroFlare::InventoryIndex* inventory_index;
            AllegroFlare::Inventory* af_inventory;
            AllegroFlare::Inventory* flags;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* room_dictionary;
            std::map<std::string, std::string>* entity_room_associations;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary;

         public:
            Configuration(AllegroFlare::InventoryIndex* inventory_index=nullptr, AllegroFlare::Inventory* af_inventory=nullptr, AllegroFlare::Inventory* flags=nullptr, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary=nullptr, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* room_dictionary=nullptr, std::map<std::string, std::string>* entity_room_associations=nullptr, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary=nullptr);
            ~Configuration();

            void set_inventory_index(AllegroFlare::InventoryIndex* inventory_index);
            void set_af_inventory(AllegroFlare::Inventory* af_inventory);
            void set_flags(AllegroFlare::Inventory* flags);
            void set_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary);
            void set_room_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* room_dictionary);
            void set_entity_room_associations(std::map<std::string, std::string>* entity_room_associations);
            void set_script_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary);
            AllegroFlare::InventoryIndex* get_inventory_index();
            AllegroFlare::Inventory* get_af_inventory();
            AllegroFlare::Inventory* get_flags();
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* get_entity_dictionary();
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* get_room_dictionary();
            std::map<std::string, std::string>* get_entity_room_associations();
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* get_script_dictionary();
            bool load_original_gametest_default();
         };
      }
   }
}



