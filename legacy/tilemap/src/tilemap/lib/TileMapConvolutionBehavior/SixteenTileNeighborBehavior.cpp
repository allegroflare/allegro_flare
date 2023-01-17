

#include <tilemap/lib/TileMapConvolutionBehavior/SixteenTileNeighborBehavior.hpp>

#include <tilemap/lib/TileNeighborMatcher.hpp>


static int match_int(ALLEGRO_BITMAP *tile_to_match, ALLEGRO_BITMAP *current_tile)
{
   return (tile_to_match == current_tile) ? 1 : 2;
}


inline static int m(const TileMap *tile_map, int x, int y, ALLEGRO_BITMAP *tile_to_match)
{
   ALLEGRO_BITMAP *current_tile = tile_map->get_tile(x, y);
   return match_int(tile_to_match, current_tile);
}


namespace TileMapConvolutionBehavior
{


SixteenTileNeighborBehavior::SixteenTileNeighborBehavior()
   : Base()
{
}


SixteenTileNeighborBehavior::~SixteenTileNeighborBehavior()
{
}


void SixteenTileNeighborBehavior::execute(
      ALLEGRO_BITMAP *source_comparison_tile,
      const std::vector<ALLEGRO_BITMAP *> tile_set,
      const TileMap *source_tilemap,
      TileMap *destination_tilemap
   )
{
   if (!destination_tilemap) throw std::runtime_error("Cannot TileMapConvolutionFilter::process() on a nullptr destination_tilemap.");
   if (!source_tilemap) throw std::runtime_error("Cannot TileMapConvolutionFilter::process() on a nullptr source_tilemap.");
   if (tile_set.size() != 16) throw std::runtime_error("Cannot TileMapConvolutionFilter::process(), expecting tile_set.size() to == 16.");
   if (destination_tilemap->get_width() != source_tilemap->get_width() || destination_tilemap->get_height() != source_tilemap->get_height())
      throw std::runtime_error("TileMapConvolutionFilter::process(), Width and height must match between source_tilemap and destination_tilemap");

   TileNeighborMatcher tile_neighbor_matcher;
   int width = source_tilemap->get_width();
   int height = source_tilemap->get_height();

   ALLEGRO_BITMAP *TOP_LEFT     = tile_set[0];
   ALLEGRO_BITMAP *TOP          = tile_set[1];
   ALLEGRO_BITMAP *TOP_RIGHT    = tile_set[2];
   ALLEGRO_BITMAP *TOP_TIP      = tile_set[3];
   ALLEGRO_BITMAP *LEFT         = tile_set[4];
   ALLEGRO_BITMAP *FULL         = tile_set[5];
   ALLEGRO_BITMAP *RIGHT        = tile_set[6];
   ALLEGRO_BITMAP *CENTER       = tile_set[7];
   ALLEGRO_BITMAP *BOTTOM_LEFT  = tile_set[8];
   ALLEGRO_BITMAP *BOTTOM       = tile_set[9];
   ALLEGRO_BITMAP *BOTTOM_RIGHT = tile_set[10];
   ALLEGRO_BITMAP *BOTTOM_TIP   = tile_set[11];
   ALLEGRO_BITMAP *LEFT_TIP     = tile_set[12];
   ALLEGRO_BITMAP *MIDDLE       = tile_set[13];
   ALLEGRO_BITMAP *RIGHT_TIP    = tile_set[14];
   ALLEGRO_BITMAP *ISOLATED     = tile_set[15];

   typedef std::pair<int const (*)[3], ALLEGRO_BITMAP *> comparitor_t;
   std::vector<comparitor_t> comparitors = {
      { tile_neighbor_matcher.top_left, TOP_LEFT },
      { tile_neighbor_matcher.top, TOP },
      { tile_neighbor_matcher.top_right, TOP_RIGHT },
      { tile_neighbor_matcher.top_tip, TOP_TIP },
      { tile_neighbor_matcher.left, LEFT},
      { tile_neighbor_matcher.full, FULL },
      { tile_neighbor_matcher.right, RIGHT },
      { tile_neighbor_matcher.center, CENTER },
      { tile_neighbor_matcher.bottom_left, BOTTOM_LEFT },
      { tile_neighbor_matcher.bottom, BOTTOM },
      { tile_neighbor_matcher.bottom_right, BOTTOM_RIGHT },
      { tile_neighbor_matcher.bottom_tip, BOTTOM_TIP },
      { tile_neighbor_matcher.left_tip, LEFT_TIP },
      { tile_neighbor_matcher.middle, MIDDLE },
      { tile_neighbor_matcher.right_tip, RIGHT_TIP },
      { tile_neighbor_matcher.isolated, ISOLATED },
   };

   for (unsigned y=0; y<height; y++)
      for (unsigned x=0; x<width; x++)
      {
         const int context_matrix[3][3] = { { m(source_tilemap, x-1, y-1, source_comparison_tile), m(source_tilemap, x+0, y-1, source_comparison_tile), m(source_tilemap, x+1, y-1, source_comparison_tile) },
                                            { m(source_tilemap, x-1, y+0, source_comparison_tile), m(source_tilemap, x+0, y+0, source_comparison_tile), m(source_tilemap, x+1, y+0, source_comparison_tile) },
                                            { m(source_tilemap, x-1, y+1, source_comparison_tile), m(source_tilemap, x+0, y+1, source_comparison_tile), m(source_tilemap, x+1, y+1, source_comparison_tile) } };

         for (auto &comparitor : comparitors)
         {
            if (tile_neighbor_matcher.match(comparitor.first, 1, context_matrix))
            {
               destination_tilemap->set_tile(x, y, comparitor.second);
               break;
            }
         }
      }
}


} // TileMapConvolutionBehavior


