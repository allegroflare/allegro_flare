#pragma once


#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Base.hpp>
#include <AllegroFlare/Placement3D.hpp>


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
               AllegroFlare::Placement3D placement;

            protected:


            public:
               StaticModel3D(AllegroFlare::Placement3D placement={});
               ~StaticModel3D();

               AllegroFlare::Placement3D get_placement() const;
               AllegroFlare::Placement3D &get_placement_ref();
            };
         }
      }
   }
}



