

#include <AllegroFlare/Layouts/Layer.hpp>




namespace AllegroFlare
{
namespace Layouts
{


Layer::Layer()
   : name("[unset-name]")
   , offset_x(0.0f)
   , offset_y(0.0f)
   , tile_mesh_is_present(false)
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




} // namespace Layouts
} // namespace AllegroFlare


