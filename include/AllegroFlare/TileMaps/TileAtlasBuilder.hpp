#pragma once


#include <AllegroFlare/TileMaps/PrimMeshAtlasIndexRecord.hpp>
#include <allegro5/allegro.h>
#include <vector>


namespace AllegroFlare
{
   namespace TileMaps
   {
      class TileAtlasBuilder
      {
      private:
         int tile_w;
         int tile_h;
         std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index;

      protected:


      public:
         TileAtlasBuilder(int tile_w=16, int tile_h=16, std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index={});
         ~TileAtlasBuilder();

         bool validate_all_sub_bitmaps_in_tile_index_are_identical_sizes();
         ALLEGRO_BITMAP* build_extruded();
         static ALLEGRO_BITMAP* build_scaled_and_extruded(ALLEGRO_BITMAP* original_bitmap=nullptr, int scale=3, int tile_width=16, int tile_height=16);
         static ALLEGRO_BITMAP* create_pixel_perfect_scaled_render(ALLEGRO_BITMAP* bitmap=nullptr, int scale=3);
      };
   }
}



