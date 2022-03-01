#pragma once




#include <allegro5/allegro.h>
#include <AllegroFlare/Vec3D.hpp>



namespace AllegroFlare
{
   class Placement3D
   {
   private:
      ALLEGRO_TRANSFORM previous_transform;

   public:
      AllegroFlare::vec3d position, size, align, scale, anchor, rotation;

      Placement3D();
      Placement3D(float x, float y, float z);
      Placement3D(AllegroFlare::vec3d position);

      void start_transform();
      void restore_transform();
      void build_transform(ALLEGRO_TRANSFORM *transform);
      void build_reverse_transform(ALLEGRO_TRANSFORM *transform);

      Placement3D& operator+=(const Placement3D& other);
      bool operator==(const Placement3D& other) const;

      AllegroFlare::vec3d get_real_position();

      bool collide(float x, float y, float z); // not implemented
      bool fcollide(float x, float y, float z, float d); // not implemented
   };
}



