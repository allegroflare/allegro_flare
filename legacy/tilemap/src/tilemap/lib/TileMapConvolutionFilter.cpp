

#include <tilemap/lib/TileMapConvolutionFilter.hpp>

#include <tilemap/lib/TileMapConvolutionBehavior/Base.hpp>
#include <tilemap/lib/TileMapConvolutionBehavior/SixteenTileNeighborBehavior.hpp>
#include <sstream>


void TileMapConvolutionFilter::set_behavior(TileMapConvolutionBehavior::behavior_t behavior_type)
{
   std::stringstream error_message;
   switch (behavior_type)
   {
   case TileMapConvolutionBehavior::SIXTEEN_TILE_NEIGHBOR_BEHAVIOR:
      if (filter_behavior != nullptr) delete filter_behavior;
      filter_behavior = new TileMapConvolutionBehavior::SixteenTileNeighborBehavior;
      break;
   default:
      error_message << "TileMapConvolutionFilter: Type \"" << behavior_type << "\" not implemented";
      throw std::runtime_error(error_message.str());
      break;
   }
}


TileMapConvolutionFilter::TileMapConvolutionFilter(
         TileMapConvolutionBehavior::behavior_t behavior_type,
         const std::vector<ALLEGRO_BITMAP *> tile_set,
         const TileMap *source_tilemap,
         TileMap *destination_tilemap
      )
   : filter_behavior(nullptr)
   , tile_set(tile_set)
   , source_tilemap(source_tilemap)
   , destination_tilemap(destination_tilemap)
{
   set_behavior(behavior_type);
}


TileMapConvolutionFilter::~TileMapConvolutionFilter()
{
   if (filter_behavior != nullptr) delete filter_behavior;
}


void TileMapConvolutionFilter::process(ALLEGRO_BITMAP *source_comparison_tile)
{
   if (filter_behavior) filter_behavior->execute(source_comparison_tile, tile_set, source_tilemap, destination_tilemap);
}


