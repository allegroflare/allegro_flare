#pragma once




#include <allegro5/allegro.h>
#include <AllegroFlare/Vec3D.hpp>



namespace allegro_flare
{
   class placement3d
   {
   private:
      ALLEGRO_TRANSFORM previous_transform;

   public:
      AllegroFlare::vec3d position, size, align, scale, anchor, rotation;

      placement3d();
      placement3d(float x, float y, float z);
      placement3d(AllegroFlare::vec3d position);

      void start_transform();
      void restore_transform();
      void build_transform(ALLEGRO_TRANSFORM *transform);
      void build_reverse_transform(ALLEGRO_TRANSFORM *transform);

      placement3d& operator+=(const placement3d& other);
      bool operator==(const placement3d& other) const;

      AllegroFlare::vec3d get_real_position();

      bool collide(float x, float y, float z); // not implemented
      bool fcollide(float x, float y, float z, float d); // not implemented
   };
}



