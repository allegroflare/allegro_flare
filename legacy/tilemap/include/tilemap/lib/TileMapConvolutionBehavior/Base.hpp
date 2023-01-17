#pragma once


#include <allegro5/allegro.h>
#include <tilemap/tile_map.hpp>
#include <vector>


namespace TileMapConvolutionBehavior
{
   class Base
   {
   public:
      Base();
      ~Base();

      virtual void execute(
            ALLEGRO_BITMAP *source_comparison_tile,
            const std::vector<ALLEGRO_BITMAP *> tile_set,
            const TileMap *source_tilemap,
            TileMap *destination_tilemap
         ) = 0;
   };
};


