


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
      {"spin_in_unit_values", camera.spin_in_unit_values},
      {"tilt_in_unit_values", camera.tilt_in_unit_values},
      {"roll_in_unit_values", camera.roll_in_unit_values},
      //bool spin_in_unit_values;
      //bool tilt_in_unit_values;
      //bool roll_in_unit_values;
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
   j.at("spin_in_unit_values").get_to(camera.spin_in_unit_values);
   j.at("roll_in_unit_values").get_to(camera.roll_in_unit_values);
   j.at("tilt_in_unit_values").get_to(camera.tilt_in_unit_values);
}



} // namespace AllegroFlare


