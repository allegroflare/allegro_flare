

#include <tilemap/tile_map.hpp>


TileMap::TileMap(int width, int height, int tile_width)
   : width(width)
   , height(height)
   , tile_width(tile_width)
   , tiles()
{
   set_width_and_height(width, height);
}


TileMap::~TileMap()
{
}


void TileMap::set_tile(int x, int y, ALLEGRO_BITMAP *tile)
{
   if (x < 0 || x >= width) throw std::runtime_error("cannot assign tile outsize x boundaries");
   if (y < 0 || y >= height) throw std::runtime_error("cannot assign tile outsize y boundaries");
   tiles[y*width+x] = tile;
}


void TileMap::set_width_and_height(int width, int height)
{
   tiles.clear();
   tiles.resize(width * height, nullptr);
   this->width = width;
   this->height = height;
}


int TileMap::get_width() const
{
   return width;
}


int TileMap::get_height() const
{
   return height;
}


ALLEGRO_BITMAP *TileMap::get_tile(int x, int y) const
{
   if (is_out_of_bounds(x, y)) return nullptr;
   return tiles[y*width+x];
}


void TileMap::draw()
{
   for (int y=0; y<height; y++)
      for (int x=0; x<width; x++)
      {
         ALLEGRO_BITMAP *tile = tiles[y * width + x];
         if (tile) al_draw_bitmap(tile, x*tile_width, y*tile_width, 0);
      }
}


bool TileMap::is_in_bounds(int x, int y) const
{
   if (x < 0 || x >= width) return false;
   if (y < 0 || y >= height) return false;
   return true;
}


bool TileMap::is_out_of_bounds(int x, int y) const
{
   return !is_in_bounds(x, y);
}


