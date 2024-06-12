

#include <AllegroFlare/Prototypes/MindDive/TunnelRenderer.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
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
      error_message << "[AllegroFlare::Prototypes::MindDive::TunnelRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::TunnelRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::TunnelRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::TunnelRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


