

#include <AllegroFlare/Layouts/Elements/Polygon.hpp>




namespace AllegroFlare
{
namespace Layouts
{
namespace Elements
{


Polygon::Polygon()
   : name("[unset-name]")
   , x(0.0f)
   , y(0.0f)
   , width(0.0f)
   , height(0.0f)
   , polygon({})
   , path()
   , fill_color(ALLEGRO_COLOR{1, 1, 1, 1})
   , tmj_object_id(0.0f)
   , on_focus({})
   , on_blur({})
   , on_activation({})
{
}


Polygon::~Polygon()
{
}




} // namespace Elements
} // namespace Layouts
} // namespace AllegroFlare


