

#include <AllegroFlare/Prototypes/MindDive/Tunnel.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


Tunnel::Tunnel(AllegroFlare::TileMap<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tile_map)
   : tile_map(tile_map)
{
}


Tunnel::~Tunnel()
{
}


void Tunnel::set_tile_map(AllegroFlare::TileMap<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tile_map)
{
   this->tile_map = tile_map;
}


AllegroFlare::TileMap<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> Tunnel::get_tile_map() const
{
   return tile_map;
}


void Tunnel::fill()
{
   tile_map.resize(6, 80);
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


