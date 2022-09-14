#pragma once


#include <AllegroFlare/Prototypes/MindDive/Tunnel.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class MindDive
         {
         private:
            AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh;
            AllegroFlare::Prototypes::MindDive::Tunnel tunnel;

         protected:


         public:
            MindDive(AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh={}, AllegroFlare::Prototypes::MindDive::Tunnel tunnel={});
            ~MindDive();

            void set_tunnel_mesh(AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh);
            void set_tunnel(AllegroFlare::Prototypes::MindDive::Tunnel tunnel);
            AllegroFlare::Prototypes::MindDive::TunnelMesh get_tunnel_mesh() const;
            AllegroFlare::Prototypes::MindDive::Tunnel get_tunnel() const;
            void initialize();
            void render();
         };
      }
   }
}



