

#include <AllegroFlare/Layouts/Elements/Frame.hpp>




namespace AllegroFlare
{
namespace Layouts
{
namespace Elements
{


Frame::Frame()
   : name("[unset-name]")
   , x(0.0f)
   , y(0.0f)
   , width(0.0f)
   , height(0.0f)
   , tmj_object_id(0.0f)
   , on_focus({})
   , on_blur({})
   , on_activation({})
{
}


Frame::~Frame()
{
}




} // namespace Elements
} // namespace Layouts
} // namespace AllegroFlare


