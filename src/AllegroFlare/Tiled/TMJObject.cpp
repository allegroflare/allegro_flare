

#include <AllegroFlare/Tiled/TMJObject.hpp>




namespace AllegroFlare
{
namespace Tiled
{


TMJObject::TMJObject()
   : type("[unset-type]")
   , id(0)
   , name("[unset-name]")
   , x(0.0f)
   , y(0.0f)
   , width(0.0f)
   , height(0.0f)
   , polygon({})
   , custom_properties({})
   , object_layer_name("[unset-object_layer_name]")
{
}


TMJObject::~TMJObject()
{
}


AllegroFlare::Vec2D TMJObject::center()
{
   return AllegroFlare::Vec2D(x + width / 2, y + height / 2);
}


} // namespace Tiled
} // namespace AllegroFlare


