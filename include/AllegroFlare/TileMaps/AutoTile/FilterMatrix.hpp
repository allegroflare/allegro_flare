#pragma once


#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace TileMaps
   {
      namespace AutoTile
      {
         class FilterMatrix
         {
         private:
            std::vector<std::vector<int>> matrix;
            std::pair<int, int> axis;

         protected:


         public:
            FilterMatrix();
            ~FilterMatrix();

            std::vector<std::vector<int>> get_matrix() const;
            void resize(int width=1, int height=1);
            int get_width() const;
            int get_height() const;
            void set_tile(int x=0, int y=0, int tile_value=0);
         };
      }
   }
}



