#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityPool.hpp>
#include <AllegroFlare/RenderSurfaces/Bitmap.hpp>
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
            AllegroFlare::Shaders::Base* depth_map_shader;
            AllegroFlare::Camera3D casting_light;
            ALLEGRO_TRANSFORM casting_light_projection_transform;
            ALLEGRO_BITMAP* backbuffer_sub_bitmap;
            ALLEGRO_BITMAP* result_surface_bitmap;
            AllegroFlare::RenderSurfaces::Bitmap render_surface;
            bool backbuffer_is_setup;
            bool backbuffer_is_managed_by_this_class;

         protected:


         public:
            ShadowDepthMapRenderer(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool=nullptr);
            ~ShadowDepthMapRenderer();

            void set_entity_pool(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool);
            void set_casting_light(AllegroFlare::Camera3D casting_light);
            void set_casting_light_projection_transform(ALLEGRO_TRANSFORM casting_light_projection_transform);
            AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* get_entity_pool() const;
            AllegroFlare::Camera3D get_casting_light() const;
            ALLEGRO_TRANSFORM get_casting_light_projection_transform() const;
            ALLEGRO_BITMAP* get_backbuffer_sub_bitmap() const;
            AllegroFlare::Camera3D &get_casting_light_ref();
            ALLEGRO_BITMAP* get_result_surface_bitmap();
            void setup_backbuffer_from_display(ALLEGRO_DISPLAY* display=nullptr);
            void setup_result_surface_bitmap();
            void init_shader();
            void init_camera_defaults();
            void destroy();
            void render();
            void setup_projection_on_render_surface();
         };
      }
   }
}



