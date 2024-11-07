

#include <AllegroFlare/Layouts/Elements/Text.hpp>




namespace AllegroFlare
{
namespace Layouts
{
namespace Elements
{


Text::Text()
   : name("[unset-name]")
   , x(0.0f)
   , y(0.0f)
   , width(0.0f)
   , height(0.0f)
   , align_x(0.0f)
   , align_y(0.0f)
   , font_family("[unset-font_family]")
   , font_size(0)
   , color(ALLEGRO_COLOR{1, 1, 1, 1})
   , tmj_object_id(0.0f)
   , on_focus({})
   , on_blur({})
   , on_activation({})
{
}


Text::~Text()
{
}




} // namespace Elements
} // namespace Layouts
} // namespace AllegroFlare


