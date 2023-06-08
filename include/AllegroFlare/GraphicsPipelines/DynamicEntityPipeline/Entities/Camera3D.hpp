#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Base.hpp>


namespace AllegroFlare
{
   namespace GraphicsPipelines
   {
      namespace DynamicEntityPipeline
      {
         namespace Entities
         {
            class Camera3D : public AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Camera3D";

            private:
               AllegroFlare::Camera3D camera_3d;

            protected:


            public:
               Camera3D(AllegroFlare::Camera3D camera_3d={});
               ~Camera3D();

               AllegroFlare::Camera3D get_camera_3d() const;
               AllegroFlare::Camera3D &get_camera_3d_ref();
            };
         }
      }
   }
}



