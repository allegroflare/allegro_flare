

#include <AllegroFlare/TileMaps/AutoTile/Filters/Fill.hpp>




namespace AllegroFlare
{
namespace TileMaps
{
namespace AutoTile
{
namespace Filters
{


Fill::Fill(int tile_value)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::Fill::TYPE)
   , tile_value(tile_value)
{
}


Fill::~Fill()
{
}


void Fill::set_tile_value(int tile_value)
{
   this->tile_value = tile_value;
}


int Fill::get_tile_value() const
{
   return tile_value;
}


bool Fill::process()
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();

   result_matrix = get_input_matrix();
   int width = result_matrix.get_width();
   int height = result_matrix.get_height();

   for (int y=0; y<height; y++)
      for (int x=0; x<width; x++)
         result_matrix.set_tile(x, y, tile_value);

   return true;
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


