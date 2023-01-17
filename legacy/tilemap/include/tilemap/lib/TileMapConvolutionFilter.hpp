#pragma once


#include <tilemap/lib/TileMapConvolutionBehavior/types.hpp>
#include <allegro5/allegro.h>
#include <tilemap/tile_map.hpp>


namespace TileMapConvolutionBehavior { class Base; }


class TileMapConvolutionFilter
{
private:
   const std::vector<ALLEGRO_BITMAP *> tile_set;
   const TileMap *source_tilemap;
   TileMap *destination_tilemap;
   TileMapConvolutionBehavior::Base *filter_behavior;

   void set_behavior(TileMapConvolutionBehavior::behavior_t behavior_type);

public:
   TileMapConvolutionFilter(
         TileMapConvolutionBehavior::behavior_t behavior_type,
         const std::vector<ALLEGRO_BITMAP *> tile_set,
         const TileMap *source_tilemap,
         TileMap *destination_tilemap
      );
   ~TileMapConvolutionFilter();

   void process(ALLEGRO_BITMAP *source_comparison_tile);
};


