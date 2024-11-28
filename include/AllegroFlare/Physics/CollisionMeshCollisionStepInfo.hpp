#pragma once


#include <AllegroFlare/Physics/CollisionMeshFace.hpp>
#include <AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{
   namespace Physics
   {
      class CollisionMeshCollisionStepInfo
      {
      private:

      protected:


      public:
         float time;
         void* entity;
         AllegroFlare::Vec3D* entity_position;
         AllegroFlare::Vec3D* entity_velocity;
         AllegroFlare::Physics::CollisionMeshFace* colliding_face;
         CollisionMeshCollisionStepInfo(float time=0.0f, void* entity=nullptr, AllegroFlare::Vec3D* entity_position=nullptr, AllegroFlare::Vec3D* entity_velocity=nullptr, AllegroFlare::Physics::CollisionMeshFace* colliding_face=nullptr);
         ~CollisionMeshCollisionStepInfo();

      };
   }
}



