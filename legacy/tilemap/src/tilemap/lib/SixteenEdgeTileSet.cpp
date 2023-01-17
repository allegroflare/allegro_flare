

#include <tilemap/lib/SixteenEdgeTileSet.hpp>
#include <tilemap/sprite_sheet.hpp>


SixteenEdgeTileSet::SixteenEdgeTileSet(
         ALLEGRO_BITMAP *top_left,
         ALLEGRO_BITMAP *top,
         ALLEGRO_BITMAP *top_right,
         ALLEGRO_BITMAP *top_tip,
         ALLEGRO_BITMAP *left,
         ALLEGRO_BITMAP *full,
         ALLEGRO_BITMAP *right,
         ALLEGRO_BITMAP *center,
         ALLEGRO_BITMAP *bottom_left,
         ALLEGRO_BITMAP *bottom,
         ALLEGRO_BITMAP *bottom_right,
         ALLEGRO_BITMAP *bottom_tip,
         ALLEGRO_BITMAP *left_tip,
         ALLEGRO_BITMAP *middle,
         ALLEGRO_BITMAP *right_tip,
         ALLEGRO_BITMAP *isolated
      )
   : set({
         top_left,
         top,
         top_right,
         top_tip,
         left,
         full,
         right,
         center,
         bottom_left,
         bottom,
         bottom_right,
         bottom_tip,
         left_tip,
         middle,
         right_tip,
         isolated,
      })
{}


SixteenEdgeTileSet::~SixteenEdgeTileSet()
{
}


ALLEGRO_BITMAP *SixteenEdgeTileSet::get_full_tile() { return set[full_index]; }


std::vector<ALLEGRO_BITMAP *> SixteenEdgeTileSet::get_set()
{
   return set;
}


