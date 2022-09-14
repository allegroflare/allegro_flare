

#include <AllegroFlare/Prototypes/MindDive/Tunnel.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


Tunnel::Tunnel(std::vector<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tiles)
   : tiles(tiles)
{
}


Tunnel::~Tunnel()
{
}


void Tunnel::set_tiles(std::vector<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tiles)
{
   this->tiles = tiles;
}


std::vector<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> Tunnel::get_tiles() const
{
   return tiles;
}


std::string Tunnel::fill()
{
   return "Hello World!";
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


