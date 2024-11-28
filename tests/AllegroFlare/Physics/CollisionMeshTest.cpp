
#include <gtest/gtest.h>

#include <AllegroFlare/Physics/CollisionMesh.hpp>


TEST(AllegroFlare_Physics_CollisionMeshTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Physics::CollisionMesh collision_mesh;
}


// Note the majority of testing for this class was done in the Physics/CollisionMeshCollisionStepper

/*
   std::vector<Face> faces;
   AllegroFlare::Model3D *model;

   CollisionMesh(AllegroFlare::Model3D *m);
   void draw(ALLEGRO_COLOR col=AllegroFlare::color::azure);
*/


