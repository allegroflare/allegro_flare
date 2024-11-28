#pragma once


#include <AllegroFlare/ALLEGRO_VERTEX_WITH_NORMAL.hpp>
#include <AllegroFlare/Physics/CollisionMeshFace.hpp>
#include <AllegroFlare/Useful3D/IntersectData.hpp>
#include <AllegroFlare/Useful3D/Ray.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Physics
   {
      class CollisionMeshFace
      {
      private:

      protected:


      public:
         AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av0;
         AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av1;
         AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av2;
         AllegroFlare::Vec3D v0;
         AllegroFlare::Vec3D v1;
         AllegroFlare::Vec3D v2;
         AllegroFlare::Vec3D normal;
         AllegroFlare::Vec3D centroid;
         int parent_models_object_num;
         int parent_models_face_num;
         CollisionMeshFace();
         ~CollisionMeshFace();

         static AllegroFlare::Physics::CollisionMeshFace build(AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av0={}, AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av1={}, AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av2={}, int parent_models_object_num=0, int parent_models_face_num=0, AllegroFlare::Vec3D normal={});
         bool intersect(AllegroFlare::Useful3D::Ray* r=nullptr, AllegroFlare::Useful3D::IntersectData* isectData=nullptr);
         void draw(ALLEGRO_COLOR col=ALLEGRO_COLOR{0.4, 0.41, 0.5, 0.6});
         static AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL _create_vtx(AllegroFlare::Vec3D vec={}, ALLEGRO_COLOR col=ALLEGRO_COLOR{0.4, 0.41, 0.5, 0.6});
      };
   }
}



