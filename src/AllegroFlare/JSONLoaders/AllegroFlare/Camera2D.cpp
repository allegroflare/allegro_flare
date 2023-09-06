

#include <AllegroFlare/JSONLoaders/AllegroFlare/Camera2D.hpp>


namespace AllegroFlare
{


void to_json(nlohmann::json& j, const Camera2D& v)
{
   j = nlohmann::json{
   // TODO: These properties
      //{"position", camera.position},
      //{"stepout", camera.stepout},
      //{"spin", camera.spin},
      //{"tilt", camera.tilt},
      //{"zoom", camera.zoom},
   };
}

void from_json(const nlohmann::json& j, Camera2D& v)
{
   // TODO: These properties
   //j.at("position").get_to(camera.position);
   //j.at("stepout").get_to(camera.stepout);
   //j.at("spin").get_to(camera.spin);
   //j.at("tilt").get_to(camera.tilt);
   //j.at("zoom").get_to(camera.zoom);
}


} // namespace AllegroFlare



