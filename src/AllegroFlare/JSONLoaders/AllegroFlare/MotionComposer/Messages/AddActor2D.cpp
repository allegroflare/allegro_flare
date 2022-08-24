

#include <AllegroFlare/JSONLoaders/AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>



namespace AllegroFlare::MotionComposer::Messages
{


void to_json(nlohmann::json& j, const AddActor2D& v)
{
   j = nlohmann::json{
      { "identifier", v.get_identifier() },
      { "script", v.get_script() },
   };
}

void from_json(const nlohmann::json& j, AddActor2D& v)
{
   j.at("identifier").get_to(v.get_identifier_ref());
   j.at("script").get_to(v.get_script_ref());
}


} // namespace AllegroFlare::JSONLoaders::AllegroFlare::MotionComposer::Messages


