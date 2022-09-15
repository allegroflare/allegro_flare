#pragma once


#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/TileMaps/Basic2D.hpp>
#include <string>
#include <vector>


namespace Wicked
{
   namespace Entities
   {
      class CollectionHelper
      {
      private:
         std::vector<Wicked::Entities::Basic2D*>* entities;

      protected:


      public:
         CollectionHelper(std::vector<Wicked::Entities::Basic2D*>* entities=nullptr);
         ~CollectionHelper();

         void set_entities(std::vector<Wicked::Entities::Basic2D*>* entities);
         std::vector<Wicked::Entities::Basic2D*>* get_entities() const;
         std::vector<Wicked::Entities::Basic2D*> select_collectable_by_player();
         std::vector<Wicked::Entities::Basic2D*> select_goalposts();
         std::vector<Wicked::Entities::Basic2D*> select_doors();
         std::vector<Wicked::Entities::Basic2D*> select_on_map(std::string on_map_name="[on-map-name-not-set]");
         Wicked::TileMaps::Basic2D* find_map_by_name(std::string map_name="[find-map-name-not-set]");
      };
   }
}



