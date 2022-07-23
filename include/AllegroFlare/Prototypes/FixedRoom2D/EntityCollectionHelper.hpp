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
            std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entities;

         public:
            EntityCollectionHelper(std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entities=nullptr);
            ~EntityCollectionHelper();

            void set_entities(std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entities);
            std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* get_entities();
            std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> select_all_in_room(std::string room_name="[unset-room_name]");
         };
      }
   }
}



