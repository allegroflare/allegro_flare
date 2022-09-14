#pragma once


#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class TunnelRenderer
         {
         private:
            AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh;

         protected:


         public:
            TunnelRenderer(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh=nullptr);
            ~TunnelRenderer();

            void set_tunnel_mesh(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh);
            AllegroFlare::Prototypes::MindDive::TunnelMesh* get_tunnel_mesh() const;
            void render();
         };
      }
   }
}



