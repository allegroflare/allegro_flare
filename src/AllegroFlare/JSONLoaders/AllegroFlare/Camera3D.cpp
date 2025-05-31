


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
      {"roll", camera.roll},
      {"zoom", camera.zoom},
      {"near_plane", camera.near_plane},
      {"far_plane", camera.far_plane},
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
   j.at("roll").get_to(camera.roll);
   j.at("near_plane").get_to(camera.near_plane);
   j.at("far_plane").get_to(camera.far_plane);
}



} // namespace AllegroFlare


