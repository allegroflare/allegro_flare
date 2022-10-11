#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TerrainMesh.hpp>
#include <set>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace TileDrive
      {
         class TerrainMeshFactory
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;

         protected:


         public:
            TerrainMeshFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            ~TerrainMeshFactory();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::Prototypes::TileDrive::TerrainMesh* create_classic_random();
            AllegroFlare::Prototypes::TileDrive::TerrainMesh* create_random_with_walls();
            AllegroFlare::Prototypes::TileDrive::TerrainMesh* create_from_tmj(std::string tmj_filename="unset-tmj_filename.tmj");
            void random_fill_from(AllegroFlare::Prototypes::TileDrive::TerrainMesh* terrain_mesh=nullptr, std::vector<std::pair<int, int>> inclusion_list={});
            void random_sparce_placement(AllegroFlare::Prototypes::TileDrive::TerrainMesh* terrain_mesh=nullptr, std::vector<std::pair<int, int>> inclusion_list={}, int one_in_chance=2);
            void random_fill_excluding(AllegroFlare::Prototypes::TileDrive::TerrainMesh* terrain_mesh=nullptr, std::set<int> exclusion_list={});
         };
      }
   }
}



