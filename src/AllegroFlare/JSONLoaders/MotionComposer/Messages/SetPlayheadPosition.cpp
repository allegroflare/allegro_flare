

#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/SetPlayheadPosition.hpp>



namespace AllegroFlare
{
namespace MotionComposer
{
namespace Messages
{


void to_json(nlohmann::json& j, const AllegroFlare::MotionComposer::Messages::SetPlayheadPosition& v)
{
   j = nlohmann::json{
      { "position", v.get_position() },
   };
}

void from_json(const nlohmann::json& j, AllegroFlare::MotionComposer::Messages::SetPlayheadPosition& v)
{
   j.at("position").get_to(v.get_position_ref());
}


} // namespace Messages
} // namespace MotionComposer
} // namespace AllegroFlare


