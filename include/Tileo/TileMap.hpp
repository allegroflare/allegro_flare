#pragma once


#include <vector>


namespace Tileo
{
   class TileMap
   {
   private:
      int width;
      int height;
      std::vector<int> tiles;
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

      int get_tile(int tile_x, int tile_y);
      bool set_tile(int tile_x, int tile_y, int value);
      std::pair<int, int> get_coordinates_from_contiguous_number(int contiguous_tile_num);

      void resize(int w, int h);
   };
}


