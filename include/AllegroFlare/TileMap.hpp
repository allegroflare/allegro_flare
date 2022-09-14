#pragma once


#include <vector>


namespace AllegroFlare
{
   template <class T>
   class TileMap
   {
   private:
      int width;
      int height;
      std::vector<T> tiles;
      bool initialized;

   public:

      TileMap(int num_columns=0, int num_rows=0);
      ~TileMap();

      void initialize();

      int get_width();
      int get_height();
      int get_num_columns();
      int get_num_rows();

      int infer_num_tiles();
      bool is_dimensionless();

      T get_tile(int tile_x, int tile_y);
      bool set_tile(int tile_x, int tile_y, T value);
      std::pair<int, int> get_coordinates_from_contiguous_number(int contiguous_tile_num);

      void resize(int w, int h);
   };
} // namespace AllegroFlare


namespace AllegroFlare
{


template <class T>
TileMap<T>::TileMap(int num_columns, int num_rows)
   : width(num_columns)
   , height(num_rows)
   , tiles()
   , initialized(false)
{}


TileMap::~TileMap()
{
}


void TileMap::initialize()
{
   if (initialized) throw std::runtime_error("AllegroFlare::TileMap::initialize() error: cannot call initialize twice.");
   resize(width, height);
   initialized = true;
}


int TileMap::get_width()
{
   // TODO: consider depreciating this in favor of get_num_columns
   return width;
}


int TileMap::get_height()
{
   // TODO: consider depreciating this in favor of get_num_rows
   return height;
}


int TileMap::get_num_columns()
{
   return width;
}


int TileMap::get_num_rows()
{
   return height;
}


int TileMap::infer_num_tiles()
{
   return width * height;
}


bool TileMap::is_dimensionless()
{
   return (width <= 0 || height <= 0);
}


int TileMap::get_tile(int tile_x, int tile_y)
{
   if (!initialized) throw std::runtime_error("AllegroFlare::TileMap::get_tile() error: tile map must be initialized first.");

   if (tile_x < 0 || (tile_x >= width)) return -1;
   if (tile_y < 0 || (tile_y >= height)) return -1;

   return tiles[tile_x + tile_y * width];
}


bool TileMap::set_tile(int tile_x, int tile_y, int value)
   // if the tile is set to a negative number, then the tiles[tile_index] will be set to that number, but
   // the image will be the bitmap at index 0
{
   if (!initialized) throw std::runtime_error("AllegroFlare::TileMap::set_tile() error: tile map must be initialized first.");

   if (tile_x < 0 || (tile_x >= width)) return false;
   if (tile_y < 0 || (tile_y >= height)) return false;

   tiles[tile_x + tile_y * width] = value;

   return true;
}


std::pair<int, int> TileMap::get_coordinates_from_contiguous_number(int contiguous_tile_num)
{
   if (is_dimensionless()) return std::pair<int, int>(-1, -1);

   int tile_x = contiguous_tile_num % width;
   int tile_y = contiguous_tile_num / width;

   return std::pair<int, int>(tile_x, tile_y);
}


void TileMap::resize(int w, int h)
{
   // TODO prevent assigning negative numbers

   // set the width and height of our map
   width = w;
   height = h;

   // resize and clear the tiles
   tiles.assign(width * height, 0);
}


} // namespace AllegroFlare


