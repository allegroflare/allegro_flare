

#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/TogglePlayback.hpp>



namespace AllegroFlare::MotionComposer::Messages
{


void to_json(nlohmann::json& j, const AllegroFlare::MotionComposer::Messages::TogglePlayback& v)
{
   j = nlohmann::json{
      //{ "position", v.get_position() },
   };
}

void from_json(const nlohmann::json& j, AllegroFlare::MotionComposer::Messages::TogglePlayback& v)
{
   //j.at("position").get_to(v.get_position_ref());
}


} // namespace AllegroFlare::MotionComposer::Messages


