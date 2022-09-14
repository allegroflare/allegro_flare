#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class TunnelRenderer
         {
         private:
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            TunnelRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh=nullptr);
            ~TunnelRenderer();

            void set_tunnel_mesh(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh);
            AllegroFlare::Prototypes::MindDive::TunnelMesh* get_tunnel_mesh() const;
            void render();
         };
      }
   }
}



