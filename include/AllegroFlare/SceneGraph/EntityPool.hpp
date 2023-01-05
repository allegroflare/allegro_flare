#pragma once


#include <AllegroFlare/SceneGraph/Entities/Base.hpp>
#include <string>
#include <utility>
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

         bool add(AllegroFlare::SceneGraph::Entities::Base* entity=nullptr);
         bool remove(AllegroFlare::SceneGraph::Entities::Base* entity=nullptr);
         bool exists(AllegroFlare::SceneGraph::Entities::Base* entity=nullptr);
         std::vector<AllegroFlare::SceneGraph::Entities::Base*> select_A(std::string attribute="[unset-attribute]");
         std::vector<AllegroFlare::SceneGraph::Entities::Base*> select_B(std::vector<std::string> attributes={});
         std::vector<AllegroFlare::SceneGraph::Entities::Base*> select_C(std::string attribute="[unset-attribute]", std::string parameter="[unset-parameter]");
         std::vector<AllegroFlare::SceneGraph::Entities::Base*> select_D(std::vector<std::pair<std::string, std::string>> attribute_param_pairs={});
         std::vector<AllegroFlare::SceneGraph::Entities::Base*> select_E(std::string attribute="[unset-attribute]", std::vector<std::pair<std::string, std::string>> attribute_param_pairs={});
         std::vector<AllegroFlare::SceneGraph::Entities::Base*> select_F(std::vector<std::string> attributes={}, std::vector<std::pair<std::string, std::string>> attribute_param_pairs={});
      };
   }
}



