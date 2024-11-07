

#include <AllegroFlare/Layouts/Elements/CursorDestination.hpp>




namespace AllegroFlare
{
namespace Layouts
{
namespace Elements
{


CursorDestination::CursorDestination()
   : name("[unset-name]")
   , x(0.0f)
   , y(0.0f)
   , width(0.0f)
   , height(0.0f)
   , tmj_object_id(0.0f)
   , move_up_to_target_tmj_object_id(0)
   , move_down_to_target_tmj_object_id(0)
   , move_left_to_target_tmj_object_id(0)
   , move_right_to_target_tmj_object_id(0)
   , on_focus({})
   , on_blur({})
   , on_activation({})
{
}


CursorDestination::~CursorDestination()
{
}




} // namespace Elements
} // namespace Layouts
} // namespace AllegroFlare


