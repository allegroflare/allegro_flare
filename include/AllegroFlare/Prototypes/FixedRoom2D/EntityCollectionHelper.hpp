#pragma once


#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <map>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class EntityCollectionHelper
         {
         private:
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary;
            std::map<std::string, std::string>* entity_room_associations;

         public:
            EntityCollectionHelper(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary=nullptr, std::map<std::string, std::string>* entity_room_associations=nullptr);
            ~EntityCollectionHelper();

            void set_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary);
            void set_entity_room_associations(std::map<std::string, std::string>* entity_room_associations);
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* get_entity_dictionary();
            std::map<std::string, std::string>* get_entity_room_associations();
            std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> select_all_in_room(std::string room_name="[unset-room_name]");
            std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> select_all_unordered();
            std::string find_dictionary_name_of_entity_that_cursor_is_now_over();
            AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* find_entity_by_dictionary_name(std::string dictionary_listing_name=nullptr);
            std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> select_all_ordered_by_id(std::string room_name="[unset-room_name]");
            void get_entities_from_entity_names(std::vector<std::string> entity_names={});
            std::vector<std::string> select_all_entity_names_in_room_name(std::string room_name="[unset-room_name]");
         };
      }
   }
}



