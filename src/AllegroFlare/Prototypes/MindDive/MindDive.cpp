

#include <AllegroFlare/Prototypes/MindDive/MindDive.hpp>

#include <AllegroFlare/Prototypes/MindDive/TunnelRenderer.hpp>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


MindDive::MindDive(AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh, AllegroFlare::Prototypes::MindDive::Tunnel tunnel)
   : tunnel_mesh(tunnel_mesh)
   , tunnel(tunnel)
{
}


MindDive::~MindDive()
{
}


void MindDive::set_tunnel_mesh(AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh)
{
   this->tunnel_mesh = tunnel_mesh;
}


void MindDive::set_tunnel(AllegroFlare::Prototypes::MindDive::Tunnel tunnel)
{
   this->tunnel = tunnel;
}


AllegroFlare::Prototypes::MindDive::TunnelMesh MindDive::get_tunnel_mesh() const
{
   return tunnel_mesh;
}


AllegroFlare::Prototypes::MindDive::Tunnel MindDive::get_tunnel() const
{
   return tunnel;
}


void MindDive::initialize()
{
   // TODO
   return;
}

void MindDive::render()
{
   // TODO
   AllegroFlare::Prototypes::MindDive::TunnelRenderer tunnel_renderer(&tunnel_mesh);
   tunnel_renderer.render();
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


