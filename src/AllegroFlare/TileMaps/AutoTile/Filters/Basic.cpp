

#include <AllegroFlare/TileMaps/AutoTile/Filters/Basic.hpp>




namespace AllegroFlare
{
namespace TileMaps
{
namespace AutoTile
{
namespace Filters
{


Basic::Basic(std::string property)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::Basic::TYPE)
   , property(property)
{
}


Basic::~Basic()
{
}


std::string Basic::get_property() const
{
   return property;
}


bool Basic::process()
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();
   result_matrix.resize(1, 2);
   return true;
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


