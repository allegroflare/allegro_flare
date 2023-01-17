#pragma once


#include <allegro5/allegro.h>
#include <vector>


class TileMap
{
private:
   int width, height;
   int tile_width;
   std::vector<ALLEGRO_BITMAP *> tiles;

public:
   TileMap(int width, int height, int tile_width);
   ~TileMap();

   void set_tile(int x, int y, ALLEGRO_BITMAP *tile);
   void set_width_and_height(int width, int height);

   int get_width() const;
   int get_height() const;
   ALLEGRO_BITMAP *get_tile(int x, int y) const;

   void draw();

   bool is_in_bounds(int x, int y) const;
   bool is_out_of_bounds(int x, int y) const;
};


