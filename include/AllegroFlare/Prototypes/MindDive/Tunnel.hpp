#pragma once


#include <AllegroFlare/Prototypes/MindDive/TunnelTiles/Base.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class Tunnel
         {
         private:
            std::vector<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tiles;

         protected:


         public:
            Tunnel(std::vector<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tiles={});
            ~Tunnel();

            void set_tiles(std::vector<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> tiles);
            std::vector<AllegroFlare::Prototypes::MindDive::TunnelTiles::Base*> get_tiles() const;
            std::string fill();
         };
      }
   }
}



