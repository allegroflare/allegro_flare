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
               AllegroFlare::MultitextureModel3D* multitexture_model_3d;
               ALLEGRO_BITMAP* multitexture_model_3d_texture_1;
               ALLEGRO_BITMAP* multitexture_model_3d_texture_2;
               AllegroFlare::Placement3D placement;

            protected:


            public:
               StaticMultitextureModel3D(AllegroFlare::MultitextureModel3D* multitexture_model_3d=nullptr, ALLEGRO_BITMAP* multitexture_model_3d_texture_1=nullptr, ALLEGRO_BITMAP* multitexture_model_3d_texture_2=nullptr, AllegroFlare::Placement3D placement={});
               ~StaticMultitextureModel3D();

               void set_multitexture_model_3d(AllegroFlare::MultitextureModel3D* multitexture_model_3d);
               void set_multitexture_model_3d_texture_1(ALLEGRO_BITMAP* multitexture_model_3d_texture_1);
               void set_multitexture_model_3d_texture_2(ALLEGRO_BITMAP* multitexture_model_3d_texture_2);
               AllegroFlare::MultitextureModel3D* get_multitexture_model_3d() const;
               ALLEGRO_BITMAP* get_multitexture_model_3d_texture_1() const;
               ALLEGRO_BITMAP* get_multitexture_model_3d_texture_2() const;
               AllegroFlare::Placement3D get_placement() const;
               AllegroFlare::Placement3D &get_placement_ref();
            };
         }
      }
   }
}



