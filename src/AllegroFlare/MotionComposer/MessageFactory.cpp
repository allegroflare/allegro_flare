

#include <AllegroFlare/MotionComposer/MessageFactory.hpp>



namespace AllegroFlare
{
namespace MotionComposer
{


MessageFactory::MessageFactory()
{
}


MessageFactory::~MessageFactory()
{
}


AllegroFlare::MotionComposer::Messages::SetPlayheadPosition* MessageFactory::create_set_playead_position_message(float position)
{
   AllegroFlare::MotionComposer::Messages::SetPlayheadPosition *result =
      new AllegroFlare::MotionComposer::Messages::SetPlayheadPosition(position);
   return result;
}
} // namespace MotionComposer
} // namespace AllegroFlare


