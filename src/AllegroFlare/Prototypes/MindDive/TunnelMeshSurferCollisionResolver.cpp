

#include <AllegroFlare/Prototypes/MindDive/TunnelMeshSurferCollisionResolver.hpp>

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
   surfer_position->x += surfer_velocity->x * 0.01;
   surfer_position->z += surfer_velocity->z * 0.01;
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


