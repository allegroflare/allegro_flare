

#include <AllegroFlare/MotionComposer/MessageFactory.hpp>
#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/SetPlayheadPosition.hpp>


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


std::string MessageFactory::build_set_playhead_position_message_json(float position)
{
   AllegroFlare::MotionComposer::Messages::SetPlayheadPosition set_playhead_position(position);
   nlohmann::json json;
   json["message"] = set_playhead_position;
   json["message"]["type"] = "SetPlayheadPosition";
   return json.dump(2);
}

AllegroFlare::MotionComposer::Messages::SetPlayheadPosition* MessageFactory::create_set_playhead_position_message(float position)
{
   AllegroFlare::MotionComposer::Messages::SetPlayheadPosition *set_playhead_position
      = new AllegroFlare::MotionComposer::Messages::SetPlayheadPosition(position);
   return set_playhead_position;
}
} // namespace MotionComposer
} // namespace AllegroFlare


