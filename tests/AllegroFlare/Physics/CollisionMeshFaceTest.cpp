
#include <gtest/gtest.h>

#include <AllegroFlare/Physics/CollisionMeshFace.hpp>


TEST(AllegroFlare_Physics_CollisionMeshFaceTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Physics::CollisionMeshFace face;
}


/*


   class Face
      // -is triangulated
      // the Face class is essentially
      // a chashed version of the model's
      // data, that can be quickly
      // used when calculating collisions.
      // for the most part, the member
      // variables should not be modified
      // because they are all interdependent
      // they are left public for accessibility
   {
   public:
      AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av0, av1, av2;
      AllegroFlare::vec3d v0, v1, v2;
      AllegroFlare::vec3d normal;
      AllegroFlare::vec3d centroid;
      
      int parent_models_object_num;
      int parent_models_face_num;

      Face(
         AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av0,
         AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av1,
         AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av2,
         int parent_models_object_num,
         int parent_models_face_num,
         AllegroFlare::vec3d normal=AllegroFlare::vec3d(0)
         );

      //bool intersect(const allegro_flare::Ray &r, allegro_flare::IsectData &isectData) const;
      bool intersect(const AllegroFlare::Useful3D::Ray &r, AllegroFlare::Useful3D::IntersectData &isectData) const;

      void draw(ALLEGRO_COLOR col=AllegroFlare::color::azure);
   };


*/

/*
         AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av0,
         AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av1,
         AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av1,
         AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av2,
         AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL av2,
         int parent_models_object_num,
         int parent_models_object_num,
         int parent_models_face_num,
         int parent_models_face_num,
         AllegroFlare::vec3d normal=AllegroFlare::vec3d(0)
         AllegroFlare::vec3d normal=AllegroFlare::vec3d(0)
*/

