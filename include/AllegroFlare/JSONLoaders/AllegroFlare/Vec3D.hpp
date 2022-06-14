#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{
   // JSON loaders for Vec3D
   void to_json(nlohmann::json& j, const AllegroFlare::Vec3D& vec3d);
   void from_json(const nlohmann::json& j, AllegroFlare::Vec3D& vec3d);
}


