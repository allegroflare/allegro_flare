

#include <AllegroFlare/TileMaps/AutoTile/Filters/BasicFloor.hpp>




namespace AllegroFlare
{
namespace TileMaps
{
namespace AutoTile
{
namespace Filters
{


BasicFloor::BasicFloor(int floor_tile_value)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::BasicFloor::TYPE)
   , floor_tile_value(floor_tile_value)
{
}


BasicFloor::~BasicFloor()
{
}


void BasicFloor::set_floor_tile_value(int floor_tile_value)
{
   this->floor_tile_value = floor_tile_value;
}


int BasicFloor::get_floor_tile_value() const
{
   return floor_tile_value;
}


bool BasicFloor::process()
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();


   // Resize the result matrix
   result_matrix.resize(input_matrix.get_width(), input_matrix.get_height());

   std::vector<std::vector<int>> if_match = {
     { 0 },
     { 1 }
   };

   std::vector<std::vector<int>> apply_this = {
     { 0                },
     { floor_tile_value }
   };

   // HERE:
   // TODO: Test if the if_match matrix fits, and if so, apply the apply_this matrix
   //for (int y=0; y<height; y++)
      //for (int x=0; x<width; x++)
         //result_matrix.set_tile(x, y, tile_value);

   return true;
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


