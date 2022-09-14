#pragma once


#include <AllegroFlare/Prototypes/MindDive/TunnelTiles/Base.hpp>
#include <AllegroFlare/TileMap.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class Tunnel
         {
         private:
            AllegroFlare::TileMap<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tile_map;

         protected:


         public:
            Tunnel(AllegroFlare::TileMap<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tile_map={});
            ~Tunnel();

            void set_tile_map(AllegroFlare::TileMap<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tile_map);
            AllegroFlare::TileMap<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> get_tile_map() const;
            void fill();
         };
      }
   }
}



