#pragma once


#include <AllegroFlare/Prototypes/MindDive/TunnelTiles/Base.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class Tunnel
         {
         private:
            AllegroFlare::TileMaps::TileMap<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tile_map;

         protected:


         public:
            Tunnel(AllegroFlare::TileMaps::TileMap<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tile_map={});
            ~Tunnel();

            void set_tile_map(AllegroFlare::TileMaps::TileMap<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tile_map);
            AllegroFlare::TileMaps::TileMap<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> get_tile_map() const;
            void fill();
         };
      }
   }
}



