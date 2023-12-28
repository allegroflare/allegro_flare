#pragma once


#include <AllegroFlare/Physics/AABB3D.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Physics
   {
      class AABB3D
      {
      private:
         AllegroFlare::Vec3D min;
         AllegroFlare::Vec3D max;

      protected:


      public:
         AABB3D(AllegroFlare::Vec3D min=AllegroFlare::Vec3D(), AllegroFlare::Vec3D max=AllegroFlare::Vec3D());
         ~AABB3D();

         void set_min(AllegroFlare::Vec3D min);
         void set_max(AllegroFlare::Vec3D max);
         AllegroFlare::Vec3D get_min() const;
         AllegroFlare::Vec3D get_max() const;
         void expand(float amount=0.0f);
         bool collides(AllegroFlare::Physics::AABB3D* other=nullptr, AllegroFlare::Vec3D self_offset=AllegroFlare::Vec3D(), AllegroFlare::Vec3D other_offset=AllegroFlare::Vec3D());
         bool collides_with_point(AllegroFlare::Vec3D point=AllegroFlare::Vec3D(), AllegroFlare::Vec3D self_offset=AllegroFlare::Vec3D(), AllegroFlare::Vec3D other_offset=AllegroFlare::Vec3D());
         void draw(ALLEGRO_COLOR color=ALLEGRO_COLOR{1.0f, 1.0f, 0.0f, 1.0f}, AllegroFlare::Vec3D offset=AllegroFlare::Vec3D());
      };
   }
}



