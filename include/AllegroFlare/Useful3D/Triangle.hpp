#pragma once


#include <AllegroFlare/Useful3D/IntersectData.hpp>
#include <AllegroFlare/Useful3D/Ray.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Useful3D
   {
      class Triangle
      {
      private:

      protected:


      public:
         AllegroFlare::vec3d v0;
         AllegroFlare::vec3d v1;
         AllegroFlare::vec3d v2;
         Triangle(AllegroFlare::vec3d v0={}, AllegroFlare::vec3d v1={}, AllegroFlare::vec3d v2={});
         ~Triangle();

         bool intersect(AllegroFlare::Useful3D::Ray* ray_=nullptr, AllegroFlare::Useful3D::IntersectData* intersect_data=nullptr, bool backface_culling=false);
         void draw(ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      };
   }
}



