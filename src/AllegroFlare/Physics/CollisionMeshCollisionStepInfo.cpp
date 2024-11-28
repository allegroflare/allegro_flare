

#include <AllegroFlare/Physics/CollisionMeshCollisionStepInfo.hpp>




namespace AllegroFlare
{
namespace Physics
{


CollisionMeshCollisionStepInfo::CollisionMeshCollisionStepInfo(float time, void* entity, AllegroFlare::Vec3D* entity_position, AllegroFlare::Vec3D* entity_velocity, AllegroFlare::Physics::CollisionMeshFace* colliding_face)
   : time(time)
   , entity(entity)
   , entity_position(entity_position)
   , entity_velocity(entity_velocity)
   , colliding_face(colliding_face)
{
}


CollisionMeshCollisionStepInfo::~CollisionMeshCollisionStepInfo()
{
}




} // namespace Physics
} // namespace AllegroFlare


