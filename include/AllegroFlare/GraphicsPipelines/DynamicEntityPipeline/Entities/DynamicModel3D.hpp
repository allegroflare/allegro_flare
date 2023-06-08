#pragma once


#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Base.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace GraphicsPipelines
   {
      namespace DynamicEntityPipeline
      {
         namespace Entities
         {
            class DynamicModel3D : public AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/DynamicModel3D";

            private:
               AllegroFlare::Model3D* model_3d;
               ALLEGRO_BITMAP* model_3d_texture;
               AllegroFlare::Placement3D placement;
               AllegroFlare::Placement3D velocity;

            protected:


            public:
               DynamicModel3D(AllegroFlare::Model3D* model_3d=nullptr, ALLEGRO_BITMAP* model_3d_texture=nullptr, AllegroFlare::Placement3D placement={}, AllegroFlare::Placement3D velocity={});
               ~DynamicModel3D();

               void set_model_3d(AllegroFlare::Model3D* model_3d);
               void set_model_3d_texture(ALLEGRO_BITMAP* model_3d_texture);
               AllegroFlare::Model3D* get_model_3d() const;
               ALLEGRO_BITMAP* get_model_3d_texture() const;
               AllegroFlare::Placement3D get_placement() const;
               AllegroFlare::Placement3D get_velocity() const;
               AllegroFlare::Placement3D &get_placement_ref();
               AllegroFlare::Placement3D &get_velocity_ref();
            };
         }
      }
   }
}



