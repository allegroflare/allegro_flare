#pragma once


#include <AllegroFlare/Logger.hpp>
#include <vector>
#include <stdexcept>
#include <sstream>


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
      T &get_tile_ref(int tile_x, int tile_y);
      T get_tile_or_fallback(int tile_x, int tile_y, T fallback);
      bool set_tile(int tile_x, int tile_y, T value);
      bool set_contiguous_tile(int tile_i, T value);
      std::pair<int, int> get_coordinates_from_contiguous_number(int contiguous_tile_num);

      void resize(int w, int h);
      void resize_with_fill(int w, int h, T value);
      void resize_and_fill_with_contiguous_data(int num_columns, int num_rows, std::vector<T> data);
      void fill_with_data(std::vector<std::vector<T>> data);
      void fill_area(int tile_x1, int tile_y1, int tile_x2, int tile_y2, T value);
      std::vector<std::vector<T>> build_data_as_2d_vector();
      void clear(int clear_to_value=0); // TODO: Use T instead of int here
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
void TileMap<T>::fill_with_data(std::vector<std::vector<T>> data)
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
         "Must be initialized first"
      );
   }

   // Validate number of rows
   int num_data_rows = data.size();
   if (num_data_rows == 0)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
         "data cannot be empty"
      );
   }
   if (num_data_rows != num_rows)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
         "The number of rows in the provided data (" + std::to_string(num_data_rows) + ") does not match the number of "
            "rows of the tile_map (" + std::to_string(num_rows) + ")"
      );
   }

   // Validate number of columns (in each row)
   for (int i=0; i<(int)data.size(); i++)
   {
      int num_data_columns = data[i].size();
      if (num_data_columns == 0)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
            "data in column cannot be empty"
         );
      }
      if (num_data_columns != num_columns)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
            "The number of columns in the provided data (" + std::to_string(num_data_columns) + ") does not match the "
               "number of columns of the tile_map (" + std::to_string(num_columns) + ")"
         );
      }
   }

   // Fill the data
   for (int y=0; y<num_rows; y++)
   {
      for (int x=0; x<num_columns; x++)
      {
         set_tile(x, y, data[y][x]);
      }
   }

   return;
}


template <class T>
void TileMap<T>::resize_and_fill_with_contiguous_data(int num_columns, int num_rows, std::vector<T> data)
//void TileMap<T>::fill_with_data(std::vector<std::vector<T>> data)
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::resize_and_fill_with_contiguous_data",
         "Must be initialized first"
      );
   }

   // Validate number of rows and columns are not empty
   if (num_columns <= 0)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::resize_and_fill_with_contiguous_data",
         "num_columns cannot be less than or equal to 0"
      );
   }
   if (num_rows <= 0)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::resize_and_fill_with_contiguous_data",
         "num_rows cannot be less than or equal to 0"
      );
   }

   // Validate num_rows and num_columns matches the size of the data
   int expected_data_size = num_rows * num_columns;
   if (expected_data_size != data.size())
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::resize_and_fill_with_contiguous_data",
         "Expecting \"data.size()\" (has a value of " + std::to_string(data.size()) + ") to be of equal size as "
         "\"num_rows * num_columns\" (has a value of " + std::to_string(expected_data_size) + ")"
      );
   }

   // Fill the data
   this->num_columns = num_columns;
   this->num_rows = num_rows;
   tiles = data;

   return;
}



template <class T>
void TileMap<T>::fill_area(int tile_x1, int tile_y1, int tile_x2, int tile_y2, T value)
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_area",
         "Must be initialized first"
      );
   }

   if (!(tile_x1 >= 0))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
         "tile_x1 must be >= 0"
      );
   }
   if (!(tile_y1 >= 0))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
         "tile_y1 must be >= 0"
      );
   }
   if (!(tile_x2 >= 0))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
         "tile_x2 must be >= 0"
      );
   }
   if (!(tile_x2 >= 0))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
         "tile_x2 must be >= 0"
      );
   }
   if (!(tile_x1 < num_rows))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
         "tile_x1 must be < num_rows"
      );
   }
   if (!(tile_y1 < num_columns))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
         "tile_y1 must be < num_columns"
      );
   }
   if (!(tile_x2 < num_rows))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
         "tile_x2 must be < num_rows"
      );
   }
   if (!(tile_y2 < num_columns))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::fill_with_data",
         "tile_y2 must be < num_columns"
      );
   }

   // Use min and max values so user can provide reversed coordinates with no issues
   int tile_min_x = std::min(tile_x1, tile_x2);
   int tile_min_y = std::min(tile_y1, tile_y2);
   int tile_max_x = std::max(tile_x1, tile_x2);
   int tile_max_y = std::max(tile_y1, tile_y2);

   // Fill the data
   for (int y=tile_min_y; y<=tile_max_y; y++)
   {
      for (int x=tile_min_x; x<=tile_max_x; x++)
      {
         set_tile(x, y, value);
      }
   }
}


template <class T>
std::vector<std::vector<T>> TileMap<T>::build_data_as_2d_vector()
{
   std::vector<std::vector<T>> result;
   result.resize(num_rows);
   for (int row=0; row<result.size(); row++)
   {
      result[row].resize(num_columns);
      for (int column=0; column<num_columns; column++)
      {
         result[row][column] = get_tile(column, row);
      }
   }
   return result;
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

   if (tile_x < 0 || (tile_x >= num_columns))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::get_tile()",
         "The tile_x argument passed was either less than 0 or greater than or equal to the number of columns."
      );
   }
   if (tile_y < 0 || (tile_y >= num_rows))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::get_tile()",
         "The tile_y argument passed was either less than 0 or greater than or equal to the number of rows."
      );
   }

   return tiles[tile_x + tile_y * num_columns];
}


template <class T>
T &TileMap<T>::get_tile_ref(int tile_x, int tile_y)
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::get_tile_ref()",
         "tile map must be initialized first."
      );
      //throw std::runtime_error("AllegroFlare::TileMaps::TileMap<T>::get_tile_ref() error: tile map must be initialized first.");
   }

   if (tile_x < 0 || (tile_x >= num_columns))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::get_tile_ref()",
         "The tile_x argument passed was either less than 0 or greater than or equal to the number of columns."
      );
   }
   if (tile_y < 0 || (tile_y >= num_rows))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::get_tile_ref()",
         "The tile_y argument passed was either less than 0 or greater than or equal to the number of rows."
      );
   }

   return tiles[tile_x + tile_y * num_columns];
}


template <class T>
T TileMap<T>::get_tile_or_fallback(int tile_x, int tile_y, T fallback)
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::get_tile()",
         "tile map must be initialized first."
      );
   }

   if (tile_x < 0 || (tile_x >= num_columns))
   {
      return fallback;
   }
   if (tile_y < 0 || (tile_y >= num_rows))
   {
      return fallback;
   }

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
         "AllegroFlare::TileMaps::TileMap<T>::set_tile",
         "tile map must be initialized first."
      );
   }

   if (tile_x < 0 || (tile_x >= num_columns))
   {
      std::stringstream error_message;
      error_message << "Cannot set tile to out-of-bounds positon [" << tile_x << ", " << tile_y
         << "], must be within map size of [" << num_columns << ", " << num_rows << "]";

      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::set_tile",
         error_message.str()
      );
   }
   if (tile_y < 0 || (tile_y >= num_rows))
   {
      std::stringstream error_message;
      error_message << "Cannot set tile to out-of-bounds positon [" << tile_x << ", " << tile_y
         << "], must be within map size of [" << num_columns << ", " << num_rows << "]";

      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileMap<T>::set_tile",
         error_message.str()
      );
   }

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
   tiles.assign(num_columns* num_rows, {}); // Resize with default constructor for whatever T is
}


template <class T>
void TileMap<T>::resize_with_fill(int num_columns, int h, T value)
{
   // TODO prevent assigning negative numbers

   // set the num_columns and num_rows of our map
   this->num_columns = num_columns;
   num_rows = h;

   // resize and clear the tiles
   tiles.assign(num_columns* num_rows, value);
}


template <class T>
void TileMap<T>::clear(int clear_to_value)
{
   // resize and clear the tiles
   tiles.assign(num_columns* num_rows, clear_to_value);
}


} // namespace AllegroFlare::TileMaps


