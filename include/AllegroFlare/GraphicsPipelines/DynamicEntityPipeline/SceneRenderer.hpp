#pragma once


#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Base.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityPool.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Shaders/Cubemap.hpp>


namespace AllegroFlare
{
   namespace GraphicsPipelines
   {
      namespace DynamicEntityPipeline
      {
         class SceneRenderer
         {
         private:
            AllegroFlare::Shaders::Cubemap* cubemap_shader;
            AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool;

         protected:


         public:
            SceneRenderer(AllegroFlare::Shaders::Cubemap* cubemap_shader=nullptr, AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool=nullptr);
            ~SceneRenderer();

            void set_cubemap_shader(AllegroFlare::Shaders::Cubemap* cubemap_shader);
            void set_entity_pool(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool);
            AllegroFlare::Shaders::Cubemap* get_cubemap_shader() const;
            AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* get_entity_pool() const;
            void render();
            AllegroFlare::Model3D* get_model_3d(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* entity=nullptr);
         };
      }
   }
}



