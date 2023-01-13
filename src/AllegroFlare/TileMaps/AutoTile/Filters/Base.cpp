

#include <AllegroFlare/TileMaps/AutoTile/Filters/Base.hpp>




namespace AllegroFlare
{
namespace TileMaps
{
namespace AutoTile
{
namespace Filters
{


Base::Base(std::string type, AllegroFlare::TileMaps::AutoTile::FilterMatrix input_matrix)
   : type(type)
   , input_matrix(input_matrix)
   , result_matrix({})
{
}


Base::~Base()
{
}


void Base::set_input_matrix(AllegroFlare::TileMaps::AutoTile::FilterMatrix input_matrix)
{
   this->input_matrix = input_matrix;
}


std::string Base::get_type() const
{
   return type;
}


AllegroFlare::TileMaps::AutoTile::FilterMatrix Base::get_input_matrix() const
{
   return input_matrix;
}


AllegroFlare::TileMaps::AutoTile::FilterMatrix Base::get_result_matrix() const
{
   return result_matrix;
}


AllegroFlare::TileMaps::AutoTile::FilterMatrix &Base::get_input_matrix_ref()
{
   return input_matrix;
}


AllegroFlare::TileMaps::AutoTile::FilterMatrix &Base::get_result_matrix_ref()
{
   return result_matrix;
}


bool Base::process()
{
   return true;
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


