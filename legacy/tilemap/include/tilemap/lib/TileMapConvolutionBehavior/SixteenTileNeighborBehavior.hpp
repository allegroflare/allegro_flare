#pragma once


#include <tilemap/lib/TileMapConvolutionBehavior/Base.hpp>


namespace TileMapConvolutionBehavior
{
   class SixteenTileNeighborBehavior : public Base
   {
   public:
      SixteenTileNeighborBehavior();
      ~SixteenTileNeighborBehavior();

      virtual void execute(
            ALLEGRO_BITMAP *source_comparison_tile,
            const std::vector<ALLEGRO_BITMAP *> tile_set,
            const TileMap *source_tilemap,
            TileMap *destination_tilemap
         ) override;
   };
}


