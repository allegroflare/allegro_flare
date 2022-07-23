#pragma once


#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
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

         public:
            EntityCollectionHelper(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary=nullptr);
            ~EntityCollectionHelper();

            void set_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary);
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* get_entity_dictionary();
            std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> select_all_in_room(std::string room_name="[unset-room_name]");
            std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> select_all_ordered_by_id(std::string room_name="[unset-room_name]");
         };
      }
   }
}



