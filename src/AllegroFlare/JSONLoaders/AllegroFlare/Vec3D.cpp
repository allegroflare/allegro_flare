

#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec3D.hpp>



namespace AllegroFlare
{


// JSON loader for Vec3D
void to_json(nlohmann::json& j, const vec3d& v)
{
   j = nlohmann::json{
      {"x", v.x},
      {"y", v.y},
      {"z", v.z},
   };
}

// JSON loader for Vec3D
void from_json(const nlohmann::json& j, vec3d& v)
{
   j.at("x").get_to(v.x);
   j.at("y").get_to(v.y);
   j.at("z").get_to(v.z);
}



} // namespace AllegroFlare


