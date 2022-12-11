

#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/RunBuildProcess.hpp>



namespace AllegroFlare::MotionComposer::Messages
{


void to_json(nlohmann::json& j, const AllegroFlare::MotionComposer::Messages::RunBuildProcess& v)
{
   j = nlohmann::json{
      { "platform", v.get_platform() },
   };
}

void from_json(const nlohmann::json& j, AllegroFlare::MotionComposer::Messages::RunBuildProcess& v)
{
   j.at("platform").get_to(v.get_platform_ref());
}


} // namespace AllegroFlare/JSONLoaders/MotionComposer/Messages


