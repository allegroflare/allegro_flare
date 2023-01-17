#pragma once


#include <allegro5/allegro.h>
#include <tilemap/sprite_sheet.hpp>


class SixteenEdgeTileSet
{
private:
   std::vector<ALLEGRO_BITMAP *> set;
   static const int top_left_index     = 0;
   static const int top_index          = 1;
   static const int top_right_index    = 2;
   static const int top_tip_index      = 3;
   static const int left_index         = 4;
   static const int full_index         = 5;
   static const int right_index        = 6;
   static const int center_index       = 7;
   static const int bottom_left_index  = 8;
   static const int bottom_index       = 9;
   static const int bottom_right_index = 10;
   static const int bottom_tip_index   = 11;
   static const int left_tip_index     = 12;
   static const int middle_index       = 13;
   static const int right_tip_index    = 14;
   static const int isolated_index     = 15;

public:
   SixteenEdgeTileSet(
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
      );
   ~SixteenEdgeTileSet();

   ALLEGRO_BITMAP *get_full_tile();

   std::vector<ALLEGRO_BITMAP *> get_set();
};


