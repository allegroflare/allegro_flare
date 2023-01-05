#pragma once


#include <AllegroFlare/SceneGraph/Entities/Base.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace SceneGraph
   {
      class EntityPool
      {
      private:
         std::vector<AllegroFlare::SceneGraph::Entities::Base*> entity_pool;

      protected:


      public:
         EntityPool();
         ~EntityPool();

         std::vector<AllegroFlare::SceneGraph::Entities::Base*> select(std::string attribute="[unset-attribute]");
      };
   }
}



