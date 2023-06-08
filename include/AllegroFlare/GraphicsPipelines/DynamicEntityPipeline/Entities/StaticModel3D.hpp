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
            class StaticModel3D : public AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticModel3D";

            private:
               AllegroFlare::Model3D* model_3d;
               ALLEGRO_BITMAP* model_3d_texture;
               AllegroFlare::Placement3D placement;

            protected:


            public:
               StaticModel3D(AllegroFlare::Model3D* model_3d=nullptr, ALLEGRO_BITMAP* model_3d_texture=nullptr, AllegroFlare::Placement3D placement={});
               ~StaticModel3D();

               void set_model_3d(AllegroFlare::Model3D* model_3d);
               void set_model_3d_texture(ALLEGRO_BITMAP* model_3d_texture);
               AllegroFlare::Model3D* get_model_3d() const;
               ALLEGRO_BITMAP* get_model_3d_texture() const;
               AllegroFlare::Placement3D get_placement() const;
               AllegroFlare::Placement3D &get_placement_ref();
            };
         }
      }
   }
}



