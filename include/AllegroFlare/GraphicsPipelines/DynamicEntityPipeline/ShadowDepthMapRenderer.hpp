#pragma once


#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityPool.hpp>


namespace AllegroFlare
{
   namespace GraphicsPipelines
   {
      namespace DynamicEntityPipeline
      {
         class ShadowDepthMapRenderer
         {
         private:
            AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool;

         protected:


         public:
            ShadowDepthMapRenderer(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool=nullptr);
            ~ShadowDepthMapRenderer();

            void set_entity_pool(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool);
            AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* get_entity_pool() const;
            void render();
         };
      }
   }
}



