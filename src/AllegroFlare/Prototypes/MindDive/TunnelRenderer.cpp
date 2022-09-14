

#include <AllegroFlare/Prototypes/MindDive/TunnelRenderer.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_primitives.h>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


TunnelRenderer::TunnelRenderer(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh)
   : tunnel_mesh(tunnel_mesh)
{
}


TunnelRenderer::~TunnelRenderer()
{
}


void TunnelRenderer::set_tunnel_mesh(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh)
{
   this->tunnel_mesh = tunnel_mesh;
}


AllegroFlare::Prototypes::MindDive::TunnelMesh* TunnelRenderer::get_tunnel_mesh() const
{
   return tunnel_mesh;
}


void TunnelRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "TunnelRenderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "TunnelRenderer" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


