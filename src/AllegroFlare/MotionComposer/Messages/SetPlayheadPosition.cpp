

#include <AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>



namespace AllegroFlare
{
namespace MotionComposer
{
namespace Messages
{


SetPlayheadPosition::SetPlayheadPosition(float position)
   : AllegroFlare::MotionComposer::Messages::Base("SetPlayheadPosition")
   , position(position)
{
}


SetPlayheadPosition::~SetPlayheadPosition()
{
}


void SetPlayheadPosition::set_position(float position)
{
   this->position = position;
}


float SetPlayheadPosition::get_position() const
{
   return position;
}


float &SetPlayheadPosition::get_position_ref()
{
   return position;
}


} // namespace Messages
} // namespace MotionComposer
} // namespace AllegroFlare


