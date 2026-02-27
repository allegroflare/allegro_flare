

#include <AllegroFlare/Layouts/Layer.hpp>




namespace AllegroFlare
{
namespace Layouts
{


Layer::Layer()
   : tile_mesh_is_present(false)
   , tile_mesh({})
   , text_slots({})
   , text_data({})
   , polygons({})
   , cursor_destinations({})
   , frames({})
{
}


Layer::~Layer()
{
}


bool Layer::get_tile_mesh_is_present() const
{
   return tile_mesh_is_present;
}




} // namespace Layouts
} // namespace AllegroFlare


