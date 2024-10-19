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

      protected:


      public:
         TileAtlasBuilder();
         ~TileAtlasBuilder();

         static ALLEGRO_BITMAP* create_extruded(std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord>* tile_index_=nullptr);
         static ALLEGRO_BITMAP* create_scaled_and_extruded(ALLEGRO_BITMAP* original_bitmap=nullptr, int scale=3, int tile_width=16, int tile_height=16);
         static ALLEGRO_BITMAP* create_pixel_perfect_scaled_render(ALLEGRO_BITMAP* bitmap=nullptr, int scale=3);
         static bool validate_all_sub_bitmaps_in_tile_index_are_identical_sizes(std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord>* tile_index_=nullptr);
      };
   }
}



