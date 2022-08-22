

#include <AllegroFlare/MotionComposer/MessageFactory.hpp>
#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/SetPlayheadPosition.hpp>
#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/TogglePlayback.hpp>


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
   AllegroFlare::MotionComposer::Messages::SetPlayheadPosition message(position);
   nlohmann::json json;
   json["message"] = message;
   json["message"]["type"] = message.get_type();
   return json.dump(2);
}

std::string MessageFactory::build_toggle_playback_message_json()
{
   AllegroFlare::MotionComposer::Messages::TogglePlayback message;
   nlohmann::json json;
   json["message"] = message;
   json["message"]["type"] = message.get_type();
   return json.dump(2);
}
} // namespace MotionComposer
} // namespace AllegroFlare


