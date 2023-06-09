#pragma once


#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Base.hpp>
#include <AllegroFlare/MultitextureModel3D.hpp>
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
            class StaticMultitextureModel3D : public AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticMultitextureModel3D";

            private:
               AllegroFlare::MultitextureModel3D* model_3d;
               ALLEGRO_BITMAP* model_3d_texture;
               AllegroFlare::Placement3D placement;

            protected:


            public:
               StaticMultitextureModel3D(AllegroFlare::MultitextureModel3D* model_3d=nullptr, ALLEGRO_BITMAP* model_3d_texture=nullptr, AllegroFlare::Placement3D placement={});
               ~StaticMultitextureModel3D();

               void set_model_3d(AllegroFlare::MultitextureModel3D* model_3d);
               void set_model_3d_texture(ALLEGRO_BITMAP* model_3d_texture);
               AllegroFlare::MultitextureModel3D* get_model_3d() const;
               ALLEGRO_BITMAP* get_model_3d_texture() const;
               AllegroFlare::Placement3D get_placement() const;
               AllegroFlare::Placement3D &get_placement_ref();
            };
         }
      }
   }
}



