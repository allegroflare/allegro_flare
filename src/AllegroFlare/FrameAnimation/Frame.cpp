

#include <AllegroFlare/FrameAnimation/Frame.hpp>




namespace AllegroFlare
{
namespace FrameAnimation
{


Frame::Frame(uint32_t index, float duration)
   : index(index)
   , duration(duration)
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




} // namespace FrameAnimation
} // namespace AllegroFlare


