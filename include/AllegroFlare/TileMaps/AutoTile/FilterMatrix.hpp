#pragma once


#include <AllegroFlare/TileMaps/AutoTile/FilterMatrix.hpp>
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
            static AllegroFlare::TileMaps::AutoTile::FilterMatrix build(std::vector<std::vector<int>> matrix={});
            void set_matrix(std::vector<std::vector<int>> matrix={});
            static bool STATIC_is_valid(std::vector<std::vector<int>> matrix={});
            void resize(int width=1, int height=1);
            int get_width() const;
            int get_height() const;
            void set_tile(int x=0, int y=0, int tile_value=0);
            bool set_tile_ignore_if_out_of_bounds(int x=0, int y=0, int tile_value=0);
            bool tile_matches(int x=0, int y=0, int tile_value=0);
         };
      }
   }
}



