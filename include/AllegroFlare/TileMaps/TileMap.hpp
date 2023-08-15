#pragma once


#include <AllegroFlare/Logger.hpp>
#include <vector>
#include <stdexcept>


namespace AllegroFlare::TileMaps
{
   template <class T>
   class TileMap
   {
   private:
      int num_columns;
      int num_rows;
      std::vector<T> tiles;
      bool initialized;

   public:

      TileMap(int num_columns=0, int num_rows=0);
      ~TileMap();

      void initialize();

      int get_num_columns();
      int get_num_rows();
      bool get_initialized();

      int infer_num_tiles();
      bool is_dimensionless();

      const std::vector<T> get_tiles() const;
      bool in_bounds(int tile_x, int tile_y);
      T get_tile(int tile_x, int tile_y);
      bool set_tile(int tile_x, int tile_y, T value);
      bool set_contiguous_tile(int tile_i, T value);
      std::pair<int, int> get_coordinates_from_contiguous_number(int contiguous_tile_num);

      void resize(int w, int h);
      void clear(int clear_to_value=0);
   };



template <class T>
TileMap<T>::TileMap(int num_columns, int num_rows)
   : num_columns(num_columns)
   , num_rows(num_rows)
   , tiles()
   , initialized(false)
{}


template <class T>
TileMap<T>::~TileMap()
{
}


template <class T>
void TileMap<T>::initialize()
{
   if (initialized) throw std::runtime_error("AllegroFlare::TileMaps::TileMap<T>::initialize() error: cannot call initialize twice.");
   resize(num_columns, num_rows);
   initialized = true;
}


template <class T>
int TileMap<T>::get_num_columns()
{
   return num_columns;
}


template <class T>
int TileMap<T>::get_num_rows()
{
   return num_rows;
}


template <class T>
bool TileMap<T>::get_initialized()
{
   return initialized;
}


template <class T>
int TileMap<T>::infer_num_tiles()
{
   return num_columns * num_rows;
}


template <class T>
bool TileMap<T>::is_dimensionless()
{
   return (num_columns <= 0 || num_rows <= 0);
}


template <class T>
const std::vector<T> TileMap<T>::get_tiles() const
{
   return tiles;
}


template <class T>
bool TileMap<T>::in_bounds(int tile_x, int tile_y)
{
   if (tile_x < 0 || (tile_x >= num_columns)) return false;
   if (tile_y < 0 || (tile_y >= num_rows)) return false;
   return true;
}


template <class T>
T TileMap<T>::get_tile(int tile_x, int tile_y)
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::get_tile()",
         "tile map must be initialized first."
      );
      //throw std::runtime_error("AllegroFlare::TileMaps::TileMap<T>::get_tile() error: tile map must be initialized first.");
   }

   if (tile_x < 0 || (tile_x >= num_columns)) return -1;
   if (tile_y < 0 || (tile_y >= num_rows)) return -1;

   return tiles[tile_x + tile_y * num_columns];
}


template <class T>
bool TileMap<T>::set_tile(int tile_x, int tile_y, T value)
   // if the tile is set to a negative number, then the tiles[tile_index] will be set to that number, but
   // the image will be the bitmap at index 0
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::set_tile()",
         "tile map must be initialized first."
      );
   }

   if (tile_x < 0 || (tile_x >= num_columns)) return false;
   if (tile_y < 0 || (tile_y >= num_rows)) return false;

   tiles[tile_x + tile_y * num_columns] = value;

   return true;
}


template <class T>
bool TileMap<T>::set_contiguous_tile(int tile_i, T value)
{
   // TODO: Test this
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::set_contiguous_tile()",
         "tile map must be initialized first."
      );
   }

   if (tile_i < 0 || (tile_i >= (num_rows * num_columns))) return false;
   tiles[tile_i] = value;

   return true;
}


template <class T>
std::pair<int, int> TileMap<T>::get_coordinates_from_contiguous_number(int contiguous_tile_num)
{
   if (is_dimensionless()) return std::pair<int, int>(-1, -1);

   int tile_x = contiguous_tile_num % num_columns;
   int tile_y = contiguous_tile_num / num_columns;

   return std::pair<int, int>(tile_x, tile_y);
}


template <class T>
void TileMap<T>::resize(int num_columns, int h)
{
   // TODO prevent assigning negative numbers

   // set the num_columns and num_rows of our map
   this->num_columns = num_columns;
   num_rows = h;

   // resize and clear the tiles
   tiles.assign(num_columns* num_rows, 0);
}


template <class T>
void TileMap<T>::clear(int clear_to_value)
{
   // resize and clear the tiles
   tiles.assign(num_columns* num_rows, clear_to_value);
}


} // namespace AllegroFlare::TileMaps


