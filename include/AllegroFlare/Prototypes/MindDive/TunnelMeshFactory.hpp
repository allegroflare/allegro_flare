#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>
#include <set>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class TunnelMeshFactory
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;

         protected:


         public:
            TunnelMeshFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            ~TunnelMeshFactory();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::Prototypes::MindDive::TunnelMesh* create_classic_random();
            AllegroFlare::Prototypes::MindDive::TunnelMesh* create_random_with_walls();
            void random_fill_excluding(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh=nullptr, std::set<int> exclusion_list={});
         };
      }
   }
}



