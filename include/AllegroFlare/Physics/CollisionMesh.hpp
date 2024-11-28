#pragma once


#include <AllegroFlare/ALLEGRO_VERTEX_WITH_NORMAL.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Physics/CollisionMeshFace.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>
#include <vector>


namespace AllegroFlare
{
   namespace Physics
   {
      class CollisionMesh
      {
      private:
         AllegroFlare::Model3D* model;
         std::vector<AllegroFlare::Physics::CollisionMeshFace> faces;
         bool loaded;

      protected:


      public:
         CollisionMesh();
         ~CollisionMesh();

         void set_model(AllegroFlare::Model3D* model);
         bool get_loaded() const;
         int get_num_faces();
         std::vector<AllegroFlare::Physics::CollisionMeshFace>& get_faces_ref();
         void load();
         void draw(ALLEGRO_COLOR col=ALLEGRO_COLOR{0.4, 0.41, 0.5, 0.6});
         static AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL _create_vtx(AllegroFlare::Vec3D vec={}, ALLEGRO_COLOR col=ALLEGRO_COLOR{0.4, 0.41, 0.5, 0.6});
      };
   }
}



