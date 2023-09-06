

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
      {"flip", camera.anchor },
      {"rotation", camera.rotation },
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
}


} // namespace AllegroFlare



