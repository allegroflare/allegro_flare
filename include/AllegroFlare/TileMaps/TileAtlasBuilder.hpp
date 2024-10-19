#pragma once


#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlasIndexRecord.hpp>
#include <allegro5/allegro.h>
#include <cstddef>
#include <vector>


namespace AllegroFlare
{
   namespace TileMaps
   {
      class TileAtlasBuilder
      {
      public:
         static constexpr std::size_t MIN_VALID_CREATE_PIXEL_PERFECT_SCALED_RENDER_SCALE_VALUE = 1;
         static constexpr std::size_t MAX_VALID_CREATE_PIXEL_PERFECT_SCALED_RENDER_SCALE_VALUE = 6;

      private:

      protected:


      public:
         TileAtlasBuilder();
         ~TileAtlasBuilder();

         static AllegroFlare::TileMaps::PrimMeshAtlas* create(ALLEGRO_BITMAP* source_bitmap=nullptr, int tile_width=16, int tile_height=16, int scale=3);
         static ALLEGRO_BITMAP* create_scaled_and_extruded(ALLEGRO_BITMAP* original_bitmap=nullptr, int scale=3, int tile_width=16, int tile_height=16);
         static ALLEGRO_BITMAP* create_extruded(std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord>* tile_index_=nullptr);
         static ALLEGRO_BITMAP* create_pixel_perfect_scaled_render(ALLEGRO_BITMAP* bitmap=nullptr, int scale=3);
         static bool validate_all_sub_bitmaps_in_tile_index_are_identical_sizes(std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord>* tile_index_=nullptr);
      };
   }
}



