


#include <AllegroFlare/JSONLoaders/AllegroFlare/Camera3D.hpp>


#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{


// JSON loader for Camera3D
void to_json(nlohmann::json& j, const AllegroFlare::Camera3D& camera)
{
   j = nlohmann::json{
      {"position", camera.position},
      {"stepout", camera.stepout},
      {"spin", camera.spin},
      {"tilt", camera.tilt},
      {"zoom", camera.zoom},
   };
}


// JSON loader for Camera3D
void from_json(const nlohmann::json& j, AllegroFlare::Camera3D& camera)
{
   j.at("position").get_to(camera.position);
   j.at("stepout").get_to(camera.stepout);
   j.at("spin").get_to(camera.spin);
   j.at("tilt").get_to(camera.tilt);
   j.at("zoom").get_to(camera.zoom);
}



} // namespace AllegroFlare


