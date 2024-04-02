

#include <AllegroFlare/FrameAnimation/Frame.hpp>




namespace AllegroFlare
{
namespace FrameAnimation
{


Frame::Frame(uint32_t index, float duration, float align_x, float align_y, float align_in_container_x, float align_in_container_y, float anchor_x, float anchor_y)
   : index(index)
   , duration(duration)
   , align_x(align_x)
   , align_y(align_y)
   , align_in_container_x(align_in_container_x)
   , align_in_container_y(align_in_container_y)
   , anchor_x(anchor_x)
   , anchor_y(anchor_y)
{
}


Frame::~Frame()
{
}


void Frame::set_index(uint32_t index)
{
   this->index = index;
}


void Frame::set_duration(float duration)
{
   this->duration = duration;
}


void Frame::set_align_x(float align_x)
{
   this->align_x = align_x;
}


void Frame::set_align_y(float align_y)
{
   this->align_y = align_y;
}


void Frame::set_align_in_container_x(float align_in_container_x)
{
   this->align_in_container_x = align_in_container_x;
}


void Frame::set_align_in_container_y(float align_in_container_y)
{
   this->align_in_container_y = align_in_container_y;
}


void Frame::set_anchor_x(float anchor_x)
{
   this->anchor_x = anchor_x;
}


void Frame::set_anchor_y(float anchor_y)
{
   this->anchor_y = anchor_y;
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


float Frame::get_align_in_container_x() const
{
   return align_in_container_x;
}


float Frame::get_align_in_container_y() const
{
   return align_in_container_y;
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


