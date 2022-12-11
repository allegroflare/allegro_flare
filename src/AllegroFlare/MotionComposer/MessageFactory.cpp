

#include <AllegroFlare/MotionComposer/MessageFactory.hpp>

#include <AllegroFlare/JSONLoaders/AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>
#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/Clear.hpp>
#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/RunBuildProcess.hpp>
#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/SetPlayheadPosition.hpp>
#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/TogglePlayback.hpp>
#include <lib/nlohmann/json.hpp>


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

std::string MessageFactory::build_clear_message_json()
{
   AllegroFlare::MotionComposer::Messages::Clear message;
   nlohmann::json json;
   json["message"] = message;
   json["message"]["type"] = message.get_type();
   return json.dump(2);
}

std::string MessageFactory::build_run_build_process_message_json(std::string platform, std::string source_release_zip_url)
{
   AllegroFlare::MotionComposer::Messages::RunBuildProcess message(platform, source_release_zip_url);
   nlohmann::json json;
   json["message"] = message;
   json["message"]["type"] = message.get_type();
   return json.dump(2);
}

std::string MessageFactory::build_add_actor2d_with_script_message_json(std::string identifier, std::string bitmap_identifier, std::string script)
{
   AllegroFlare::MotionComposer::Messages::AddActor2D message(identifier, bitmap_identifier, script);
   nlohmann::json json;
   json["message"] = message;
   json["message"]["type"] = message.get_type();
   return json.dump(2);
}


} // namespace MotionComposer
} // namespace AllegroFlare


