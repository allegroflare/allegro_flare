#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityPool.hpp>
#include <AllegroFlare/Shaders/Base.hpp>
#include <allegro5/allegro.h>


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
            AllegroFlare::Camera3D casting_light;
            ALLEGRO_TRANSFORM shadow_map_depth_pass_transform;
            ALLEGRO_BITMAP* backbuffer_sub_bitmap;
            AllegroFlare::Shaders::Base* depth_map_shader;
            bool backbuffer_is_setup;
            bool backbuffer_is_managed_by_this_class;

         protected:


         public:
            ShadowDepthMapRenderer(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool=nullptr);
            ~ShadowDepthMapRenderer();

            void set_entity_pool(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool);
            void set_casting_light(AllegroFlare::Camera3D casting_light);
            void set_shadow_map_depth_pass_transform(ALLEGRO_TRANSFORM shadow_map_depth_pass_transform);
            AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* get_entity_pool() const;
            AllegroFlare::Camera3D get_casting_light() const;
            ALLEGRO_TRANSFORM get_shadow_map_depth_pass_transform() const;
            ALLEGRO_BITMAP* get_backbuffer_sub_bitmap() const;
            void setup_backbuffer_from_display(ALLEGRO_DISPLAY* display=nullptr);
            void init_shader();
            void destroy();
            void render();
            void setup_projection_SHADOW();
         };
      }
   }
}



