#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/TileMaps/Basic2D.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         class EntityCollectionHelper
         {
         private:
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>* entities;

         protected:


         public:
            EntityCollectionHelper(std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>* entities=nullptr);
            ~EntityCollectionHelper();

            void set_entities(std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>* entities);
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>* get_entities() const;
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> select_collectable_by_player();
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> select_collides_with_player();
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> select_goalposts();
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> select_save_points();
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> select_doors();
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> select_on_map(std::string on_map_name="[on-map-name-not-set]");
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> select_on_map_y_sorted(std::string on_map_name="[on-map-name-not-set]");
            AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* find_map_by_name(std::string map_name="[find-map-name-not-set]");
         };
      }
   }
}



