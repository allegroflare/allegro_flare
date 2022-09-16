#pragma once


//#include <Tileo/TileIndexInfo.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlasIndexRecord.hpp>
#include <allegro5/allegro.h>
#include <vector>


class TileAtlasBuilder
{
private:
   int tile_w;
   int tile_h;
   std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index;

public:
   TileAtlasBuilder(int tile_w=0, int tile_h=0, std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index={});
   ~TileAtlasBuilder();

   ALLEGRO_BITMAP *build_extruded();
   static ALLEGRO_BITMAP *build_scaled_and_extruded(ALLEGRO_BITMAP *bitmap=nullptr, int scale=3);

   static ALLEGRO_BITMAP *create_pixel_perfect_scaled_render(ALLEGRO_BITMAP *bitmap=nullptr, int scale=4);
};



