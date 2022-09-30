

#include <AllegroFlare/Prototypes/MindDive/TunnelMeshSurferCollisionResolver.hpp>

#include <AllegroFlare/Physics/TileMapCollisionStepper.hpp>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


TunnelMeshSurferCollisionResolver::TunnelMeshSurferCollisionResolver(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh, AllegroFlare::Vec3D* surfer_position, AllegroFlare::Vec3D* surfer_velocity)
   : tunnel_mesh(tunnel_mesh)
   , surfer_position(surfer_position)
   , surfer_velocity(surfer_velocity)
{
}


TunnelMeshSurferCollisionResolver::~TunnelMeshSurferCollisionResolver()
{
}


void TunnelMeshSurferCollisionResolver::set_tunnel_mesh(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh)
{
   this->tunnel_mesh = tunnel_mesh;
}


void TunnelMeshSurferCollisionResolver::set_surfer_position(AllegroFlare::Vec3D* surfer_position)
{
   this->surfer_position = surfer_position;
}


void TunnelMeshSurferCollisionResolver::set_surfer_velocity(AllegroFlare::Vec3D* surfer_velocity)
{
   this->surfer_velocity = surfer_velocity;
}


AllegroFlare::Prototypes::MindDive::TunnelMesh* TunnelMeshSurferCollisionResolver::get_tunnel_mesh() const
{
   return tunnel_mesh;
}


AllegroFlare::Vec3D* TunnelMeshSurferCollisionResolver::get_surfer_position() const
{
   return surfer_position;
}


AllegroFlare::Vec3D* TunnelMeshSurferCollisionResolver::get_surfer_velocity() const
{
   return surfer_velocity;
}


void TunnelMeshSurferCollisionResolver::resolve_classic()
{
   surfer_position->x += surfer_velocity->x * 0.01;
   surfer_position->z += surfer_velocity->z * 0.01;
   return;
}

void TunnelMeshSurferCollisionResolver::resolve()
{
   if (!(tunnel_mesh))
   {
      std::stringstream error_message;
      error_message << "TunnelMeshSurferCollisionResolver" << "::" << "resolve" << ": error: " << "guard \"tunnel_mesh\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(surfer_position))
   {
      std::stringstream error_message;
      error_message << "TunnelMeshSurferCollisionResolver" << "::" << "resolve" << ": error: " << "guard \"surfer_position\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(surfer_velocity))
   {
      std::stringstream error_message;
      error_message << "TunnelMeshSurferCollisionResolver" << "::" << "resolve" << ": error: " << "guard \"surfer_velocity\" not met";
      throw std::runtime_error(error_message.str());
   }
   // make an AABB2D to represent the surfer
   float surfer_size = 0.2;
   float surfer_hsize = surfer_size * 0.5;
   AllegroFlare::Physics::AABB2D aabb2d(
      surfer_position->x - surfer_hsize,
      surfer_position->z - surfer_hsize,
      surfer_size,
      surfer_size,
      surfer_velocity->x * 0.01,
      surfer_velocity->z * 0.01
   );

   // create a collision stepper
   AllegroFlare::Physics::TileMapCollisionStepper collision_stepper(
      &tunnel_mesh->get_collision_tile_map_ref(), 
      &aabb2d,
      tunnel_mesh->obtain_tile_width(),
      tunnel_mesh->obtain_tile_height()
   );

   // step the collision and collect the collision info
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> collision_info =
      collision_stepper.step();

   if (!collision_info.empty())
   {
      std::cout << "COLLISIONS: " << collision_info.size() << std::endl;
      std::cout << "  - [0] tile_value: " << collision_info[0].get_tile_value() << std::endl;
      std::cout << "        coord_x:    " << collision_info[0].get_collided_tile_coordinate().get_x() << std::endl;
      std::cout << "        coord_y:    " << collision_info[0].get_collided_tile_coordinate().get_y() << std::endl;
   }

   // reposition our surfer to the stepper-modified aabb2d
   surfer_position->x = aabb2d.get_x() + surfer_hsize;
   surfer_position->z = aabb2d.get_y() + surfer_hsize;
   surfer_velocity->x = (aabb2d.get_velocity_x() * 100);
   surfer_velocity->z = (aabb2d.get_velocity_y() * 100);
      
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


