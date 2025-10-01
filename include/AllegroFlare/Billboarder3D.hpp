#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/Placement3D.hpp>


namespace AllegroFlare
{
   class Billboarder3D
   {
   private:
      AllegroFlare::Camera3D* camera;

   protected:


   public:
      Billboarder3D(AllegroFlare::Camera3D* camera=nullptr);
      ~Billboarder3D();

      void set_camera(AllegroFlare::Camera3D* camera);
      AllegroFlare::Camera3D* get_camera() const;
      void set_billboard_placement(AllegroFlare::Placement3D* placement=nullptr);
   };
}



