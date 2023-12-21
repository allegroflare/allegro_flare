#pragma once


#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Base.hpp>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace GraphicsPipelines
   {
      namespace DynamicEntityPipeline
      {
         class EntityPool
         {
         private:
            std::unordered_set<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> entity_pool;

         protected:


         public:
            EntityPool();
            ~EntityPool();

            void set_entity_pool(std::unordered_set<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> entity_pool);
            std::unordered_set<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> get_entity_pool() const;
            std::unordered_set<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> &get_entity_pool_ref();
            int num_elements();
            bool add(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* entity=nullptr);
            bool add(std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> entities);
            bool remove(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* entity=nullptr);
            int remove(std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> entities={});
            bool exists(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* entity=nullptr);
            AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* find_with_attribute(std::string attribute="[unset-attribute]");
            std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> find_all_with_attribute(std::string attribute="[unset-attribute]");
            std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> select_A(std::string attribute="[unset-attribute]");
            std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> select_B(std::vector<std::string> attributes={});
            std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> select_C(std::string attribute="[unset-attribute]", std::string parameter="[unset-parameter]");
            std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> select_D(std::vector<std::pair<std::string, std::string>> attribute_param_pairs={});
            std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> select_E(std::string attribute="[unset-attribute]", std::vector<std::pair<std::string, std::string>> attribute_param_pairs={});
            std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> select_F(std::vector<std::string> attributes={}, std::vector<std::pair<std::string, std::string>> attribute_param_pairs={});
         };
      }
   }
}



