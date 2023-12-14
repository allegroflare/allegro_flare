#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Base.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityPool.hpp>
#include <AllegroFlare/MultitextureModel3D.hpp>
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
            AllegroFlare::RenderSurfaces::Bitmap render_surface;
            bool render_surface_is_setup;

         protected:


         public:
            ShadowDepthMapRenderer(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool=nullptr);
            ~ShadowDepthMapRenderer();

            void set_entity_pool(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool);
            void set_casting_light(AllegroFlare::Camera3D casting_light);
            AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* get_entity_pool() const;
            AllegroFlare::Camera3D get_casting_light() const;
            AllegroFlare::Camera3D &get_casting_light_ref();
            ALLEGRO_BITMAP* get_result_surface_bitmap();
            void setup_result_surface_bitmap(int width=1920, int height=1080);
            void init_shader();
            void init_camera_defaults();
            void destroy();
            void render();
            void setup_projection_on_render_surface();
            AllegroFlare::MultitextureModel3D* get_multitexture_model_3d(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* entity=nullptr);
            void render_multitexture_model_3d(AllegroFlare::MultitextureModel3D* multitexture_model_3d=nullptr);
         };
      }
   }
}



