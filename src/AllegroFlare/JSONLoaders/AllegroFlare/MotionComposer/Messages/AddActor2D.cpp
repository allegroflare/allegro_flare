

#include <AllegroFlare/JSONLoaders/AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>



namespace AllegroFlare::MotionComposer::Messages
{


void to_json(nlohmann::json& j, const AddActor2D& v)
{
   //j = nlohmann::json{
      //{ "position", v.get_position() },
   //};
}

void from_json(const nlohmann::json& j, AddActor2D& v)
{
   //j.at("position").get_to(v.get_position_ref());
}


} // namespace AllegroFlare::JSONLoaders::AllegroFlare::MotionComposer::Messages


