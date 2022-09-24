#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>


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
         };
      }
   }
}



