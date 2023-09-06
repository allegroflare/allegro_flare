

#include <AllegroFlare/JSONLoaders/AllegroFlare/Camera2D.hpp>

#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec2B.hpp>


namespace AllegroFlare
{


void to_json(nlohmann::json& j, const Camera2D& camera)
{
   j = nlohmann::json{
      {"position", camera.position },
      {"size", camera.size },
      {"align", camera.align },
      {"scale", camera.scale },
      {"anchor", camera.anchor },
      {"flip", camera.flip },
      {"rotation", camera.rotation },
      {"width_num_units", camera.get_width_num_units() },
      {"height_num_units", camera.get_height_num_units() },
   };
}

void from_json(const nlohmann::json& j, Camera2D& camera)
{
   j.at("position").get_to(camera.position);
   j.at("size").get_to(camera.size);
   j.at("align").get_to(camera.align);
   j.at("scale").get_to(camera.scale);
   j.at("anchor").get_to(camera.anchor);
   j.at("flip").get_to(camera.flip);
   j.at("rotation").get_to(camera.rotation);
   decltype(camera.get_width_num_units()) width_num_units;
   j.at("width_num_units").get_to(width_num_units);
   decltype(camera.get_height_num_units()) height_num_units;
   j.at("height_num_units").get_to(height_num_units);
}


} // namespace AllegroFlare



