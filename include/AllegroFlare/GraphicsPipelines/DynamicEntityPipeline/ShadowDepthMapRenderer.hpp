#pragma once


#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityPool.hpp>
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
            ALLEGRO_BITMAP* backbuffer_sub_bitmap;
            bool backbuffer_is_setup;
            bool backbuffer_is_managed_by_this_class;

         protected:


         public:
            ShadowDepthMapRenderer(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool=nullptr);
            ~ShadowDepthMapRenderer();

            void set_entity_pool(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool);
            void set_backbuffer_sub_bitmap(ALLEGRO_BITMAP* backbuffer_sub_bitmap);
            AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* get_entity_pool() const;
            ALLEGRO_BITMAP* get_backbuffer_sub_bitmap() const;
            ALLEGRO_BITMAP* &get_backbuffer_sub_bitmap_ref();
            void setup_backbuffer_from_display(ALLEGRO_DISPLAY* display=nullptr);
            void destroy();
            void render();
            void setup_projection_SHADOW();
         };
      }
   }
}



