#pragma once


#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/InventoryIndex.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
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
         class ConfigurationLoader
         {
         private:
            AllegroFlare::Prototypes::FixedRoom2D::Configuration* source_configuration;
            AllegroFlare::InventoryIndex* destination_inventory_index;
            AllegroFlare::Inventory* destination_af_inventory;
            AllegroFlare::Inventory* destination_flags;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* destination_entity_dictionary;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* destination_room_dictionary;
            std::map<std::string, std::string>* destination_entity_room_associations;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* destination_script_dictionary;
            std::string starting_in_room_identifier;

         protected:


         public:
            ConfigurationLoader(AllegroFlare::Prototypes::FixedRoom2D::Configuration* source_configuration=nullptr, AllegroFlare::InventoryIndex* destination_inventory_index=nullptr, AllegroFlare::Inventory* destination_af_inventory=nullptr, AllegroFlare::Inventory* destination_flags=nullptr, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* destination_entity_dictionary=nullptr, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* destination_room_dictionary=nullptr, std::map<std::string, std::string>* destination_entity_room_associations=nullptr, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* destination_script_dictionary=nullptr);
            ~ConfigurationLoader();

            void set_source_configuration(AllegroFlare::Prototypes::FixedRoom2D::Configuration* source_configuration);
            void set_destination_inventory_index(AllegroFlare::InventoryIndex* destination_inventory_index);
            void set_destination_af_inventory(AllegroFlare::Inventory* destination_af_inventory);
            void set_destination_flags(AllegroFlare::Inventory* destination_flags);
            void set_destination_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* destination_entity_dictionary);
            void set_destination_room_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* destination_room_dictionary);
            void set_destination_entity_room_associations(std::map<std::string, std::string>* destination_entity_room_associations);
            void set_destination_script_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* destination_script_dictionary);
            AllegroFlare::Prototypes::FixedRoom2D::Configuration* get_source_configuration() const;
            AllegroFlare::InventoryIndex* get_destination_inventory_index() const;
            AllegroFlare::Inventory* get_destination_af_inventory() const;
            AllegroFlare::Inventory* get_destination_flags() const;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* get_destination_entity_dictionary() const;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* get_destination_room_dictionary() const;
            std::map<std::string, std::string>* get_destination_entity_room_associations() const;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* get_destination_script_dictionary() const;
            std::string get_starting_in_room_identifier() const;
            bool load_from_source_configuration();
         };
      }
   }
}



