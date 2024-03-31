

#include <AllegroFlare/FrameAnimation/Frame.hpp>




namespace AllegroFlare
{
namespace FrameAnimation
{


Frame::Frame(uint32_t index, float duration, float align_x, float align_y, float anchor_x, float anchor_y)
   : index(index)
   , duration(duration)
   , align_x(align_x)
   , align_y(align_y)
   , anchor_x(anchor_x)
   , anchor_y(anchor_y)
{
}


Frame::~Frame()
{
}


uint32_t Frame::get_index() const
{
   return index;
}


float Frame::get_duration() const
{
   return duration;
}


float Frame::get_align_x() const
{
   return align_x;
}


float Frame::get_align_y() const
{
   return align_y;
}


float Frame::get_anchor_x() const
{
   return anchor_x;
}


float Frame::get_anchor_y() const
{
   return anchor_y;
}




} // namespace FrameAnimation
} // namespace AllegroFlare


